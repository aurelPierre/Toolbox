#include "Logger.h"

#include <fstream>
#include <functional>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <thread>
#include <vector>
#include <utility>

namespace tlbx
{
	Payload::Payload(const ESeverity severity, const std::string& msg)
		: _severity { severity }, _msg { msg.c_str() }, _threadId { std::this_thread::get_id() }
	{
    const std::chrono::system_clock::time_point timestamp = std::chrono::system_clock::now();
    _timestamp = std::chrono::system_clock::to_time_t(timestamp);
	}


	void StdChannel::print(const Payload& payload)
	{
		std::clog << '[' << payload._threadId << "] | " << std::put_time(std::localtime(&payload._timestamp), "%T") << " | " << svrt::_colors[payload._severity] << '[' 
			<< svrt::_names[payload._severity] << "]\033[0m | " << payload._msg << '\n';
	}

	FileChannel::FileChannel()
		: _file { "log", std::ios::trunc | std::ios::out }
	{
		ASSERT(_file.is_open(), "file log could not be opened")
	}

	void FileChannel::print(const Payload& payload)
	{
		_file << '[' << payload._threadId << "] | " << std::put_time(std::localtime(&payload._timestamp), "%T") << " | [" << svrt::_names[payload._severity] << "] | "
		 	<< payload._msg << '\n'; 
	}

	Logger Logger::_instance;

	Logger::Logger()
	{
		_isRunning = true;
		_thread = std::thread(&Logger::loggingLoop, this);
	}

	Logger::~Logger()
	{
		_isRunning = false;
		_conditionVariable.notify_one();

		if(_thread.joinable())
			_thread.join();
	}

	void Logger::loggingLoop()
	{
		while(_isRunning)
		{
			{
				std::unique_lock<std::mutex> lock(_mutex);
				_conditionVariable.wait(lock, [&]{ return !_logs.empty() || !_isRunning; });
			}

			while(!_logs.empty())
			{
				Payload log;
				{
					std::unique_lock<std::mutex> lock(_mutex);
					
					log = _logs.front();
					_logs.pop();
				}

				for(size_t i = 0; i < _channels.size(); ++i)
					_channels[i]->print(log);
			}
		}
	}
}
