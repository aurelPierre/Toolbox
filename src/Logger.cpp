#include "Logger.h"

#include <iostream>
#include <chrono>
#include <iomanip>

namespace tlbx
{
  void log(const ESeverity severity, const std::string& msg)
  {
    const std::chrono::system_clock::time_point timestamp = std::chrono::system_clock::now();
    const std::time_t time = std::chrono::system_clock::to_time_t(timestamp);
    std::cout << std::put_time(std::localtime(&time), "%T") << " | [" << svrt::to_string(severity) << "] | " << msg << '\n';
  }
}
