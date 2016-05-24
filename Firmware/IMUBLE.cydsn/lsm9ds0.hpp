#ifndef LSM9DS0_HPP__
#define LSM9DS0_HPP__

#include <stdint.h>
#include "imu.hpp"

template< template<class> class TIOAccessPolicy >
class LSM9DS0
{
private:
	typedef LSM9DS0<TIOAccessPolicy> SelfType;
	typedef TIOAccessPolicy<SelfType> IOAccessPolicy;

	static constexpr uint_least8_t REG_WHO_AMI_I_G = 0x0f;
	static constexpr uint_least8_t REG_CTRL_REG1_G = 0x20;
	static constexpr uint_least8_t REG_CTRL_REG2_G = 0x21;
	static constexpr uint_least8_t REG_CTRL_REG3_G = 0x22;
	static constexpr uint_least8_t REG_CTRL_REG4_G = 0x23;
	static constexpr uint_least8_t REG_CTRL_REG5_G = 0x24;
	static constexpr uint_least8_t REG_REFERENCE_G = 0x25;
	static constexpr uint_least8_t REG_STATUS_REG_G = 0x27;
	static constexpr uint_least8_t REG_OUT_X_L_G = 0x28;
	static constexpr uint_least8_t REG_FIFO_CTRL_REG_G = 0x2e;
	static constexpr uint_least8_t REG_FIFO_SRC_REG_G = 0x2f;

	static constexpr uint_least8_t CTRL_REG1_G_BW_BIT = 4;
	static constexpr uint_least8_t CTRL_REG1_G_DR_BIT = 6;
	static constexpr uint_least8_t CTRL_REG1_G_PD = (1u << 3);
	static constexpr uint_least8_t CTRL_REG1_G_ZEN = (1u << 2);
	static constexpr uint_least8_t CTRL_REG1_G_YEN = (1u << 1);
	static constexpr uint_least8_t CTRL_REG1_G_XEN = (1u << 0);

	static constexpr uint_least8_t CTRL_REG2_G_HPM_BIT = 4;
	static constexpr uint_least8_t CTRL_REG2_G_HPCF_BIT = 0;

	static constexpr uint_least8_t CTRL_REG3_G_I1_INT1 = (1u << 7);
	static constexpr uint_least8_t CTRL_REG3_G_I1_BOOT = (1u << 6);
	static constexpr uint_least8_t CTRL_REG3_G_H_LACTIVE = (1u << 5);
	static constexpr uint_least8_t CTRL_REG3_G_PP_OD = (1u << 4);
	static constexpr uint_least8_t CTRL_REG3_G_I2_DRDY = (1u << 3);
	static constexpr uint_least8_t CTRL_REG3_G_I2_WTM = (1u << 2);
	static constexpr uint_least8_t CTRL_REG3_G_I2_ORUN = (1u << 1);
	static constexpr uint_least8_t CTRL_REG3_G_I2_EMPTY = (1u << 0);

	static constexpr uint_least8_t CTRL_REG4_G_BDU = (1u << 7);
	static constexpr uint_least8_t CTRL_REG4_G_BLE = (1u << 6);
	static constexpr uint_least8_t CTRL_REG4_G_SIM = (1u << 0);
	static constexpr uint_least8_t CTRL_REG4_G_FS_BIT = 4;
	static constexpr uint_least8_t CTRL_REG4_G_ST_BIT = 1;

	static constexpr uint_least8_t CTRL_REG5_G_BOOT = (1u << 7);
	static constexpr uint_least8_t CTRL_REG5_G_FIFO_EN = (1u << 6);
	static constexpr uint_least8_t CTRL_REG5_G_HPEN = (1u << 4);
	static constexpr uint_least8_t CTRL_REG5_G_INT1_SEL_BIT = 2;
	static constexpr uint_least8_t CTRL_REG5_G_OUT_SEL_BIT = 0;

