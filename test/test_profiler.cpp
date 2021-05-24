#include <thread>
#include <random>

#include "Profiler.h"
#include "Logger.h"

int main(int argc, char** argv)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(10, 30);

	for(size_t i = 0; i < 100; ++i)
	{
		tlbx::Profiler profiler("demo");
		std::this_thread::sleep_for(tlbx::milliseconds(distrib(gen)));
	}

	tlbx::Logger::Add<tlbx::StdChannel>();
	LOG(tlbx::INFO, "Count: " + std::to_string(tlbx::Profiler::_profile["demo"]._count));
	LOG(tlbx::INFO, "Min: " + std::to_string(tlbx::Profiler::_profile["demo"]._min));
	LOG(tlbx::INFO, "Avg: " + std::to_string(tlbx::Profiler::_profile["demo"]._avg));
	LOG(tlbx::INFO, "Max: " + std::to_string(tlbx::Profiler::_profile["demo"]._max));

	return 0;
}
