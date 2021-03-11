#include "Timer.h"

namespace tlbx
{
	Timer::Timer()
	{
		start();
	}

	void Timer::start()
	{
		_start = clock_type::now();
		_end = _start;
	}

	void Timer::stop()
	{
		_end = clock_type::now();
	}
}
