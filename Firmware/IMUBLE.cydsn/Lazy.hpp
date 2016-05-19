#ifndef LAZY_HPP_
#define LAZY_HPP_

#include "interrupt.hpp"

#include <type_traits>
#include <new>

template<typename TTarget, typename TLock = InterruptLock >
class Lazy
{
private:
	typedef Lazy<TTarget, TLock> SelfType;
	typedef LockGuard<TLock> GuardType;
	typedef TTarget* (SelfType::*EnsureFunction)();
	typedef typename std::aligned_storage<sizeof(TTarget), alignof(TTarget)>::type StorageType;

	EnsureFunction ensureImpl;
	StorageType storage;

	TTarget* ensureGet()
	{
		return reinterpret_cast<TTarget*>(&this->storage);
	}

	TTarget* ensureConstruct()
	{
		GuardType guard;
		this->ensureImpl = &SelfType::ensureGet;
		return new(&this->storage) TTarget();
	}

public:
	Lazy() : ensureImpl(&SelfType::ensureConstruct) {}

	void ensure() { (this->*ensureImpl)(); }
	TTarget& get() { return *(this->*ensureImpl)(); }
	TTarget* operator->() { return (this->*ensureImpl)(); }
};

#endif //LAZY_HPP_
