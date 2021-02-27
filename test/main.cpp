#include <iostream>


#include "Logger.h"
#include "Config.h"

int main(int argc, char** argv)
{
  // static_assert to make sure that severity is handled at compile time
  static_assert(sizeof(tlbx::svrt::_names) == sizeof(char*) * 4);
  static_assert(tlbx::svrt::to_string(tlbx::INFO) == "INFO");

  LOG(tlbx::INFO, "Toolbox version " + std::to_string(Toolbox_VERSION_MAJOR) + "." + std::to_string(Toolbox_VERSION_MINOR))
  return 0;
}
