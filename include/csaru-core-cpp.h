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

#pragma once

#include <cstdint>
#include <climits>
#include <cassert>

#define ASSERT(x) assert(x)

#define ref(x) \
    (void(&x))

#define arrsize(a) \
    (sizeof(a) / sizeof(a[0]))

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
// As explained in some places, MSVC's C compiler is still mostly in the C98 days.  GCC uses more modern C standards.
// Copy-paste-tweaked from:
// http://stackoverflow.com/questions/1546789/clean-code-to-printf-size-t-in-c-or-nearest-equivalent-of-c99s-z-in-c
#if defined(_MSC_VER) || defined(__MINGW32__) //__MINGW32__ should goes before __GNUC__
#	define PF_SIZE_T    "%Iu"
#	define PF_SSIZE_T   "%Id"
#	define PF_PTRDIFF_T "%Id"
#elif defined(__GNUC__)
#	define PF_SIZE_T    "%zu"
#	define PF_SSIZE_T   "%zd"
#	define PF_PTRDIFF_T "%zd"
#else
  // TODO figure out which to use.
#	if NUMBITS == 32
#		error "Figure out size_t format specifiers for this platform."
#		define PF_SIZE_T    something_unsigned
#		define PF_SSIZE_T   something_signed
#		define PF_PTRDIFF_T something_signed
#	else
#		error "Figure out size_t format specifiers for this platform."
#		define PF_SIZE_T    something_bigger_unsigned
#		define PF_SSIZE_T   something_bigger_signed
#		define PF_PTRDIFF_T something-bigger_signed
#	endif
#endif
//
//////

namespace CSaruCore {

// system page size in bytes
std::size_t GetSystemPageSize ();

void SecureZero (void * dest, std::size_t byteCount);

void Beep ();

} // namespace CSaruCore

