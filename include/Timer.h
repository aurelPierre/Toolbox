#ifndef TIMER_H
#define TIMER_H

#include <chrono>

namespace tlbx
{
	using nanoseconds 	= std::chrono::nanoseconds;
	using microseconds 	= std::chrono::microseconds;
	using milliseconds 	= std::chrono::milliseconds;
	using seconds 			= std::chrono::seconds;
	using minutes 			= std::chrono::minutes;
	using hours 				= std::chrono::hours;

	class Timer
	{
		using clock_type = std::chrono::high_resolution_clock;
		
		std::chrono::time_point<clock_type> _start;
		std::chrono::time_point<clock_type> _end;

	public:
		Timer();
		~Timer() = default;

		void start();
		void stop();

		template<class T>
		auto duration()
		{
			return std::chrono::duration_cast<T>(_end - _start).count();
		}
	};
}

#endif
