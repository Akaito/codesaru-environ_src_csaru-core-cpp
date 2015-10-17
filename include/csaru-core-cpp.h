/*
Copyright (c) 2015 Christopher Higgins Barrett

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

namespace CSaruCore {

// system page size in bytes
unsigned long GetSystemPageSize ();

void SecureZero (void * dest, size_t byteCount);

} // namespace CSaruCore
