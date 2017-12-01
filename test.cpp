#include <cstdio>

#define CSARU_CORE_IMPL
#include "csaru-core.h"


int main (int argc, const char ** argv) {
	unused(argc);
	unused(argv);


	// beep (print alarm character, or other system beep/bell)
	cscore::Beep();


	// system info
	std::printf(
		"System page size is {" PF_SIZE_T "} bytes.\n",
		cscore::GetSystemPageSize()
	);


	// buffer stuff
	uint8_t           buffer[5]      = { 1, 1, 2, 3, 5 };
	const std::size_t bufferElements = arrsize(buffer);
	TEST(bufferElements == 5);

	cscore::SecureZero(buffer, sizeof(buffer));
	for (std::size_t i = 0; i < arrsize(buffer); ++i) {
		TEST(buffer[i] == 0);
	}


	std::printf(
		"\nAll's well.  "
		"Go ahead and copy and use csaru-core.h\n"
	);

	return 0;
}

