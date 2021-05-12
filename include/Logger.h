#ifndef LOGGER_H
#define LOGGER_H

#include <algorithm>
#include <string>
#include <iostream>
#include <chrono>
#include <fstream>
#include <thread>
#include <vector>
#include <memory>

#include <threads.h>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include <queue>

#include "Config.h"

namespace tlbx
{
  enum ESeverity
  {
    INFO,
		DEBUG,
		VERBOSE,
    WARNING,
    ERROR
  };

  namespace svrt
  {
    constexpr const char* _names[] = { "INFO", "DEBUG", "VERBOSE", "WARNING", "ERROR" };
  	// blue, green, cyan, yellow and red (everything in bold)
		constexpr const char* _colors[] = { "\033[1;34m", "\033[1;32m", "\033[1;36m", "\033[1;33m", "\033[1;31m" };
	};

	struct Payload
	{
		const ESeverity 	_severity;
		const std::string _msg;
		std::time_t 			_timestamp;

		Payload(const ESeverity severity, const std::string& msg);
		~Payload() = default;
	};

	struct Channel
	{
		using container_type = std::vector<std::unique_ptr<Channel>>;
		static container_type _channels;

		template<class T, class... Args>
		static const container_type::const_iterator Add(Args&&... args)
		{
			_channels.emplace_back(new T(std::forward<Args&&>(args)...));
			return _channels.cend() - 1;
		}

		static void Remove(const container_type::const_iterator& it)
		{
			_channels.erase(it);
		}

		Channel() = default;
		virtual ~Channel() = default;

		Channel(const Channel&) = delete;
		Channel& operator=(const Channel&) = delete;

		Channel(Channel&&) = delete;
		Channel& operator=(Channel&&) = delete;
	
		virtual void print(const Payload& payload) = 0;
	};

	struct StdChannel : public Channel
	{
		virtual void print(const Payload& payload) override;
	};

	struct FileChannel : public Channel
	{
		std::ofstream _file;

		FileChannel();
		~FileChannel() = default;

		virtual void print(const Payload& payload) override;
	};

	class Logger
	{
		std::thread 						_thread;
		std::mutex 							_mutex;
		std::condition_variable _conditionVariable;
		std::atomic<bool>				_isRunning;

		std::queue<Payload> _logs;

	public:
		static Logger _instance;

	private:
		Logger()
		{
			_isRunning = true;
			_thread = std::thread(&Logger::loggingLoop, this);
		}

		~Logger()
		{
			_isRunning = false;
			_conditionVariable.notify_one();

			if(_thread.joinable())
				_thread.join();
		}

		void loggingLoop()
		{
			while(_isRunning)
			{
				{
					std::unique_lock<std::mutex> lock(_mutex);
					_conditionVariable.wait(lock, [&]{ return !_logs.empty() || !_isRunning; });

					while(!_logs.empty())
					{
						Payload log = _logs.front();
						_logs.pop();

						for(size_t i = 0; i < Channel::_channels.size(); ++i)
							Channel::_channels[i]->print(log);
					}
				}
			}
		}

	public:
		void operator()(const Payload& payload)
		{
			{
				std::unique_lock<std::mutex> lock(_mutex);
				_logs.emplace(payload);
			}
			_conditionVariable.notify_one();
		}
	};

  void log(const Payload& payload);
}

#ifdef DISABLE_LOGS
	#define LOG(sev, msg) ;;
#else	
	#define LOG(sev, msg) tlbx::Logger::_instance({ sev, msg });
#endif

#define ASSERT(predicate, msg) if(!predicate) { LOG(tlbx::ERROR, std::string(__FILE__) + ":" + std::to_string(__LINE__) + ":\n\t" + msg) std::exit(-1); }

#endif /* end of include guard: LOGGER_H */
