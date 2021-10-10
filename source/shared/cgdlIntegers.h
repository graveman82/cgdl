/*
//-----------------------------------------------------------------------------

    MIT License
    Project: CGDL (Common Game Development Library)
    Copyright (c) 2021 Marat Sungatullin (aka graveman[82], aka MrSung[82])

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

//-----------------------------------------------------------------------------
Purpose: Integer types wrappers for size accuracy and convenience.
Changes (date, description):
    2021-10-09  creation from scratch
//-----------------------------------------------------------------------------

*/
#ifndef CGDL_SHARED_INTEGERS_H_INCLUDED
#define CGDL_SHARED_INTEGERS_H_INCLUDED

#include "shared/cgdlCompiler.h"

#ifdef __GNUC__
#   include <stdint.h>
#endif

namespace cgdl {


//-----------------------------------------------------------------------------
/** @page Unsigned integers.
Ok, all <Name_of_type>U<Number_of_bits> that is SizeU32, CountU32, IndexU32, FlagsU32 and DataU32 are the same type.
It were introduced for convenience when reading the code in some context. For example, we can use IndexU32 as iterator
type when iterating array.
*/

typedef uint8_t SizeU8;
typedef uint16_t SizeU16;
typedef uint32_t SizeU32;

const SizeU8 kNoSizeU8 = SizeU8(-1);
const SizeU16 kNoSizeU16 = SizeU16(-1);
const SizeU32 kNoSizeU32 = SizeU32(-1);

typedef uint8_t ByteU8;

typedef SizeU8 CountU8;
typedef SizeU16 CountU16;
typedef SizeU32 CountU32;

const CountU8 kNoCountU8 = kNoSizeU8;
const CountU16 kNoCountU16 = kNoSizeU16;
const CountU32 kNoCountU32 = kNoSizeU32;

typedef SizeU8 IndexU8;
typedef SizeU16 IndexU16;
typedef SizeU32 IndexU32;

const IndexU8 kNoIndexU8 = kNoSizeU8;
const IndexU16 kNoIndexU16 = kNoSizeU16;
const IndexU32 kNoIndexU32 = kNoSizeU32;

typedef SizeU8 FlagsU8;
typedef SizeU16 FlagsU16;
typedef SizeU32 FlagsU32;

typedef SizeU8 DataU8;
typedef SizeU16 Data16;
typedef SizeU32 DataU32;

//-----------------------------------------------------------------------------
// signed
typedef int8_t IndexS8;
typedef int16_t IndexS16;
typedef int32_t IndexS32;

typedef IndexS8 DataS8;
typedef IndexS16 DataS16;
typedef IndexS32 DataS32;

} // end of cgdl

#endif // CGDL_SHARED_INTEGERS_H_INCLUDED




