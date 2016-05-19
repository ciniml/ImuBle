#include "lsm9ds0.hpp"
#include "project.hpp"


template<typename TCallback>
struct IOAccessPolicy
{
	static constexpr uint32 SS_GYRO = SPI_LSM9DS0_SPI_SLAVE_SELECT0;
	static constexpr uint32 SS_MAGNETO = SPI_LSM9DS0_SPI_SLAVE_SELECT1;

	static void onInitialized()
	{
		SPI_LSM9DS0_Start();
		SPI_LSM9DS0_DisableInt();
	}
	static void selectGyro()
	{
		SPI_LSM9DS0_SpiSetActiveSlaveSelect(SS_GYRO);
	}
	static void selectMagnetometer()
	{
		SPI_LSM9DS0_SpiSetActiveSlaveSelect(SS_MAGNETO);
	}
	static void exchangeData(uint8_t* buffer, size_t length)
	{
		SPI_LSM9DS0_SpiUartPutArray(buffer, length);
		for (; length > 0; --length, ++buffer)
		{
			*buffer = SPI_LSM9DS0_SpiUartReadRxData();
		}
	}

	static void dataReadyHandler()
	{
		ISR_LSM_DRDY_G_ClearPending();
		TCallback::onDataReady();
	}
	static void enableDataReadyInt()
	{
		ISR_LSM_DRDY_G_StartEx(dataReadyHandler);
	}
	static void disableDataReadyInt()
	{
	}
};

