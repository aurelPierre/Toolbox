#include "Logger.h"

#include <fstream>
#include <functional>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

namespace tlbx
{
	Payload::Payload(const ESeverity severity, const std::string& msg)
		: _severity { severity }, _msg { msg.c_str() }
	{
    const std::chrono::system_clock::time_point timestamp = std::chrono::system_clock::now();
    _timestamp = std::chrono::system_clock::to_time_t(timestamp);
	}

	Channel::container_type Channel::_channels;

	void StdChannel::print(const Payload& payload)
	{
		std::clog << std::put_time(std::localtime(&payload._timestamp), "%T") << " | " << svrt::_colors[payload._severity] << '[' 
			<< svrt::_names[payload._severity] << "]\033[0m | " << payload._msg << '\n';
	}

	FileChannel::FileChannel()
		: _file { "log", std::ios::trunc | std::ios::out }
	{
		ASSERT(_file.is_open(), "file log could not be opened")
	}

	void FileChannel::print(const Payload& payload)
	{
		_file << std::put_time(std::localtime(&payload._timestamp), "%T") << " | [" << svrt::_names[payload._severity] << "] | "
		 	<< payload._msg << '\n'; 
	}

	Logger Logger::_instance;

  void log(const Payload& payload)
  {
		for(size_t i = 0; i < Channel::_channels.size(); ++i)
			Channel::_channels[i]->print(payload);
  }
}
