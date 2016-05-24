/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.hpp"
#include "imu.hpp"
#include "lsm9ds0.hpp"
#include "lsm9ds0_io.hpp"
#include "adxl375.hpp"
#include "adxl375_io.hpp"
#include "interlocked.hpp"
#include "interrupt.hpp"
#include <stdint.h>


static uint8_t* putImuOutputToBuffer(uint8_t* p, const ImuOutput& output)
{
	*(p++) = output.x & 0xff;
	*(p++) = output.x >> 8;
	*(p++) = output.y & 0xff;
	*(p++) = output.y >> 8;
	*(p++) = output.z & 0xff;
	*(p++) = output.z >> 8;
	return p;
}

static InterruptLock interruptLock;

struct InterruptDisableOnReadIntelockPolicy
{
	static void enterRead() { interruptLock.enter(); }
	static void leaveRead() { interruptLock.leave(); }
	static void enterWrite() { }
	static void leaveWrite() { }
};
template<typename TValue> using InterruptInterlocked = InterlockedAccess<TValue, InterruptDisableOnReadIntelockPolicy>;

static volatile uint8_t ledOutput = 0x00;
static constexpr uint8_t LED_BLE_CONNECTED = 0x02;
static constexpr uint8_t LED_ALIVE = 0x01;
static uint16_t aliveLedBlinkCounter = 0;
static constexpr uint16_t ALIVE_LED_BLINK_INTERVAL = 400;

typedef LSM9DS0<LSM9DS0_IOAccessPolicy> IMU;
typedef typename IMU::AccessPolicyType IMUAccessPolicy;
typedef ADXL375<ADXL375_IOAccessPolicy> WRA;	// Wide-Range Accelerometer
typedef typename WRA::AccessPolicyType WRAAccessPolicy;

static InterruptInterlocked<ImuOutput> lastGyroOutput;
static InterruptInterlocked<ImuOutput> lastMagnetometerOutput;
static InterruptInterlocked<ImuOutput> lastAccelerometerOutput;
static InterruptInterlocked<ImuOutput> lastWRAOutput;
static bool isNotificationEnabled = false;
static volatile bool hasNewData = false;

struct SampledOutput
{
	ImuOutput gyro;
	ImuOutput magnetometer;
	ImuOutput accelerometer[2];
	ImuOutput wra[2];
};

static InterruptInterlocked<SampledOutput> sampledOutput;

template<>
void IMUAccessPolicy::onGyroDataReady(const ImuOutput& output)
{
	lastGyroOutput = output;
}
template<>
void IMUAccessPolicy::onMagnetometerDataReady(const ImuOutput& output)
{
	lastMagnetometerOutput = output;
}
template<>
void IMUAccessPolicy::onAccelerometerDataReady(const ImuOutput& output)
{
	lastAccelerometerOutput = output;
}

template <>
void WRAAccessPolicy::onDataReady(const ImuOutput& output)
{
	lastWRAOutput = output;
}

CY_ISR(SwitchInterruptHandler)
{
	CySoftwareReset();
}

CY_ISR(SamplingInterruptHandler)
{
    static uint8_t sampleCount = 0;
	static ImuOutput prevAccelerometer;
	static ImuOutput prevWra;

	Timer_Sampling_ClearInterrupt(Timer_Sampling_INTR_MASK_TC);
	ISR_SampleOutput_ClearPending();
	
	if (sampleCount == 1)
	{
		SampledOutput next = sampledOutput;
		next.accelerometer[1] = prevAccelerometer;
		next.accelerometer[0] = lastAccelerometerOutput;
		next.wra[1] = prevWra;
		next.wra[0] = lastWRAOutput;
		next.gyro = lastGyroOutput;
		next.magnetometer = lastMagnetometerOutput;
		sampledOutput.assign(next);

		hasNewData = true;
	}
	else
	{
		prevAccelerometer = lastAccelerometerOutput;
		prevWra = lastWRAOutput;
	}
    sampleCount = (sampleCount + 1) & 1;
}

