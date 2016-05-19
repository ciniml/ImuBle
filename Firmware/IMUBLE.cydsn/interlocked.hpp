#ifndef INTERLOCKED_HPP_
#define INTERLOCKED_HPP_

template<typename TValue, typename TInterlockPolicy>
class InterlockedAccess
{
private:
	struct ReadGuard
	{
		ReadGuard() { TInterlockPolicy::enterRead(); }
		~ReadGuard() { TInterlockPolicy::leaveRead(); }
	};
	struct WriteGuard
	{
		WriteGuard() { TInterlockPolicy::enterWrite(); }
		~WriteGuard() { TInterlockPolicy::leaveWrite(); }
	};

	TValue value;
public:
	InterlockedAccess() : value() {}
	explicit InterlockedAccess(const TValue& value) : value(value) {}

	void assign(const TValue& value) { WriteGuard guard; this->value = value; }
	void assign(const TValue& value) volatile { WriteGuard guard; this->value = value; }
	operator TValue() const { ReadGuard guard; return this->value; }
	const TValue& operator=(const TValue& value) { this->assign(value); return value; }
	const TValue& operator=(const TValue& value) volatile { this->assign(value); return value; }
};

#endif //INTERLOCKED_HPP_

