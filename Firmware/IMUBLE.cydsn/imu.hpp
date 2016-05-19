#ifndef IMU_HPP__
#define IMU_HPP__

#include <stdint.h>

struct ImuOutput
{
	uint16_t x;
	uint16_t y;
	uint16_t z;
};

#endif //IMU_HPP__
