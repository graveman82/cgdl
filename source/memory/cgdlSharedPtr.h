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
Purpose: Shared pointer definition.
Changes (date, description):
    2021-10-10  creation from scratch
//-----------------------------------------------------------------------------

*/
#ifndef CGDL_MEMORY_SHAREDPTR_H_INCLUDED
#define CGDL_MEMORY_SHAREDPTR_H_INCLUDED


#include "shared/cgdlIntegers.h"

namespace cgdl {

//-----------------------------------------------------------------------------
void* SharedPtr_AllocCountedRef();
void SharedPtr_FreeCountedRef(void*);

//-----------------------------------------------------------------------------
template <typename T>
class StandardDeleter
{
public:
    void operator() (T* ptr)
    {
        delete ptr;
    }
};

//-----------------------------------------------------------------------------
template <typename T, typename Deleter = StandardDeleter<T>>
class SharedPtr
{
    struct CountedRef
    {
        CountedRef() : ptr(nullptr), count(0) { }
        T* ptr;
        CountU32 count;
    };
public:

    ~SharedPtr()
    {
        Release();
    }

    SharedPtr(T* ptr = nullptr) : pCountedRef_(nullptr)
    {
        if (ptr)
            pCountedRef_ = CreateCountedRef(ptr);
    }

    SharedPtr(const SharedPtr<T, Deleter>& oth) : pCountedRef_(nullptr)
    {
        if (oth)
        {
            pCountedRef_ = oth.pCountedRef_;
            ++pCountedRef_->count;
        }

    }

    SharedPtr<T, Deleter>& operator=(const SharedPtr<T, Deleter>& oth)
    {
        if (this == &oth)
            return *this;

        Release();
        if (oth)
        {
            pCountedRef_ = oth.pCountedRef_;
            ++pCountedRef_->count;
        }
        return *this;
    }

    SharedPtr<T, Deleter>& operator=(T* ptr)
    {
        if (pCountedRef_ && pCountedRef_->ptr == ptr)
            return *this;

        Release();
        if (ptr)
            pCountedRef_ = CreateCountedRef(ptr);
        return *this;
    }

    void Release()
    {
        if (pCountedRef_)
        {
            if (--pCountedRef_->count == 0)
            {
                T* ptr = pCountedRef_->ptr;
                DeleteCountedRef(pCountedRef_);
                Deleter d;
                d(ptr);
            }
            pCountedRef_ = nullptr;
        }
    }

    operator bool() const { return nullptr != pCountedRef_; }

    bool operator==(const SharedPtr<T, Deleter>& oth) const
    {
        return pCountedRef_ == oth.pCountedRef_;
    }

    bool operator!=(const SharedPtr<T, Deleter>& oth) const
    {
        return !((*this) == oth);
    }

    T* operator->() { return pCountedRef_ ? pCountedRef_->ptr : nullptr; }
    const T* operator->() const { return pCountedRef_ ? pCountedRef_->ptr : nullptr; }

    T& operator*() { return *pCountedRef_->ptr; }
    const T& operator*() const { return *pCountedRef_->ptr; }


private:
    static CountedRef* CreateCountedRef(T* ptr)
    {
        CountedRef* pCountedRef = (CountedRef*)SharedPtr_AllocCountedRef();
        pCountedRef->ptr = ptr;
        pCountedRef->count = 1;
        return pCountedRef;
    }

    static void DeleteCountedRef(CountedRef* pCountedRef)
    {
        SharedPtr_FreeCountedRef(pCountedRef);
    }
    CountedRef* pCountedRef_;
};

} // end of cgdl

#endif // CGDL_MEMORY_SHAREDPTR_H_INCLUDED