	static constexpr uint_least8_t CTRL_REG5_G_OUT_SEL_LPF1 = (0u << CTRL_REG5_G_OUT_SEL_BIT);
	static constexpr uint_least8_t CTRL_REG5_G_OUT_SEL_HPF = (1u << CTRL_REG5_G_OUT_SEL_BIT);
	static constexpr uint_least8_t CTRL_REG5_G_OUT_SEL_LPF2 = (2u << CTRL_REG5_G_OUT_SEL_BIT);

	static constexpr uint_least8_t FIFO_CTRL_REG_G_FM_BIT = 5;
	static constexpr uint_least8_t FIFO_CTRL_REG_G_WTM_BIT = 0;
	static constexpr uint_least8_t FIFO_CTRL_REG_G_FM_BYPASS = (0 << FIFO_CTRL_REG_G_FM_BIT);
	static constexpr uint_least8_t FIFO_CTRL_REG_G_FM_FIFO = (1 << FIFO_CTRL_REG_G_FM_BIT);
	static constexpr uint_least8_t FIFO_CTRL_REG_G_FM_STREAM = (2 << FIFO_CTRL_REG_G_FM_BIT);
	static constexpr uint_least8_t FIFO_CTRL_REG_G_FM_STREAM_TO_FIFO = (3 << FIFO_CTRL_REG_G_FM_BIT);
	static constexpr uint_least8_t FIFO_CTRL_REG_G_FM_BYPASS_TO_STREAM = (4 << FIFO_CTRL_REG_G_FM_BIT);

	struct RegMA
	{
		static constexpr uint_least8_t OUT_TEMP_L_XM = 0x05;
		static constexpr uint_least8_t STATUS_REG_M = 0x06;
		static constexpr uint_least8_t OUT_X_L_M = 0x07;
		static constexpr uint_least8_t WHO_AM_I_XM = 0x0f;
		static constexpr uint_least8_t INT_CTRL_REG_M = 0x12;
		static constexpr uint_least8_t INT_SRC_REG_M = 0x12;
		static constexpr uint_least8_t CTRL_REG0_XM = 0x1f;
		static constexpr uint_least8_t CTRL_REG1_XM = 0x20;
		static constexpr uint_least8_t CTRL_REG2_XM = 0x21;
		static constexpr uint_least8_t CTRL_REG3_XM = 0x22;
		static constexpr uint_least8_t CTRL_REG4_XM = 0x23;
		static constexpr uint_least8_t CTRL_REG5_XM = 0x24;
		static constexpr uint_least8_t CTRL_REG6_XM = 0x25;
		static constexpr uint_least8_t CTRL_REG7_XM = 0x26;
		static constexpr uint_least8_t OUT_X_L_A = 0x28;
		static constexpr uint_least8_t FIFO_CTRL_REG = 0x2e;
		static constexpr uint_least8_t FIFO_SRC_REG = 0x2f;

		static constexpr uint_least8_t CTRL_REG0_XM_BOOT = (1u << 7);
		static constexpr uint_least8_t CTRL_REG0_XM_FIFO_EN = (1u << 6);
		static constexpr uint_least8_t CTRL_REG0_XM_WTM_EN = (1u << 5);
		static constexpr uint_least8_t CTRL_REG0_XM_HP_CLICK = (1u << 2);
		static constexpr uint_least8_t CTRL_REG0_XM_HPIS1 = (1u << 1);
		static constexpr uint_least8_t CTRL_REG0_XM_HPIS2 = (1u << 0);

