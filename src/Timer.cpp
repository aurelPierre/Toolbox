#include "Timer.h"

namespace tlbx
{
	Timer::Timer(float time, const std::function<void()>& func, bool autoStart)
		: _time { time }, _func { func }
	{
		if(autoStart)
			start();
	}

	void Timer::start()
	{
		_stopwatch.start();
	}

	void Timer::step()
	{
		_stopwatch.stop();
		float time = _stopwatch.duration<milliseconds::period>();
		if(time > _time)
			_func();
	}
}
