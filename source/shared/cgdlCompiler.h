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
Purpose: compiler determination and making related settings to project.
Changes (date, description):
    2021-10-09  creation from scratch
//-----------------------------------------------------------------------------

*/
#ifndef CGDL_SHARED_COMPILER_H_INCLUDED
#define CGDL_SHARED_COMPILER_H_INCLUDED
namespace cgdl {


//-----------------------------------------------------------------------------
// GCC version checking staff
#define CGDL_MAKE_GCC_VERSION(major,minor,patchlevel) ( \
                                (((major)       & 0x000000ff) << 16) |\
                                (((minor)       & 0x000000ff) << 8) |\
                                (((patchlevel)  & 0x000000ff)) )

#define CGDL_GET_GCC_VERSION CGDL_MAKE_GCC_VERSION(__GNUC__,__GNUC_MINOR__,__GNUC_PATCHLEVEL__)

#define CGDL_CHECK_GCC_VERSION(major,minor,patchlevel) \
    CGDL_GET_GCC_VERSION >= CGDL_MAKE_GCC_VERSION(major,minor,patchlevel)

//-----------------------------------------------------------------------------
// determine compiler
#ifdef __GNUC__
#   if !(CGDL_CHECK_GCC_VERSION(6,2,0))
#       error this code work on gcc 6.2.0 or higher!
#   endif
#else // unsupported compiler
#   error unsupported compiler. Supported compilers: \
    gcc 6.2.0 or higher;
#endif

} // end of cgdl
#endif // CGDL_SHARED_COMPILER_H_INCLUDED
