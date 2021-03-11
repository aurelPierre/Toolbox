#include "Profiler.h"

namespace tlbx
{
	std::unordered_map<std::string, Profiler::Info> Profiler::_profile;
	
	Profiler::Profiler(const std::string& name)
		: _name { name }
	{}

	Profiler::~Profiler()
	{
		_timer.stop();
		auto time = _timer.duration<milliseconds::period>();

		if(_profile[_name]._min > time)
			_profile[_name]._min = time;
		else if(_profile[_name]._max < time)
			_profile[_name]._max = time;

		_profile[_name]._avg = (_profile[_name]._avg * _profile[_name]._count + time) / (_profile[_name]._count + 1);
		_profile[_name]._count++;
	}
}
