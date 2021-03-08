#include "Logger.h"

#include <fstream>
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

#ifdef BUILD_STANDARD_CHANNEL
	StdChannel StdChannel::out;

	template<>
	StdChannel& operator<<(StdChannel& os, const Payload& obj)
	{
		std::clog << std::put_time(std::localtime(&obj._timestamp), "%T") << " | " << svrt::_colors[obj._severity] << '[' 
			<< svrt::_names[obj._severity] << "]\033[0m | " << obj._msg << '\n'; 
		return os;
	}
#endif

#ifdef BUILD_FILE_CHANNEL
	FileChannel FileChannel::out;

	FileChannel::FileChannel()
		: _file { "log", std::ios::trunc | std::ios::out }
	{
		ASSERT(_file.is_open(), "file log could not be opened")
	}

	template<>
	FileChannel& operator<<(FileChannel& os, const Payload& obj)
	{
		os._file << std::put_time(std::localtime(&obj._timestamp), "%T") << " | [" << svrt::_names[obj._severity] << "] | "
		 	<< obj._msg << '\n'; 
		return os;
	}
#endif

  void log(const Payload& payload)
  {
#ifdef BUILD_STANDARD_CHANNEL
		StdChannel::out << payload;
#endif

#ifdef BUILD_FILE_CHANNEL
		FileChannel::out << payload;
#endif
  }
}
