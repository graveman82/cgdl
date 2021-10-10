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
Purpose: Log implementation..
Changes (date, description):
    2021-10-10  creation from scratch
//-----------------------------------------------------------------------------

*/

#include <stdio.h>
#include <string.h>

#include <new>
#ifdef CGDL_LOGIMPL_ASSERT_FROM_BOOST
#   include <boost/assert.hpp>
#endif // CGDL_LOGIMPL_ASSERT_FROM_BOOST

#include "debug/cgdlLog.h"

namespace cgdl {

//-----------------------------------------------------------------------------

class LogImpl
{
    enum { kMAX_PATH = 260 };
    enum { kBUF_SIZE = 4096 };
public:
    LogImpl(const char* filename) : p_(&buffer_[0])
    {
#ifdef CGDL_LOGIMPL_ASSERT_FROM_BOOST
        BOOST_ASSERT(filename);
#endif // CGDL_LOGIMPL_ASSERT_FROM_BOOST
        strcpy(path_, filename);

        FILE* fp = fopen(path_, "rb");
        if (fp)
        {
            fclose(fp);
            fp = fopen(path_, "wb");
            if (fp)
            {
                char buf[] = "\n";
                fwrite(&buf[0], 1, 1, fp);
                fclose(fp);
            }
        }
    }

    ~LogImpl()
    {
        Flush();
    }

    void Flush()
    {
        FILE* fp = fopen(path_, "ab");
        fwrite(buffer_, 1, p_ - &buffer_[0], fp);
        fclose(fp);
        Reset();
    }

    void Reset() { p_ = &buffer_[0]; }

    char* Write(const char* s)
    {
#ifdef CGDL_LOGIMPL_ASSERT_FROM_BOOST
        BOOST_ASSERT(s);
#endif // CGDL_LOGIMPL_ASSERT_FROM_BOOST
        int len = strlen(s);
        int nFreeSpace = kBUF_SIZE - (p_ - &buffer_[0]);
        if (len + 1 > nFreeSpace)
        {
            Flush();
        }
        strcpy(p_, s);
        p_ += len;
        return p_;
    }

private:
    char buffer_[kBUF_SIZE];
    char* p_;
    char path_[kMAX_PATH + 1];
};

//-----------------------------------------------------------------------------
Log* Log::pInstance_ = nullptr;
ByteU8 Log::instanceMemory_[(sizeof(class LogImpl*) + 4) + 16 - (sizeof(class LogImpl*) + 4) % 16];

//-----------------------------------------------------------------------------
Log& Log::Instance()
{
    if (!pInstance_)
    {
        pInstance_ = new (instanceMemory_) Log();
    }
    return *pInstance_;
}
//-----------------------------------------------------------------------------

Log::Log()
{
    pImpl_ = new LogImpl("cgdl_log.txt");
}

//-----------------------------------------------------------------------------
Log::~Log()
{
    delete pImpl_;
}

//-----------------------------------------------------------------------------

Log& Log::operator<<(const char* s)
{
    pImpl_->Write(s);
    return *this;
}

//-----------------------------------------------------------------------------

Log& Log::operator<<(SizeU32 n)
{
    char buf[32] = {0};
    sprintf(buf, "%u", n);
    pImpl_->Write(buf);
    return *this;
}

//-----------------------------------------------------------------------------

Log& Log::operator<<(IndexS32 n)
{
    char buf[32] = {0};
    sprintf(buf, "%d", n);
    pImpl_->Write(buf);
    return *this;
}

//-----------------------------------------------------------------------------

Log& Log::operator<<(float scalar)
{
    char buf[32] = {0};
    sprintf(buf, "%f", scalar);
    pImpl_->Write(buf);
    return *this;
}

//-----------------------------------------------------------------------------

Log& Log::operator<<(void* p)
{
    char buf[32] = {0};
    sprintf(buf, "%p", p);
    pImpl_->Write(buf);
    return *this;
}

//-----------------------------------------------------------------------------
Log& Log::Tab(IndexU32 level)
{
    while (level--)
        (*this) << "    ";
    return *this;
}

//-----------------------------------------------------------------------------
void Log::Flush()
{
    pImpl_->Flush();
}
} // end of cgdl
