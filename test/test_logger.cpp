#include <iostream>
#include <future>
#include <thread>

#include "Logger.h"
#include "Config.h"

int main(int argc, char** argv)
{
	tlbx::Logger::Add<tlbx::StdChannel>();
	auto it = tlbx::Logger::Add<tlbx::FileChannel>();

  // static_assert to make sure that severity is handled at compile time
  static_assert(sizeof(tlbx::svrt::_names) == sizeof(char*) * 5);
  static_assert(sizeof(tlbx::svrt::_colors) == sizeof(char*) * 5);	

	(void)std::async(std::launch::async, []{ LOG(tlbx::INFO, "Toolbox version " + std::to_string(Toolbox_VERSION_MAJOR) + "." + std::to_string(Toolbox_VERSION_MINOR)) });
	(void)std::async(std::launch::async, []{ LOG(tlbx::DEBUG, "Toolbox version " + std::to_string(Toolbox_VERSION_MAJOR) + "." + std::to_string(Toolbox_VERSION_MINOR)) });
	(void)std::async(std::launch::async, []{ LOG(tlbx::VERBOSE, "Toolbox version " + std::to_string(Toolbox_VERSION_MAJOR) + "." + std::to_string(Toolbox_VERSION_MINOR)) });
	(void)std::async(std::launch::async, []{ LOG(tlbx::WARNING, "Toolbox version " + std::to_string(Toolbox_VERSION_MAJOR) + "." + std::to_string(Toolbox_VERSION_MINOR)) });

	tlbx::Logger::Remove(it);

	(void)std::async(std::launch::async, []{ LOG(tlbx::ERROR, "Toolbox version " + std::to_string(Toolbox_VERSION_MAJOR) + "." + std::to_string(Toolbox_VERSION_MINOR)) });

	for(size_t i = 0; i < 10; ++i)
	{ auto t = std::thread([i]{ 
				LOG(tlbx::INFO, "Log nb: " + std::to_string(i)) });
		t.detach();
	}
	
	return 0;
}