		static constexpr uint_least8_t CTRL_REG1_AODR_BIT = 4;
		static constexpr uint_least8_t CTRL_REG1_AODR_POWER_DOWN = (0x0 << CTRL_REG1_AODR_BIT);
		static constexpr uint_least8_t CTRL_REG1_AODR_3_125_HZ = (0x1 << CTRL_REG1_AODR_BIT);
		static constexpr uint_least8_t CTRL_REG1_AODR_6_25_HZ = (0x2 << CTRL_REG1_AODR_BIT);
		static constexpr uint_least8_t CTRL_REG1_AODR_12_5_HZ = (0x3 << CTRL_REG1_AODR_BIT);
		static constexpr uint_least8_t CTRL_REG1_AODR_25_HZ = (0x4 << CTRL_REG1_AODR_BIT);
		static constexpr uint_least8_t CTRL_REG1_AODR_50_HZ = (0x5 << CTRL_REG1_AODR_BIT);
		static constexpr uint_least8_t CTRL_REG1_AODR_100_HZ = (0x6 << CTRL_REG1_AODR_BIT);
		static constexpr uint_least8_t CTRL_REG1_AODR_200_HZ = (0x7 << CTRL_REG1_AODR_BIT);
		static constexpr uint_least8_t CTRL_REG1_AODR_400_HZ = (0x8 << CTRL_REG1_AODR_BIT);
		static constexpr uint_least8_t CTRL_REG1_AODR_800_HZ = (0x9 << CTRL_REG1_AODR_BIT);
		static constexpr uint_least8_t CTRL_REG1_AODR_1600_HZ = (0xa << CTRL_REG1_AODR_BIT);
		static constexpr uint_least8_t CTRL_REG1_BDU = (1u << 3);
		static constexpr uint_least8_t CTRL_REG1_AZEN = (1u << 2);
		static constexpr uint_least8_t CTRL_REG1_AYEN = (1u << 1);
		static constexpr uint_least8_t CTRL_REG1_AXEN = (1u << 0);

		static constexpr uint_least8_t CTRL_REG2_ABW_BIT = 6;
		static constexpr uint_least8_t CTRL_REG2_ABW_773_HZ = (0u << CTRL_REG2_ABW_BIT);
		static constexpr uint_least8_t CTRL_REG2_ABW_194_HZ = (1u << CTRL_REG2_ABW_BIT);
		static constexpr uint_least8_t CTRL_REG2_ABW_362_HZ = (2u << CTRL_REG2_ABW_BIT);
		static constexpr uint_least8_t CTRL_REG2_ABW_50_HZ = (3u << CTRL_REG2_ABW_BIT);

		static constexpr uint_least8_t CTRL_REG2_AFS_BIT = 3;
		static constexpr uint_least8_t CTRL_REG2_AFS_2G = (0u << CTRL_REG2_AFS_BIT);
		static constexpr uint_least8_t CTRL_REG2_AFS_4G = (1u << CTRL_REG2_AFS_BIT);
		static constexpr uint_least8_t CTRL_REG2_AFS_6G = (2u << CTRL_REG2_AFS_BIT);
		static constexpr uint_least8_t CTRL_REG2_AFS_8G = (3u << CTRL_REG2_AFS_BIT);
		static constexpr uint_least8_t CTRL_REG2_AFS_16G = (4u << CTRL_REG2_AFS_BIT);

		static constexpr uint_least8_t CTRL_REG2_AST_BIT = 1;
		static constexpr uint_least8_t CTRL_REG2_AST_NORMAL = (0u << CTRL_REG2_AST_BIT);
		static constexpr uint_least8_t CTRL_REG2_AST_POSITIVE_SIGN = (1u << CTRL_REG2_AST_BIT);
		static constexpr uint_least8_t CTRL_REG2_AST_NEGATIVE_SIGN = (2u << CTRL_REG2_AST_BIT);

		static constexpr uint_least8_t CTRL_REG3_P1_BOOT = (1u << 7);
		static constexpr uint_least8_t CTRL_REG3_P1_TAP = (1u << 6);
		static constexpr uint_least8_t CTRL_REG3_P1_INT1 = (1u << 5);
		static constexpr uint_least8_t CTRL_REG3_P1_INT2 = (1u << 4);
		static constexpr uint_least8_t CTRL_REG3_P1_INTM = (1u << 3);
		static constexpr uint_least8_t CTRL_REG3_P1_DRDYA = (1u << 2);
		static constexpr uint_least8_t CTRL_REG3_P1_DRDYM = (1u << 1);
		static constexpr uint_least8_t CTRL_REG3_P1_EMPTY = (1u << 0);

