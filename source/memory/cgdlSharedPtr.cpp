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
Purpose: shared pointers allocation staff.
Changes (date, description):
    2021-10-10  creation from scratch
//-----------------------------------------------------------------------------

*/

#include <new>
#ifdef CGDL_SHARED_PTR_ASSERT_FROM_BOOST
#   include <boost/assert.hpp>
#endif // CGDL_SHARED_PTR_ASSERT_FROM_BOOST
#include <vector>

#include "memory/cgdlSharedPtr.h"
#include "memory/cgdlMemoryAllocator.h"


namespace cgdl {

//-----------------------------------------------------------------------------

namespace SharedPtrPrivate {

struct CountedRef
{
    void* ptr;
    CountU32 count;
};


//-----------------------------------------------------------------------------
class CountedRefPool : public MemoryAllocator<CountedRef>
{
    enum
    {
        kCOUNTEDREF_SIZE = sizeof(CountedRef),
        kBASE_CLASS_SIZE = sizeof(MemoryAllocator<CountedRef>),
        kINSTANCE_MEMORY_SIZE = (kBASE_CLASS_SIZE + 4) + 16 - (kBASE_CLASS_SIZE + 4) % 16
    };
public:
    static CountedRefPool& Instance()
    {
        if (!pInstance_)
        {
            pInstance_ = new (&instanceMemory_[0]) CountedRefPool();
        }
        return *pInstance_;
    }

private:
    CountedRefPool()
    {
#ifdef CGDL_SHARED_PTR_ASSERT_FROM_BOOST
        BOOST_ASSERT_MSG(!pInstance_, "creation more than one instance of singleton class");
#endif // CGDL_SHARED_PTR_ASSERT_FROM_BOOST
    }
    // not allowed copy methods
    CountedRefPool(const CountedRefPool&);
    CountedRefPool& operator=(const CountedRefPool&);

    static CountedRefPool* pInstance_;
    static ByteU8 instanceMemory_[kINSTANCE_MEMORY_SIZE];
};

//-----------------------------------------------------------------------------

CountedRefPool* CountedRefPool::pInstance_ = nullptr;
ByteU8 CountedRefPool::instanceMemory_[kINSTANCE_MEMORY_SIZE];

} // end of SharedPtrPrivate

//-----------------------------------------------------------------------------
void* SharedPtr_AllocCountedRef()
{
    return SharedPtrPrivate::CountedRefPool::Instance().Allocate();
}
//-----------------------------------------------------------------------------;
void SharedPtr_FreeCountedRef(void* p)
{
    SharedPtrPrivate::CountedRefPool::Instance().Free(p);
}
} // end of cgdl
