#ifndef PROFILER_H
#define PROFILER_H

#include <unordered_map>
#include <string>
#include <limits>

#include "Stopwatch.h"

namespace tlbx
{
	class Profiler
	{
	public:
		struct Info
		{
			uint32_t 	_count 	= 0;
			float			_min		= std::numeric_limits<float>::max();	
			float			_avg		= 0;	
			float 		_max		= std::numeric_limits<float>::min();
		};

		static std::unordered_map<std::string, Info> _profile;

	private:
		std::string _name;
		Stopwatch 	_stopwatch;

	public:
		Profiler(const std::string& name);
		~Profiler();

		Profiler(const Profiler&) = delete;
		Profiler& operator=(const Profiler&) = delete;

		Profiler(Profiler&&) = delete;
		Profiler& operator=(Profiler&&) = delete;	
	};
}

#endif
