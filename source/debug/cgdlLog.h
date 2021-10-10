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
Purpose: Log interface definition.
Changes (date, description):
    2021-10-10  creation from scratch
//-----------------------------------------------------------------------------

*/
#ifndef CGDL_DEBUG_LOG_H_INCLUDED
#define CGDL_DEBUG_LOG_H_INCLUDED

#include "shared/cgdlIntegers.h"

namespace cgdl {

//-----------------------------------------------------------------------------
/**
    **Usage**
    @code
    cgdl::Log::Instance() << "Engine initialization...\n";
    cgdl::Log::Instance().Tab(1) << "Graphics initialization...\n";
    cgdl::Log::Instance().Tab(2) << "Material system initialization...\n";
    cgdl::Log::Instance().Tab(2) << "Material system initialization...failed!\n";
    cgdl::Log::Instance().Tab(1) << "Graphics initialization...failed\n";
    cgdl::Log::Instance() << "Engine initialization...failed!\n";
    cgdl::Log::Instance().Flush();
    @endcode
*/
class Log
{
public:
    static Log& Instance();
    ~Log();

    Log& operator<<(const char* s);
    Log& operator<<(SizeU32 n);
    Log& operator<<(IndexS32 n);
    Log& operator<<(float scalar);
    Log& operator<<(void* p);

    Log& Tab(IndexU32 level);
    void Flush();

private:
    Log();
    Log(const Log&);
    Log& operator=(const Log&);

    class LogImpl* pImpl_;
    static Log* pInstance_;
    static ByteU8 instanceMemory_[(sizeof(class LogImpl*) + 4) + 16 - (sizeof(class LogImpl*) + 4) % 16];
};

} // end of cgdl
#endif // CGDL_DEBUG_LOG_H_INCLUDED