		static constexpr uint_least8_t CTRL_REG4_P2_TAP = (1u << 7);
		static constexpr uint_least8_t CTRL_REG4_P2_INT1 = (1u << 6);
		static constexpr uint_least8_t CTRL_REG4_P2_INT2 = (1u << 5);
		static constexpr uint_least8_t CTRL_REG4_P2_INTM = (1u << 4);
		static constexpr uint_least8_t CTRL_REG4_P2_DRDYA = (1u << 3);
		static constexpr uint_least8_t CTRL_REG4_P2_DRDYM = (1u << 2);
		static constexpr uint_least8_t CTRL_REG4_P2_OVERRUN = (1u << 1);
		static constexpr uint_least8_t CTRL_REG4_P2_WTM = (1u << 0);

		static constexpr uint_least8_t CTRL_REG5_TEMP_EN = (1u << 7);
		static constexpr uint_least8_t CTRL_REG5_M_RES_BIT = 5;
		static constexpr uint_least8_t CTRL_REG5_M_ODR_BIT = 2;
		static constexpr uint_least8_t CTRL_REG5_LIR2 = (1u << 1);
		static constexpr uint_least8_t CTRL_REG5_LIR1 = (1u << 0);

		static constexpr uint_least8_t CTRL_REG5_M_RES_LOW = (0u << CTRL_REG5_M_RES_BIT);
		static constexpr uint_least8_t CTRL_REG5_M_RES_HIGH = (3u << CTRL_REG5_M_RES_BIT);
		
		static constexpr uint_least8_t CTRL_REG5_M_ODR_3_125_HZ = (0u << CTRL_REG5_M_ODR_BIT);
		static constexpr uint_least8_t CTRL_REG5_M_ODR_6_25_HZ = (1u << CTRL_REG5_M_ODR_BIT);
		static constexpr uint_least8_t CTRL_REG5_M_ODR_12_5_HZ = (2u << CTRL_REG5_M_ODR_BIT);
		static constexpr uint_least8_t CTRL_REG5_M_ODR_25_HZ = (3u << CTRL_REG5_M_ODR_BIT);
		static constexpr uint_least8_t CTRL_REG5_M_ODR_50_HZ = (4u << CTRL_REG5_M_ODR_BIT);
		static constexpr uint_least8_t CTRL_REG5_M_ODR_100_HZ = (5u << CTRL_REG5_M_ODR_BIT);

		static constexpr uint_least8_t CTRL_REG6_MFS_BIT = 6;
		static constexpr uint_least8_t CTRL_REG6_MFS_2_GAUSS = (0u << CTRL_REG6_MFS_BIT);
		static constexpr uint_least8_t CTRL_REG6_MFS_4_GAUSS = (1u << CTRL_REG6_MFS_BIT);
		static constexpr uint_least8_t CTRL_REG6_MFS_8_GAUSS = (2u << CTRL_REG6_MFS_BIT);
		static constexpr uint_least8_t CTRL_REG6_MFS_12_GAUSS = (3u << CTRL_REG6_MFS_BIT);

		static constexpr uint_least8_t CTRL_REG7_AHPM_BIT = 6;
		static constexpr uint_least8_t CTRL_REG7_AFDS = (1u << 5);
		static constexpr uint_least8_t CTRL_REG7_MLP = (1u << 2);
		static constexpr uint_least8_t CTRL_REG7_MD_BIT = 0;

		static constexpr uint_least8_t CTRL_REG7_AHPM_NORMAL_RESET = (0u << CTRL_REG7_AHPM_BIT);
		static constexpr uint_least8_t CTRL_REG7_AHPM_REFERENCE = (1u << CTRL_REG7_AHPM_BIT);
		static constexpr uint_least8_t CTRL_REG7_AHPM_NORMAL = (2u << CTRL_REG7_AHPM_BIT);
		static constexpr uint_least8_t CTRL_REG7_AHPM_AUTORESET = (3u << CTRL_REG7_AHPM_BIT);

