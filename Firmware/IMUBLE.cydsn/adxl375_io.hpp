#ifndef ADXL375_IO_HPP_
#define ADXL375_IO_HPP_

#include "project.hpp"

template<typename TCallback>
struct ADXL375_IOAccessPolicy
{
	static constexpr uint32 SS_MAIN = SPI_ADX_SPI_SLAVE_SELECT0;
	static constexpr uint32 SS_UNUSED = SPI_ADX_SPI_SLAVE_SELECT3;

	static void onInitialized()
	{
		SPI_ADX_Start();
	}
	static void onDataReady(const ImuOutput& output);;
	
	static void select()
	{
		SPI_ADX_SpiSetActiveSlaveSelect(SS_MAIN);
	}
	static void unselect()
	{
		SPI_ADX_SpiSetActiveSlaveSelect(SS_UNUSED);
	}
	static void exchangeData(uint8_t* buffer, size_t length)
	{
		SPI_ADX_SpiUartClearRxBuffer();
		SPI_ADX_SpiUartClearTxBuffer();
		SPI_ADX_SpiUartPutArray(buffer, length);
		// Wait until last transmission completes.
		while (SPI_ADX_SpiUartGetRxBufferSize() < length);

		for (; length > 0; --length, ++buffer)
		{
			*buffer = SPI_ADX_SpiUartReadRxData();
		}
	}

	static void dataReadyHandler()
	{
		ISR_ADX_INT1_ClearPending();
		TCallback::onDataReady();
	}
	static void enableDataReadyInt()
	{
		ISR_ADX_INT1_StartEx(dataReadyHandler);
	}
	static void disableDataReadyInt()
	{
		ISR_ADX_INT1_Disable();
	}
};

#endif //ADXL375_IO_HPP_

