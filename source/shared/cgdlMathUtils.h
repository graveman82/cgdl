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
Purpose: simple fast math utils.
Changes (date, description):
    2021-10-09  creation from scratch
//-----------------------------------------------------------------------------

*/
#ifndef CGDL_SHARED_MATHUTILS_H_INCLUDED
#define CGDL_SHARED_MATHUTILS_H_INCLUDED
namespace cgdl {


//-----------------------------------------------------------------------------
template <typename T>
T Max(T x, T y) { return x >= y ? x : y; }

//-----------------------------------------------------------------------------
template <typename T>
T Min(T x, T y) { return x <= y ? x : y; }

//-----------------------------------------------------------------------------
template <typename RT, typename T1, typename T2>
RT Max(T1 x, T2 y) { return x >= y ? (RT)x : (RT)y; }

//-----------------------------------------------------------------------------
template <typename RT, typename T1, typename T2>
RT Min(T1 x, T2 y) { return x <= y ? (RT)x : (RT)y; }

//-----------------------------------------------------------------------------
template <typename T>
T Abs(T x) { return x < 0 ? -x : x; }

} // end of cgdl

#endif // CGDL_SHARED_MATHUTILS_H_INCLUDED
