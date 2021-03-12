#include "Stopwatch.h"
#include "Logger.h"

#include <chrono>
#include <thread>

int main(int argc, char** argv)
{
	tlbx::Stopwatch stopwatch;

	std::this_thread::sleep_for(tlbx::milliseconds(200));

	stopwatch.stop();

	tlbx::Channel::Add<tlbx::StdChannel>();
	LOG(tlbx::INFO, std::to_string(stopwatch.duration<tlbx::milliseconds::period>()));	

	return 0;
}
