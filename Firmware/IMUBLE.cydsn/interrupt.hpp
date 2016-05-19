#ifndef INTERRUPT_HPP_
#define	INTERRUPT_HPP_

extern "C" {
#include <CyLib.h>
}
#include <stdint.h>

class InterruptLock
{
private:
	uint32_t mask;

public:
	InterruptLock() : mask(0) {}

	void enter()
	{
		this->mask = CyDisableInts();
	}

	void leave() const
	{
		CyEnableInts(this->mask);
	}
};

template<class TLock> 
class LockGuard
{
private:
	TLock lock;

public:
	LockGuard()
	{
		this->lock.enter();
	}
	~LockGuard()
	{
		this->lock.leave();
	}
};

#endif //INTERRUPT_HPP_

