/*
Copyright (c) 2017 Christopher Higgins Barrett

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

// csaru-core.h
// Platform-independence functions and a few small utilities.

#pragma once

// Feel free to change this if you like.
#define CSCORE_NAMESPACE cscore

#include <cstdint>
#include <climits>
#include <cassert>

#ifndef ASSERT
#   define ASSERT(x) assert(x)
#endif

#ifdef unused
#   error "unused already defined"
#else
// use to silence "unused variable" warnings
#   define unused(x) (void(&x))
#endif

// Tweaked version from a talk by Ryan Gordon (of Icculus) at
// Steam Dev Days, on (porting to) Linux game development.
#ifndef STUBBED
#   ifdef fprintf
#       define STUBBED(msg) \
    do { \
        static bool seenThis = false; \
        if (!seenThis) { \
            fprintf(stderr, "STUBBED: %s at %s (%s:%d)\n", \
                msg, __FUNCTION__, __FILE__, __LINE__); \
        } \
    } while(0);
#   else
#       define STUBBED(msg) (void(&x))
#   endif
#endif

// Seen at ArenaNet and elsewhere.
#define arrsize(a) \
    (sizeof(a) / sizeof(a[0]))

// From Google and others.
#define DISALLOW_COPY_AND_ASSIGN(type)       \
    type (const type &) = delete;            \
    type & operator=(const type &) = delete;

#ifndef MIN
#   define MIN(x, y) ((x) < (y) ? (x) : (y))
#endif

#ifndef MAX
#   define MAX(x, y) ((x) > (y) ? (x) : (y))
#endif

//////
// size_t printf specifiers for multiple platforms.
// Copy-paste-tweaked from:
// http://stackoverflow.com/questions/1546789/clean-code-to-printf-size-t-in-c-or-nearest-equivalent-of-c99s-z-in-c
// As explained in some places, MSVC's C compiler is still mostly in the C98 days.  GCC uses more modern C standards.
#if defined(_MSC_VER) || defined(__MINGW32__) //__MINGW32__ should goes before __GNUC__
#    define PF_SIZE_T    "%Iu"
#    define PF_SSIZE_T   "%Id"
#    define PF_PTRDIFF_T "%Id"
#elif defined(__GNUC__)
#    define PF_SIZE_T    "%zu"
#    define PF_SSIZE_T   "%zd"
#    define PF_PTRDIFF_T "%zd"
#else
  // TODO figure out which to use.
#    if NUMBITS == 32
#        error "Figure out size_t format specifiers for this platform."
#        define PF_SIZE_T    something_unsigned
#        define PF_SSIZE_T   something_signed
#        define PF_PTRDIFF_T something_signed
#    else
#        error "Figure out size_t format specifiers for this platform."
#        define PF_SIZE_T    something_bigger_unsigned
#        define PF_SSIZE_T   something_bigger_signed
#        define PF_PTRDIFF_T something-bigger_signed
#    endif
#endif
//
//////

namespace CSCORE_NAMESPACE {

// system page size in bytes
std::size_t GetSystemPageSize ();

void SecureZero (void * dest, std::size_t byteCount);

void Beep ();

} // namespace for csaru-core




//=====================================================================
// Linux implementations
//=====================================================================

#ifdef __linux__

#	include <cstdio>
#	include <cstring>
#	include <unistd.h>

#	include "exported/everything.hpp"

namespace CSCORE_NAMESPACE {

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
    // TODO : Could GCC/Clang/etc. ever optimize this out?
    memset(dest, 0, byteCount);
}

} // namespace for csaru-core

#endif // __linux__




//=====================================================================
// Windows implementations
//=====================================================================

#ifdef _MSC_VER

#	include <cstddef>
#	include <cstdio>

#	include "exported/everything.hpp"

#	define WIN32_LEAN_AND_MEAN
#	define NOMINMAX
#	include <Windows.h>

namespace CSaruCore {

//=====================================================================
void Beep () {
    std::printf("\a");
}

//=====================================================================
std::size_t GetSystemPageSize () {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    return static_cast<std::size_t>(sysInfo.dwPageSize);
}

//=====================================================================
void SecureZero (void * dest, size_t byteCount) {
    SecureZeroMemory(dest, byteCount);
}

} // namespace CSaruCore

#endif // _MSC_VER

