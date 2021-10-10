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
Purpose: Definition of stdio fFILE wrapper.
Changes (date, description):
    2021-10-10  creation from scratch
//-----------------------------------------------------------------------------

*/
#ifndef CGDL_FILE_IO_CSTDIOFILE_H_INCLUDED
#define CGDL_FILE_IO_CSTDIOFILE_H_INCLUDED


#include "shared/cgdlIntegers.h"

namespace cgdl {
namespace cstdio {

//-----------------------------------------------------------------------------
class File
{
public:
    enum { kMAX_PATH = 260u };

    enum E_Origin
    {
        kO_BEGIN,
        kO_CURRENT,
        kO_END
    };

    File();
    ~File();

    bool Open(const wchar_t* pFilename, const wchar_t* pMode);
    void Close();

    SizeU32 Read(void* p, SizeU32 nBytes);

    SizeU32 Size();

    IndexS32 GetPos();
    bool SetPos(IndexS32 nOffset, E_Origin origin);

private:
    class FileImpl* pImpl_;
};

} // end of cstdio
} // end of cgdl

#endif // CGDL_FILE_IO_CSTDIOFILE_H_INCLUDED
