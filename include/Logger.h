#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <memory>

#include "Config.h"

/*
* TODO:
* -> Logging thread
*/

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
		const ESeverity _severity;
		const char* 		_msg;
		std::time_t 		_timestamp;

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

  void log(const Payload& payload);
}

#define LOG(sev, msg) tlbx::log({ sev, msg });
#define ASSERT(predicate, msg) if(!predicate) { LOG(tlbx::ERROR, std::string(__FILE__) + ":" + std::to_string(__LINE__) + ":\n\t" + msg) std::exit(-1); }

#endif /* end of include guard: LOGGER_H */
