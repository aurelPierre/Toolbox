#include "Logger.h"

#include <iostream>
#include <iomanip>

namespace tlbx
{
	Payload::Payload(const ESeverity severity, const std::string& msg)
		: _severity { severity }, _msg { msg.c_str() }
	{
    const std::chrono::system_clock::time_point timestamp = std::chrono::system_clock::now();
    _timestamp = std::chrono::system_clock::to_time_t(timestamp);
	}

	template<>
	StdChannel& operator<<(StdChannel& os, const Payload& obj)
	{
		std::clog << std::put_time(std::localtime(&obj._timestamp), "%T") << " | " << svrt::_colors[obj._severity] << '[' 
			<< svrt::_names[obj._severity] << "]\033[0m | " << obj._msg << '\n'; 
		return os;
	}

  void log(const Payload& payload)
  {
#ifdef BUILD_STANDARD_CHANNEL
		StdChannel s;
		s << payload;
#endif

#ifdef BUILD_FILE_CHANNEL
		FileChannel f;
	  f << std::put_time(std::localtime(&time), "%T") << " | " << '[' << svrt::_names[severity] << "] | " << msg << '\n'; 
#endif
  }
}