		static constexpr uint_least8_t CTRL_REG7_MD_CONTINUOUS = (0u << CTRL_REG7_MD_BIT);
		static constexpr uint_least8_t CTRL_REG7_MD_SINGLE = (1u << CTRL_REG7_MD_BIT);
		static constexpr uint_least8_t CTRL_REG7_MD_POWERDOWN1 = (2u << CTRL_REG7_MD_BIT);
		static constexpr uint_least8_t CTRL_REG7_MD_POWERDOWN2 = (3u << CTRL_REG7_MD_BIT);


	};

	static constexpr uint_least8_t commandByte(bool isRead, bool incrementAddress, uint_least8_t address)
	{
		return (isRead ? 0x80 : 0x00) | (incrementAddress ? 0x40 : 0x00) | (address & 0x3f);
	}

	static uint_least8_t readRegister(uint_least8_t index)
	{
		uint8 buffer[2] = { 0 };
		buffer[0] = commandByte(true, false, index);
		IOAccessPolicy::exchangeData(buffer, 2);
		return buffer[1];
	}
	static void writeRegister(uint_least8_t index, uint_least8_t value)
	{
		uint8 buffer[2] = { 0 };
		buffer[0] = commandByte(false, false, index);
		buffer[1] = value & 0xff;
		IOAccessPolicy::exchangeData(buffer, 2);
	}

	static uint_least8_t readGyroRegister(uint_least8_t index)
	{
		IOAccessPolicy::selectGyro();
		auto value = readRegister(index);
		IOAccessPolicy::unselect();
		return value;
	}
	static void writeGyroRegister(uint_least8_t index, uint_least8_t value)
	{
		IOAccessPolicy::selectGyro();
		writeRegister(index, value);
		IOAccessPolicy::unselect();
	}

	static uint_least8_t readMagnetoRegister(uint_least8_t index)
	{
		IOAccessPolicy::selectMagnetometer();
		auto value = readRegister(index);
		IOAccessPolicy::unselect();
		return value;
	}
	static void writeMagnetoRegister(uint_least8_t index, uint_least8_t value)
	{
		IOAccessPolicy::selectMagnetometer();
		writeRegister(index, value);
		IOAccessPolicy::unselect();
	}
	static ImuOutput toImuOutput(const uint8_t* buffer)
	{
		ImuOutput output;
		output.x = (buffer[1] << 8) | (buffer[0] << 0);
		output.y = (buffer[3] << 8) | (buffer[2] << 0);
		output.z = (buffer[5] << 8) | (buffer[4] << 0);
		return output;
	}
public:
	typedef IOAccessPolicy AccessPolicyType;

	LSM9DS0() = delete;
	LSM9DS0(const LSM9DS0&) = delete;

	static void initialize()
	{
		IOAccessPolicy::onInitialized();
		IOAccessPolicy::unselect();
	}

	static uint_least8_t identifyGyro()
	{
		return readGyroRegister(REG_WHO_AMI_I_G);
	}

	static void enableGyro()
	{
		IOAccessPolicy::disableGyroDataReadyInt();

		writeGyroRegister(REG_CTRL_REG1_G, (3 << CTRL_REG1_G_DR_BIT) | (3 << CTRL_REG1_G_BW_BIT) | CTRL_REG1_G_PD | CTRL_REG1_G_ZEN | CTRL_REG1_G_YEN | CTRL_REG1_G_XEN);
		writeGyroRegister(REG_CTRL_REG2_G, (0 << CTRL_REG2_G_HPM_BIT) | (0 << CTRL_REG2_G_HPCF_BIT));
		writeGyroRegister(REG_CTRL_REG3_G, CTRL_REG3_G_I2_DRDY);
		writeGyroRegister(REG_CTRL_REG4_G, (3 << CTRL_REG4_G_FS_BIT));
		writeGyroRegister(REG_CTRL_REG5_G, CTRL_REG5_G_OUT_SEL_HPF);
		writeGyroRegister(REG_FIFO_CTRL_REG_G, FIFO_CTRL_REG_G_FM_BYPASS);	// Disable FIFO.

		IOAccessPolicy::enableGyroDataReadyInt();
	}

