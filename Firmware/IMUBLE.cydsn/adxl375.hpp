#ifndef ADXL375_HPP__
#define ADXL375_HPP__

#include <stdint.h>
#include "imu.hpp"

template< template<class> class TIOAccessPolicy >
class ADXL375
{
private:
	typedef ADXL375<TIOAccessPolicy> SelfType;
	typedef TIOAccessPolicy<SelfType> IOAccessPolicy;

	struct Reg
	{
		static constexpr uint_least8_t DEVID = 0x00;
		static constexpr uint_least8_t OFSX = 0x1e;
		static constexpr uint_least8_t OFSY = 0x1f;
		static constexpr uint_least8_t OFSZ = 0x20;
		static constexpr uint_least8_t BW_RATE = 0x2c;
		static constexpr uint_least8_t POWER_CTL = 0x2d;
		static constexpr uint_least8_t INT_ENABLE = 0x2e;
		static constexpr uint_least8_t INT_MAP = 0x2f;
		static constexpr uint_least8_t INT_SOURCE = 0x30;
		static constexpr uint_least8_t DATA_FORMAT = 0x31;
		static constexpr uint_least8_t DATAX0 = 0x32;
		static constexpr uint_least8_t DATAX1 = 0x33;
		static constexpr uint_least8_t DATAY0 = 0x34;
		static constexpr uint_least8_t DATAY1 = 0x35;
		static constexpr uint_least8_t DATAZ0 = 0x36;
		static constexpr uint_least8_t DATAZ1 = 0x37;
		static constexpr uint_least8_t FIFO_CTL = 0x38;
		static constexpr uint_least8_t FIFO_STATUS = 0x39;

		static constexpr uint_least8_t BW_RATE_LOW_POWER = 4;
		static constexpr uint_least8_t BW_RATE_D_BIT = 0;
		static constexpr uint_least8_t BW_RATE_D_3200_HZ = 0xfu<<BW_RATE_D_BIT;
		static constexpr uint_least8_t BW_RATE_D_1600_HZ = 0xeu << BW_RATE_D_BIT;
		static constexpr uint_least8_t BW_RATE_D_800_HZ = 0xdu << BW_RATE_D_BIT;
		static constexpr uint_least8_t BW_RATE_D_400_HZ = 0xcu << BW_RATE_D_BIT;
		static constexpr uint_least8_t BW_RATE_D_200_HZ = 0xbu << BW_RATE_D_BIT;
		static constexpr uint_least8_t BW_RATE_D_100_HZ = 0xau << BW_RATE_D_BIT;
		static constexpr uint_least8_t BW_RATE_D_50_HZ = 0x9u << BW_RATE_D_BIT;
		static constexpr uint_least8_t BW_RATE_D_25_HZ = 0x8u << BW_RATE_D_BIT;
		static constexpr uint_least8_t BW_RATE_D_12_5_HZ = 0x7u << BW_RATE_D_BIT;
		static constexpr uint_least8_t BW_RATE_D_6_25_HZ = 0x6u << BW_RATE_D_BIT;
		static constexpr uint_least8_t BW_RATE_D_3_13_HZ = 0x5u<<BW_RATE_D_BIT;
		static constexpr uint_least8_t BW_RATE_D_1_56_HZ = 0x4u<<BW_RATE_D_BIT;
		static constexpr uint_least8_t BW_RATE_D_0_78_HZ = 0x3u<<BW_RATE_D_BIT;
		static constexpr uint_least8_t BW_RATE_D_0_30_HZ = 0x2u<<BW_RATE_D_BIT;
		static constexpr uint_least8_t BW_RATE_D_0_20_HZ = 0x1u<<BW_RATE_D_BIT;
		static constexpr uint_least8_t BW_RATE_D_0_10_HZ = 0x0u<<BW_RATE_D_BIT;

		static constexpr uint_least8_t POWER_CTL_LINK = 1u << 5;
		static constexpr uint_least8_t POWER_CTL_AUTO_SLEEP = 1u << 4;
		static constexpr uint_least8_t POWER_CTL_MEASURE = 1u << 3;
		static constexpr uint_least8_t POWER_CTL_SLEEP = 1u << 2;
		static constexpr uint_least8_t POWER_CTL_WAKE_BIT = 0;

		static constexpr uint_least8_t POWER_CTL_WAKE_8_HZ = 0u << POWER_CTL_WAKE_BIT;
		static constexpr uint_least8_t POWER_CTL_WAKE_4_HZ = 1u << POWER_CTL_WAKE_BIT;
		static constexpr uint_least8_t POWER_CTL_WAKE_2_HZ = 2u << POWER_CTL_WAKE_BIT;
		static constexpr uint_least8_t POWER_CTL_WAKE_1_HZ = 3u << POWER_CTL_WAKE_BIT;

		static constexpr uint_least8_t INT_ENABLE_DATA_READY = 1u << 7;
		static constexpr uint_least8_t INT_ENABLE_SINGLE_SHOCK = 1u << 6;
		static constexpr uint_least8_t INT_ENABLE_DOUBLE_SHOCK = 1u << 5;
		static constexpr uint_least8_t INT_ENABLE_ACTIVITY = 1u << 4;
		static constexpr uint_least8_t INT_ENABLE_INACTIVITY = 1u << 3;
		static constexpr uint_least8_t INT_ENABLE_WATERMARK = 1u << 1;
		static constexpr uint_least8_t INT_ENABLE_OVERRUN = 1u << 0;

