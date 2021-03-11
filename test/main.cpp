#include <iostream>

#include "Logger.h"
#include "Config.h"

int main(int argc, char** argv)
{
	tlbx::Channel::Add<tlbx::StdChannel>();
	auto it = tlbx::Channel::Add<tlbx::FileChannel>();

  // static_assert to make sure that severity is handled at compile time
  static_assert(sizeof(tlbx::svrt::_names) == sizeof(char*) * 5);
  static_assert(sizeof(tlbx::svrt::_colors) == sizeof(char*) * 5);

  LOG(tlbx::INFO, "Toolbox version " + std::to_string(Toolbox_VERSION_MAJOR) + "." + std::to_string(Toolbox_VERSION_MINOR))
  LOG(tlbx::DEBUG, "Toolbox version " + std::to_string(Toolbox_VERSION_MAJOR) + "." + std::to_string(Toolbox_VERSION_MINOR))
  LOG(tlbx::VERBOSE, "Toolbox version " + std::to_string(Toolbox_VERSION_MAJOR) + "." + std::to_string(Toolbox_VERSION_MINOR))
  LOG(tlbx::WARNING, "Toolbox version " + std::to_string(Toolbox_VERSION_MAJOR) + "." + std::to_string(Toolbox_VERSION_MINOR))
  
	tlbx::Channel::Remove(it);
	
	LOG(tlbx::ERROR, "Toolbox version " + std::to_string(Toolbox_VERSION_MAJOR) + "." + std::to_string(Toolbox_VERSION_MINOR))

	return 0;
}
