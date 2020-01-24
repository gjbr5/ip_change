#ifdef _WIN32
#include "WinDivertCapture.h"
#endif
#include "IPChanger.h"
#include <atomic>
#include <csignal>
#include <iostream>

int main(int argc, char** argv)
{
	if (argc != 2) {
		std::cerr << argv[0] << " <dst_ip>" << std::endl;
		return 0;
	}

	static std::atomic_bool flag = true;
	signal(SIGINT, [](int)->void { flag = false; });
#ifdef _WIN32
	std::unique_ptr<Capture> capture = std::make_unique<WinDivertCapture>("true");
#endif
	capture->addListener(new IPChanger(1234, argv[1]));
	while (flag)
		capture->next();

	std::cout << "Finished.\n";
	std::cin.get();
	return 0;
}
