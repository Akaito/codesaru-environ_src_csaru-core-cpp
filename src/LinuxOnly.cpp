/*
Copyright (c) 2016 Christopher Higgins Barrett

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgement in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

// this file implements the Windows side of Core functions.
#ifdef linux

#include <cstdio>
#include <cstring>
#include <unistd.h>

#include "exported/csaru-core-cpp.h"

namespace CSaruCore {

//=====================================================================
void Beep () {
	std::printf("\a");
}

//=====================================================================
std::size_t GetSystemPageSize () {
	// From getpagesize man page.
    return sysconf(_SC_PAGESIZE);
}

//=====================================================================
void SecureZero (void * dest, size_t byteCount) {
	// TODO : Will GCC/Clang/etc. ever optimize this out?
    memset(dest, 0, byteCount);
}

} // namespace CSaruCore

#endif // linux

