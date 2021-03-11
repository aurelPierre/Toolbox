#include "Timer.h"
#include "Logger.h"

#include <chrono>
#include <thread>

int main(int argc, char** argv)
{
	tlbx::Timer timer;

	std::this_thread::sleep_for(tlbx::milliseconds(200));

	timer.stop();

	tlbx::Channel::Add<tlbx::StdChannel>();
	LOG(tlbx::INFO, std::to_string(timer.duration<tlbx::milliseconds::period>()));	

	return 0;
}
