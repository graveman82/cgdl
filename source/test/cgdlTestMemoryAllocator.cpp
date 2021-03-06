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
Purpose: Allocator test.
Changes (date, description):
    2021-10-09  creation from scratch
//-----------------------------------------------------------------------------

*/


#include <stdio.h>
#include <conio.h>
#include <string.h>

#include <new>

#define CGDL_MEMORYALLOCATOR_IN_DEBUG_MODE
#include "memory/cgdlMemoryAllocator.h"
#include "test/cgdlTestDummy.h"

void Test()
{
    std::vector<char> statBuf;

    cgdl::MemoryAllocator<cgdl::TestDummy> malc;
    cgdl::TestDummy* dummies[24] =
    {
        new (malc.Allocate()) cgdl::TestDummy("Carl",     3.14f),
        new (malc.Allocate()) cgdl::TestDummy("Gabriel",    3.14f),
        new (malc.Allocate()) cgdl::TestDummy("Daniel",     3.14f),
        new (malc.Allocate()) cgdl::TestDummy("Luis",     3.14f),

        new (malc.Allocate()) cgdl::TestDummy("Carl",     3.14f * 2),
        new (malc.Allocate()) cgdl::TestDummy("Gabriel",    3.14f * 2),
        new (malc.Allocate()) cgdl::TestDummy("Daniel",     3.14f * 2),
        new (malc.Allocate()) cgdl::TestDummy("Luis",     3.14f * 2),

        new (malc.Allocate()) cgdl::TestDummy("Carl",     3.14f * 3),
        new (malc.Allocate()) cgdl::TestDummy("Gabriel",    3.14f * 3),
        new (malc.Allocate()) cgdl::TestDummy("Daniel",     3.14f * 3),
        new (malc.Allocate()) cgdl::TestDummy("Luis",     3.14f * 3),

        new (malc.Allocate()) cgdl::TestDummy("Carl",     3.14f * 4),
        new (malc.Allocate()) cgdl::TestDummy("Gabriel",    3.14f * 4),
        new (malc.Allocate()) cgdl::TestDummy("Daniel",     3.14f * 4),
        new (malc.Allocate()) cgdl::TestDummy("Luis",     3.14f * 4),
    };


    malc.GetStatistics(statBuf);
    printf(&statBuf[0]);

    malc.Free(dummies[3]);
    malc.Free(dummies[14]);
    malc.Free(dummies[7]);

    malc.GetStatistics(statBuf);
    printf(&statBuf[0]);

    dummies[20] = new (malc.Allocate()) cgdl::TestDummy("Carl",     3.14f * 5);
    dummies[21] = new (malc.Allocate()) cgdl::TestDummy("Gabriel",    3.14f * 5);
    dummies[22] = new (malc.Allocate()) cgdl::TestDummy("Daniel",     3.14f * 5);
    dummies[23] = new (malc.Allocate()) cgdl::TestDummy("Luis",     3.14f * 5);

    malc.GetStatistics(statBuf);
    printf(&statBuf[0]);
}

int main(int argc, char** argv)
{
    Test();
    // quit trigger
    printf("Press any key to quit...");
    getch();
    return 0;
}

