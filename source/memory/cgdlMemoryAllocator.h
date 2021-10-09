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
Purpose: memory allocatior with growing policy.
Changes (date, description):
    2021-10-09  creation from scratch
//-----------------------------------------------------------------------------

*/
#ifndef CGDL_MEMORY_MEMORYALLOCATOR_H_INCLUDED
#define CGDL_MEMORY_MEMORYALLOCATOR_H_INCLUDED

#include <vector>
#ifdef CGDL_MEMORYALLOCATOR_IN_DEBUG_MODE
#   include <algorithm>
#endif
#include "memory/cgdlStandardMemoryAllocationPolicy.h"

namespace cgdl {


//-----------------------------------------------------------------------------
/** @class MemoryAllocator
    @param T just for size determining.
*/
template <typename T, typename AllocationPolicy = StandardMemoryAllocationPolicy>
class MemoryAllocator
{
    enum { kSIZE_OF_TYPE = sizeof(T) };

    class Index
    {
    public:
        Index(IndexU16 iContainer, IndexU16 iElement) :
            iContainer(iContainer), iElement(iElement)
        {

        }

        bool operator<(const Index& oth) const
        {
            if (iContainer < oth.iContainer)
                return true;
            else if (iContainer > oth.iContainer)
                return false;
            return iElement < oth.iElement;
        }

        IndexU16 ContainerIndex() const { return iContainer; }
        IndexU16 ElementIndex() const { return iElement; }

    private:
        IndexU16 iContainer;
        IndexU16 iElement;
    };

    struct Node : public Index
    {
         Node(IndexU16 iContainer, IndexU16 iElement) :
            Index(iContainer, iElement)
        {

        }

        ByteU8 memory[kSIZE_OF_TYPE];
    };

    typedef std::vector<Node> Container;

public:
    MemoryAllocator() : capacity_(0) { }
    void* Allocate()
    {
        if (indices_.empty())
        {
            if (!Reserve())
            {
                return nullptr;
            }
        }
        Index index(indices_.back());
        indices_.pop_back();
        Container& container = containers_[index.ContainerIndex()];
        Node& node = container[index.ElementIndex()];

        return &node.memory[0];
    }

    void Free(void* p)
    {
        Index* pIndex = reinterpret_cast<Index*>(p);
        --pIndex;
        indices_.push_back(*pIndex);
    }
private:
    bool Reserve()
    {
        CountU32 newCap = AllocationPolicy::NewCapacity(capacity_);

        IndexU32 iNewContainer = containers_.size();
        containers_.push_back(Container());
        Container& newContainer = containers_.back();
        InitializeNewContainer(newContainer, iNewContainer, newCap);

        AddIndices(newContainer);

        capacity_ += newCap;
        return true;
    }

    // used by Reserve()
    void InitializeNewContainer(Container& container, IndexU32 iNewContainer, CountU32 newCapacity)
    {
        container.reserve(newCapacity);
        // initialize elements
        for (IndexU32 i = 0; i < newCapacity; ++i)
        {
            container.push_back( Node(iNewContainer, container.size()) );
        }
    }

    // used by Reserve()
    bool AddIndices(Container& newContainer)
    {
        for (IndexU32 i = 0; i < newContainer.size(); ++i)
        {
            Node& node = newContainer[i];
            indices_.push_back( Index(node.ContainerIndex(), node.ElementIndex()) );
        }
        return true;
    }

    std::vector<Container> containers_;
    std::vector<Index> indices_; // indices of free (unused) nodes
    CountU32 capacity_;

public:
    void GetStatistics(std::vector<char>& buffer)
    {
        auto PushString = [&buffer](const char* s)
        {
            while (*s)
            {
                buffer.push_back(*s++);
            }
        };

        const char* ToCString(SizeU32 n);
        auto PushNumber = [PushString, &buffer](SizeU32 n)
        {
            PushString(ToCString(n));
        };

        const char* ToCString(const void* p);
        auto PushPointer = [PushString, &buffer](const void* p)
        {
            PushString(ToCString(p));
        };

        auto PushEndL = [PushString, &buffer]()
        {
            PushString("\n");
        };

        buffer.clear();
        PushString("-----------------------------------------------------------------------------\n\n"
                   "  Statistics of Memory allocator of (");
        PushNumber(sizeof(T));
        PushString(" bytes):\n");

        PushString("    containers: ");
        PushNumber(containers_.size());
        PushEndL();

#ifdef CGDL_MEMORYALLOCATOR_IN_DEBUG_MODE

        for (IndexU32 i = 0; i < containers_.size(); ++i)
        {
            Container& container = containers_[i];
            PushString("        [");
            PushNumber(container.size());
            PushString("]\n");

            for (IndexU32 b_i = 0; b_i < container.size(); ++b_i)
            {
                Node& node = container[b_i];
                PushString("            [");
                PushNumber(node.ContainerIndex());
                PushString(", ");
                PushNumber(node.ElementIndex());
                PushString(", ");
                PushPointer(&node.memory[0]);
                PushString("]\n");
            }

        }
#endif

        PushString("    free blocks: ");
        PushNumber(indices_.size());
        PushEndL();

#ifdef CGDL_MEMORYALLOCATOR_IN_DEBUG_MODE
        std::stable_sort(indices_.begin(), indices_.end());
        for (IndexU32 i = 0; i < indices_.size(); ++i)
        {
            Index& index = indices_[i];
            PushString("        [");
            PushNumber(index.ContainerIndex());
            PushString(", ");
            PushNumber(index.ElementIndex());
            PushString("]\n");
        }
#endif
        PushString("\n-----------------------------------------------------------------------------\n");
        PushEndL();
        buffer.push_back('\0');
    }
};

} // end of cgdl
#endif // CGDL_MEMORY_MEMORYALLOCATOR_H_INCLUDED
