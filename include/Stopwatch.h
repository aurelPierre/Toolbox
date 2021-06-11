#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

namespace tlbx
{
	using nanoseconds 	= std::chrono::nanoseconds;
	using microseconds 	= std::chrono::microseconds;
	using milliseconds 	= std::chrono::milliseconds;
	using seconds 		= std::chrono::seconds;
	using minutes 		= std::chrono::minutes;
	using hours 		= std::chrono::hours;

	class Stopwatch
	{
		using clock_type = std::chrono::high_resolution_clock;
		
		std::chrono::time_point<clock_type> _start;
		std::chrono::time_point<clock_type> _end;

	public:
		Stopwatch();
		~Stopwatch() = default;

		void start();
		void stop();

		template<class T>
		float duration()
		{
			return std::chrono::duration<float, T>(_end - _start).count();
		}
	};
}

#endif