	static ImuOutput readGyroOutput()
	{
		IOAccessPolicy::selectGyro();
		uint8 buffer[1 + 6] = {0};
		buffer[0] = commandByte(true, true, REG_OUT_X_L_G);
		IOAccessPolicy::exchangeData(buffer, 1 + 6);
		IOAccessPolicy::unselect();

		return toImuOutput(buffer + 1);
	}
	static void onGyroDataReady()
	{
		auto output = readGyroOutput();
		IOAccessPolicy::onGyroDataReady(output);
	}

	static uint_least8_t identifyMagnetometer()
	{
		return readMagnetoRegister(RegMA::WHO_AM_I_XM);
	}

	static void enableMagnetometer()
	{
		IOAccessPolicy::disableMagnetometerDataReadyInt();
		IOAccessPolicy::disableAccelerometerDataReadyInt();

		writeMagnetoRegister(RegMA::CTRL_REG0_XM, 0);
		writeMagnetoRegister(RegMA::CTRL_REG1_XM, RegMA::CTRL_REG1_AODR_1600_HZ | RegMA::CTRL_REG1_AZEN | RegMA::CTRL_REG1_AYEN | RegMA::CTRL_REG1_AXEN);
		writeMagnetoRegister(RegMA::CTRL_REG2_XM, RegMA::CTRL_REG2_ABW_773_HZ | RegMA::CTRL_REG2_AFS_16G | RegMA::CTRL_REG2_AST_NORMAL);
		writeMagnetoRegister(RegMA::CTRL_REG3_XM, RegMA::CTRL_REG3_P1_DRDYM);
		writeMagnetoRegister(RegMA::CTRL_REG4_XM, RegMA::CTRL_REG4_P2_DRDYA);
		writeMagnetoRegister(RegMA::CTRL_REG5_XM, RegMA::CTRL_REG5_TEMP_EN | RegMA::CTRL_REG5_M_RES_HIGH | RegMA::CTRL_REG5_M_ODR_100_HZ);
		writeMagnetoRegister(RegMA::CTRL_REG6_XM, RegMA::CTRL_REG6_MFS_12_GAUSS);
		writeMagnetoRegister(RegMA::CTRL_REG7_XM, RegMA::CTRL_REG7_AHPM_NORMAL_RESET | RegMA::CTRL_REG7_MD_CONTINUOUS);

		IOAccessPolicy::enableAccelerometerDataReadyInt();
		IOAccessPolicy::enableMagnetometerDataReadyInt();
	}

	static ImuOutput readAccelerometerOutput()
	{
		IOAccessPolicy::selectMagnetometer();
		uint8 buffer[1 + 6] = { 0 };
		buffer[0] = commandByte(true, true, RegMA::OUT_X_L_A);
		IOAccessPolicy::exchangeData(buffer, 1 + 6);
		IOAccessPolicy::unselect();
        
        return toImuOutput(buffer + 1);
	}
	static void onAccelerometerDataReady()
	{
		auto output = readAccelerometerOutput();
		IOAccessPolicy::onAccelerometerDataReady(output);
	}

	static ImuOutput readMagnetometerOutput()
	{
		IOAccessPolicy::selectMagnetometer();
		uint8 buffer[1 + 6] = { 0 };
		buffer[0] = commandByte(true, true, RegMA::OUT_X_L_M);
		IOAccessPolicy::exchangeData(buffer, 1 + 6);
		IOAccessPolicy::unselect();
        
        return toImuOutput(buffer + 1);
	}
	static void onMagnetometerDataReady()
	{
		auto output = readMagnetometerOutput();
		IOAccessPolicy::onMagnetometerDataReady(output);
	}
};

#endif //LSM9DS0_HPP__
