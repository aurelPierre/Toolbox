#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>
#include <chrono>

#include "Config.h"

/*
* TODO:
* -> Different ostream
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

#ifdef BUILD_STANDARD_CHANNEL 
	struct StdChannel
	{};

	template<class T>
	StdChannel& operator<<(StdChannel& os, const T& obj)
 	{
		std::cout << obj;	
		return os; 
	}
#endif

// TODO wip structure
#ifndef BUILD_FILE_CHANNEL 
	struct FileChannel
	{};

	template<class T>
	FileChannel& operator<<(FileChannel& os, const T& obj) { return os; }
#endif

  namespace details
  {
  }

  void log(const Payload& payload);
}

#define LOG(sev, msg) tlbx::log({ sev, msg });
#define ASSERT(predicate, msg) if(!predicate) { LOG(tlbx::ERROR, std::string(__FILE__) + ":" + std::to_string(__LINE__) + ":\n\t" + msg) std::exit(-1); }

#endif /* end of include guard: LOGGER_H */