		static constexpr uint_least8_t INT_MAP_DATA_READY = 1u << 7;
		static constexpr uint_least8_t INT_MAP_SINGLE_SHOCK = 1u << 6;
		static constexpr uint_least8_t INT_MAP_DOUBLE_SHOCK = 1u << 5;
		static constexpr uint_least8_t INT_MAP_ACTIVITY = 1u << 4;
		static constexpr uint_least8_t INT_MAP_INACTIVITY = 1u << 3;
		static constexpr uint_least8_t INT_MAP_WATERMARK = 1u << 1;
		static constexpr uint_least8_t INT_MAP_OVERRUN = 1u << 0;

		static constexpr uint_least8_t INT_SOURCE_DATA_READY = 1u << 7;
		static constexpr uint_least8_t INT_SOURCE_SINGLE_SHOCK = 1u << 6;
		static constexpr uint_least8_t INT_SOURCE_DOUBLE_SHOCK = 1u << 5;
		static constexpr uint_least8_t INT_SOURCE_ACTIVITY = 1u << 4;
		static constexpr uint_least8_t INT_SOURCE_INACTIVITY = 1u << 3;
		static constexpr uint_least8_t INT_SOURCE_WATERMARK = 1u << 1;
		static constexpr uint_least8_t INT_SOURCE_OVERRUN = 1u << 0;

		static constexpr uint_least8_t DATA_FORMAT_SELF_TEST = 1u << 7;
		static constexpr uint_least8_t DATA_FORMAT_SPI = 1u << 6;
		static constexpr uint_least8_t DATA_FORMAT_INT_INVERT = 1u << 5;
		static constexpr uint_least8_t DATA_FORMAT_JUSTIFY = 1u << 2;
		static constexpr uint_least8_t DATA_FORMAT_FIXED_BITS = 0x0b;

		static constexpr uint_least8_t FIFO_CTL_FIFO_MODE_BIT = 6;
		static constexpr uint_least8_t FIFO_CTL_TRIGGER = 1u << 5;
		static constexpr uint_least8_t FIFO_CTL_SAMPLES_BIT = 0;
		
		static constexpr uint_least8_t FIFO_CTL_FIFO_MODE_BYPASS  = 0u << FIFO_CTL_FIFO_MODE_BIT;
		static constexpr uint_least8_t FIFO_CTL_FIFO_MODE_FIFO    = 1u << FIFO_CTL_FIFO_MODE_BIT;
		static constexpr uint_least8_t FIFO_CTL_FIFO_MODE_STREAM  = 2u << FIFO_CTL_FIFO_MODE_BIT;
		static constexpr uint_least8_t FIFO_CTL_FIFO_MODE_TRIGGER = 3u << FIFO_CTL_FIFO_MODE_BIT;
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

	static uint_least8_t readSingleRegister(uint_least8_t index)
	{
		IOAccessPolicy::select();
		auto value = readRegister(index);
		IOAccessPolicy::unselect();
		return value;
	}
	static void writeSingleRegister(uint_least8_t index, uint_least8_t value)
	{
		IOAccessPolicy::select();
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

	ADXL375() = delete;
	ADXL375(const ADXL375&) = delete;

	static void initialize()
	{
		IOAccessPolicy::onInitialized();
		IOAccessPolicy::unselect();
	}

	static uint_least8_t identify()
	{
		return readSingleRegister(Reg::DEVID);
	}

	static void enable()
	{
		IOAccessPolicy::disableDataReadyInt();

		writeSingleRegister(Reg::OFSX, 0);
		writeSingleRegister(Reg::OFSY, 0);
		writeSingleRegister(Reg::OFSZ, 0);

		writeSingleRegister(Reg::FIFO_CTL, Reg::FIFO_CTL_FIFO_MODE_BYPASS);

		writeSingleRegister(Reg::INT_MAP, 0);
		writeSingleRegister(Reg::DATA_FORMAT, Reg::DATA_FORMAT_FIXED_BITS);
		writeSingleRegister(Reg::INT_ENABLE, Reg::INT_ENABLE_DATA_READY);

		writeSingleRegister(Reg::BW_RATE, Reg::BW_RATE_D_400_HZ);
		writeSingleRegister(Reg::POWER_CTL, Reg::POWER_CTL_MEASURE);

		IOAccessPolicy::enableDataReadyInt();
	}

	static ImuOutput readOutput()
	{
		IOAccessPolicy::select();
		uint8 buffer[1 + 6] = {0};
		buffer[0] = commandByte(true, true, Reg::DATAX0);
		IOAccessPolicy::exchangeData(buffer, 1 + 6);
		IOAccessPolicy::unselect();

		return toImuOutput(buffer + 1);
	}
	static void onDataReady()
	{
		auto output = readOutput();
		IOAccessPolicy::onDataReady(output);
	}
};

#endif //ADXL375_HPP__
