#ifndef LSM9DS0_IO_HPP_
#define LSM9DS0_IO_HPP_

#include "project.hpp"

template<typename TCallback>
struct LSM9DS0_IOAccessPolicy
{
	static constexpr uint32 SS_GYRO = SPI_LSM9DS0_SPI_SLAVE_SELECT0;
	static constexpr uint32 SS_MAGNETO = SPI_LSM9DS0_SPI_SLAVE_SELECT1;
	static constexpr uint32 SS_UNUSED = SPI_LSM9DS0_SPI_SLAVE_SELECT3;

	static void onInitialized()
	{
		SPI_LSM9DS0_Start();
	}
	static void onGyroDataReady(const ImuOutput& output);
	static void onMagnetometerDataReady(const ImuOutput& output);
	static void onAccelerometerDataReady(const ImuOutput& output);
	
	static void selectGyro()
	{
		SPI_LSM9DS0_SpiSetActiveSlaveSelect(SS_GYRO);
	}
	static void selectMagnetometer()
	{
		SPI_LSM9DS0_SpiSetActiveSlaveSelect(SS_MAGNETO);
	}
	static void unselect()
	{
		SPI_LSM9DS0_SpiSetActiveSlaveSelect(SS_UNUSED);
	}
	static void exchangeData(uint8_t* buffer, size_t length)
	{
		SPI_LSM9DS0_SpiUartClearRxBuffer();
		SPI_LSM9DS0_SpiUartClearTxBuffer();
		SPI_LSM9DS0_SpiUartPutArray(buffer, length);
		// Wait until last transmission completes.
		while (SPI_LSM9DS0_SpiUartGetRxBufferSize() < length);

		for (; length > 0; --length, ++buffer)
		{
			*buffer = SPI_LSM9DS0_SpiUartReadRxData();
		}
	}

	static void dataReadyHandler_Gyro()
	{
		ISR_LSM_DRDY_G_ClearPending();
		TCallback::onGyroDataReady();
	}
	static void enableGyroDataReadyInt()
	{
		ISR_LSM_DRDY_G_StartEx(dataReadyHandler_Gyro);
	}
	static void disableGyroDataReadyInt()
	{
		ISR_LSM_DRDY_G_Disable();
	}

	static void dataReadyHandler_Magnetometer()
	{
		ISR_LSM_INT1_ClearPending();
		TCallback::onMagnetometerDataReady();
	}
	static void enableMagnetometerDataReadyInt()
	{
		ISR_LSM_INT1_StartEx(dataReadyHandler_Magnetometer);
	}
	static void disableMagnetometerDataReadyInt()
	{
		ISR_LSM_INT1_Disable();
	}

	static void dataReadyHandler_Accelerometer()
	{
		ISR_LSM_INT2_ClearPending();
		TCallback::onAccelerometerDataReady();
	}
	static void enableAccelerometerDataReadyInt()
	{
		ISR_LSM_INT2_StartEx(dataReadyHandler_Accelerometer);
	}
	static void disableAccelerometerDataReadyInt()
	{
		ISR_LSM_INT2_Disable();
	}
};

#endif //LSM9DS0_IO_HPP_

