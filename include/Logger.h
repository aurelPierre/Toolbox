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

#include <thread>
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
		ESeverity 		_severity;
		std::string 	_msg;
		time_t 			_timestamp;
		std::thread::id _threadId;

		Payload() = default;
		Payload(const ESeverity severity, const std::string& msg);
		~Payload() = default;
	};

	struct Channel
	{
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
		using container_type = std::vector<std::unique_ptr<Channel>>;

	public:
		static Logger 				_instance;

	private:
		std::thread 				_thread;
		std::mutex 					_mutex;
		std::condition_variable		_conditionVariable;
		std::atomic<bool>			_isRunning;

		std::queue<Payload> 		_logs;
		container_type 				_channels;

	public:
		template<class T, class... Args>
		static const container_type::const_iterator Add(Args&&... args)
		{
			_instance._channels.emplace_back(new T(std::forward<Args&&>(args)...));
			return _instance._channels.cend() - 1;
		}

		static void Remove(const container_type::const_iterator& it)
		{
			_instance._channels.erase(it);
		}

	private:
		Logger();
		~Logger();

		void loggingLoop();

	public:
		template<class ... Args>
		void operator()(Args&&... args)
		{
			{
				std::unique_lock<std::mutex> lock(_mutex);
				_logs.emplace(std::forward<Args>(args)...);
			}
			_conditionVariable.notify_one();
		}
	};
}

#ifdef DISABLE_LOGS
	#define LOG(sev, msg) ;;
#else	
	#define LOG(sev, msg) tlbx::Logger::_instance(sev, msg);
#endif

#define ASSERT(predicate, msg) if(!predicate) { LOG(tlbx::ERROR, std::string(__FILE__) + ":" + std::to_string(__LINE__) + ":\n\t" + msg) std::exit(-1); }

#endif /* end of include guard: LOGGER_H */
