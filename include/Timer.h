#ifndef TIMER_H
#define TIMER_H

#include <functional>

#include "Stopwatch.h"

namespace tlbx
{

	class Timer
	{
		Stopwatch _stopwatch;
	
		float _time;
		std::function<void()> _func;

	public:
		Timer(float time, const std::function<void()>& func, bool autoStart = false);
		~Timer() = default;

		void start();
		void step();
	};
}

#endif
