#include "Stopwatch.h"

namespace tlbx
{
	Stopwatch::Stopwatch()
	{
		start();
	}

	void Stopwatch::start()
	{
		_start = clock_type::now();
		_end = _start;
	}

	void Stopwatch::stop()
	{
		_end = clock_type::now();
	}
}
