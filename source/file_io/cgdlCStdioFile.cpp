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
Purpose: Implementation of cstdio FILE wrapper.
Changes (date, description):
    2021-10-10  creation from scratch
//-----------------------------------------------------------------------------

*/
#include <wchar.h>
#include <stdio.h>

#ifdef CGDL_CSTDIOFILE_ASSERT_FROM_BOOST
#   include <boost/assert.hpp>
#endif // CGDL_CSTDIOFILE_ASSERT_FROM_BOOST
#include <vector>

#include "file_io/cgdlCStdioFile.h"
#include "shared/cgdlMathUtils.h"

namespace cgdl {
namespace cstdio {

//-----------------------------------------------------------------------------
class FileImpl
{
public:

    FileImpl() : fp_(nullptr) { }

    ~FileImpl() { Close(); }

    bool Open(const wchar_t* pFilename, const wchar_t* pMode)
    {
        Close();

        if (0 != _wfopen_s(&fp_, pFilename, pMode))
        {
            return false;
        }

        CountU32 n = Min<CountU32>(wcsnlen_s(pFilename, File::kMAX_PATH), File::kMAX_PATH);
        for (IndexU32 i = 0; i < n; ++i)
        {
            path_[i] = pFilename[i];
        }
        path_[n] = 0;
        return true;
    }


    void Close()
    {
        if (fp_)
        {
            fclose(fp_);
            fp_ = nullptr;
#ifdef CGDL_CSTDIOFILE_DEBUG_CHECK_AUTOCLOSING
wprintf(L"File \"%s\" was closed.\n", path_);
#endif // CGDL_CSTDIOFILE_DEBUG_CHECK_AUTOCLOSING
        }
    }

    SizeU32 Read(void* p, SizeU32 nBytes)
    {
#ifdef CGDL_CSTDIOFILE_ASSERT_FROM_BOOST
        BOOST_ASSERT_MSG(fp_, "File not opened yet!");
#endif // CGDL_CSTDIOFILE_ASSERT_FROM_BOOST
        return fread(p, 1, nBytes, fp_);
    }

    SizeU32 Size()
    {
        IndexU32 oldPos = GetPos();
        SetPos(0, File::kO_END);
        SizeU32 nSize = GetPos();
        SetPos(oldPos, File::kO_BEGIN);
        return nSize;
    }

    IndexS32 GetPos()
    {
#ifdef CGDL_CSTDIOFILE_ASSERT_FROM_BOOST
        BOOST_ASSERT_MSG(fp_, "File not opened yet!");
#endif // CGDL_CSTDIOFILE_ASSERT_FROM_BOOST
        return (IndexU32)ftell(fp_);
    }

    bool SetPos(IndexS32 nOffset, File::E_Origin origin)
    {
#ifdef CGDL_CSTDIOFILE_ASSERT_FROM_BOOST
        BOOST_ASSERT_MSG(fp_, "File not opened yet!");
#endif // CGDL_CSTDIOFILE_ASSERT_FROM_BOOST
        return 0 == fseek(fp_, nOffset, origin);
    }

private:
    FILE* fp_;
    wchar_t path_[File::kMAX_PATH + 1];
};

//-----------------------------------------------------------------------------

File::File()
{
    pImpl_ = new FileImpl();
}

//-----------------------------------------------------------------------------
File::~File()
{
    delete pImpl_;
}

//-----------------------------------------------------------------------------

bool File::Open(const wchar_t* pFilename, const wchar_t* pMode)
{
    return pImpl_->Open(pFilename, pMode);
}


//-----------------------------------------------------------------------------

void File::Close()
{
    pImpl_->Close();
}

//-----------------------------------------------------------------------------

SizeU32 File::Read(void* p, SizeU32 nBytes)
{
    return pImpl_->Read(p, nBytes);
}

//-----------------------------------------------------------------------------

SizeU32 File::Size()
{
    return pImpl_->Size();
}

//-----------------------------------------------------------------------------

IndexS32 File::GetPos()
{
    return pImpl_->GetPos();
}

//-----------------------------------------------------------------------------

bool File::SetPos(IndexS32 nOffset, E_Origin origin)
{
    return pImpl_->SetPos(nOffset, origin);
}

} // end of cstdio
} // end of cgdl