static void BleCallback(uint32 eventCode, void *eventParam)
{
	switch (eventCode)
	{
	case CYBLE_EVT_STACK_ON:
	case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
		ledOutput &= ~LED_BLE_CONNECTED;
		// Start Advertisement
		CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
		break;
	case CYBLE_EVT_GAP_DEVICE_CONNECTED:
		//// Update connection parameters
		//{
		//	CYBLE_GAP_CONN_UPDATE_PARAM_T connParam = {
		//		800,
		//		800,
		//		0,
		//		500,
		//	};

		//	CyBle_L2capLeConnectionParamUpdateRequest(cyBle_connHandle.bdHandle, &connParam);
		//}
		ledOutput |= LED_BLE_CONNECTED;
		break;
	case CYBLE_EVT_TIMEOUT:
		break;
	case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
		if (CyBle_GetState() != CYBLE_STATE_ADVERTISING)
		{
			CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_SLOW);
		}
		break;
	case CYBLE_EVT_GATT_CONNECT_IND:
	{
		/* Register service specific callback functions and init CCCD values */
		CYBLE_GATT_DB_ATTR_HANDLE_T handle = cyBle_customs[0].customServiceInfo[0].customServiceCharHandle;
		CyBle_GattsEnableAttribute(handle);
	}
		break;
	case CYBLE_EVT_GAP_ENCRYPT_CHANGE:
		break;
	case CYBLE_EVT_GAP_KEYINFO_EXCHNGE_CMPLT:
		break;
	case CYBLE_EVT_GATT_DISCONNECT_IND:
		break;

	case CYBLE_EVT_GAP_PASSKEY_DISPLAY_REQUEST:
		break;
	case CYBLE_EVT_GAP_AUTH_FAILED:
		break;
	case CYBLE_EVT_GATTS_WRITE_REQ:
		// Write request
		{
			CYBLE_GATTS_WRITE_REQ_PARAM_T* param = (CYBLE_GATTS_WRITE_REQ_PARAM_T*)eventParam;
			switch (param->handleValPair.attrHandle)
			{
				case CYBLE_IMU_SERVICE_CUSTOM_CHARACTERISTIC_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE:
				{
					if (param->handleValPair.value.len > 0)
					{
						uint8_t value = *param->handleValPair.value.val;
						isNotificationEnabled = value != 0;
					}
					CyBle_GattsWriteAttributeValue(&param->handleValPair, 0, &param->connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
					CyBle_GattsWriteRsp(param->connHandle);
				}
				break;
				case CYBLE_IMU_SERVICE_UPDATE_INTERVAL_CHAR_HANDLE:
				{
					if (param->handleValPair.value.len >= 2)
					{
						uint16_t value = *(param->handleValPair.value.val + 0) | (*(param->handleValPair.value.val + 1) << 8);
						if( 5 <= value && value <= 8000)
						{
							Timer_Sampling_WritePeriod(value-1);
						}
						*(param->handleValPair.value.val + 0) = value & 0xff;
						*(param->handleValPair.value.val + 1) = value >> 8;
						CyBle_GattsWriteAttributeValue(&param->handleValPair, 0, &param->connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
					}
					CyBle_GattsWriteRsp(param->connHandle);
					
				}
				break;
			}
		}
		break;
	case CYBLE_EVT_HCI_STATUS:
		break;
	
	default:
		break;
	}
}

int main()
{
	// Initialize sampled data
	{
		SampledOutput zero = { {0,}, {0, }, {{0,} } };
		sampledOutput = zero;
	}

	// Enable reset switch interrupt
    ISR_Switch_StartEx(SwitchInterruptHandler);
    
    // Initialize SPI controllers
	IMU::initialize();
	WRA::initialize();
    
	// Start samplling timer
	ISR_SampleOutput_StartEx(SamplingInterruptHandler);
	Timer_Sampling_Init();
	Timer_Sampling_WritePeriod(500-1);
	Timer_Sampling_Enable();
	
    CyGlobalIntEnable; /* Enable global interrupts. */

	// Identify the IMU sensor.
	volatile auto gyroIdentity = IMU::identifyGyro();
	volatile auto magnetoIdentity = IMU::identifyMagnetometer();
    volatile auto wraIdentity = WRA::identify();
    
    // Enable IMU outputs
    IMU::enableGyro();
	IMU::enableMagnetometer();
    
    // Enable WRA outputs
    WRA::enable();
    
	// Start BLE
	CyBle_Start(BleCallback);

	bool canEnterToDeepSleep = false;
	uint8 valueBuffer[40];

    for(;;)
    {
		CyBle_ProcessEvents();
		CyBle_EnterLPM(CYBLE_BLESS_DEEPSLEEP);

		if (CyBle_GetState() == CYBLE_STATE_CONNECTED)
		{
			if (hasNewData)
			{
				hasNewData = false;

				uint8_t* p = valueBuffer;
				*(p++) = 0;
				SampledOutput sampled = sampledOutput;
				p = putImuOutputToBuffer(p, sampled.gyro);
				p = putImuOutputToBuffer(p, sampled.magnetometer);
				p = putImuOutputToBuffer(p, sampled.accelerometer[0]);
				p = putImuOutputToBuffer(p, sampled.accelerometer[1]);
				p = putImuOutputToBuffer(p, sampled.wra[0]);
				p = putImuOutputToBuffer(p, sampled.wra[1]);
				size_t length = p - valueBuffer;

				CYBLE_GATT_DB_ATTR_HANDLE_T handle = cyBle_customs[0].customServiceInfo[0].customServiceCharHandle;
				CYBLE_GATTS_HANDLE_VALUE_NTF_T pair = {
					{ valueBuffer, length, length },
					handle,
				};
				CyBle_GattsWriteAttributeValue(&pair, 0, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
				if (isNotificationEnabled)
				{
					CyBle_GattsNotification(cyBle_connHandle, &pair);
				}
			}
			canEnterToDeepSleep = true;
		}
		else
		{
			// Not connected. The system should enter to deepsleep.
			canEnterToDeepSleep = true;
		}

		// Update alive LED output
		if( aliveLedBlinkCounter >= ALIVE_LED_BLINK_INTERVAL )
		{
			aliveLedBlinkCounter = 0;
			ledOutput ^= LED_ALIVE;
		}
		else
		{
			aliveLedBlinkCounter++;
		}

		// Update LED
		Pin_LED_Write(ledOutput);

		uint8 intrStatus = CyEnterCriticalSection();
		CySysPmSleep();
		CyExitCriticalSection(intrStatus);
    }
}

/* [] END OF FILE */
