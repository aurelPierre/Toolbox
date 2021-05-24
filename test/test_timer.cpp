#include "Timer.h"
#include "Logger.h"

#include <thread>

int main(int argc, char** argv)
{
	tlbx::Logger::Add<tlbx::StdChannel>();

	tlbx::Timer t(100, []{ LOG(tlbx::INFO, "executed timer function") }, true);

	std::this_thread::sleep_for(tlbx::milliseconds(100));
	
	t.step();

	return 0;
}
