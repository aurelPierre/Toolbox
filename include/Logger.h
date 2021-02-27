#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>

/*
* TODO:
* -> Channel
* -> Different ostream
* -> Logging thread
*/

namespace tlbx
{
  enum ESeverity
  {
    INFO,
    WARNING,
    ERROR,
    CRITICAL
  };

  namespace svrt
  {
    constexpr const char* _names[] = { "INFO", "WARNING", "ERROR", "CRITICAL" };
    constexpr const char* to_string(const ESeverity severity) {  return _names[severity]; }
  };

  namespace details
  {
    struct NullOutput
    {
      void out(const std::string&) {};
    };

    struct StdOutput
    {
      void out(const std::string& msg) { std::cout << msg; }
    };

    template<class T>
    struct Register
    {
      using type = T;
      static T _obj;
    }

    using StdRegister = Register<StdOutput>;
  }

  void log(const ESeverity severity, const std::string& msg);
}

#define LOG(sev, msg) tlbx::log(sev , msg);
#define ASSERT(predicate, msg) if(!predicate) { LOG(tlbx::ERROR, std::string(__FILE__) + ":" + std::to_string(__LINE__) + ":\n\t" + msg) std::exit(-1); }

#endif /* end of include guard: LOGGER_H */
