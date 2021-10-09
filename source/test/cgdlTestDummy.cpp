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
Purpose: Implementation of data structure for testing the cgdl code.
Changes (date, description):
    2021-10-09  creation from scratch
//-----------------------------------------------------------------------------

*/

#include <string.h>
#include <stdio.h>

#include "shared/cgdlIntegers.h"
#include "shared/cgdlMathUtils.h"
#include "test/cgdlTestDummy.h"

namespace cgdl {

TestDummy::TestDummy(const char* pName, float scalar) :
    scalar(scalar)
{
    strncpy(name, pName, Min(SizeU32(kNAME_SIZE), (SizeU32)strlen(pName)));
    name[Min(SizeU32(kNAME_SIZE), (SizeU32)strlen(pName))] = 0;
    printf("Test dummy [%p] constructed from args (%s, %f)\n",
           this, pName, scalar);
}

TestDummy::TestDummy(const TestDummy& oth) :
    scalar(oth.scalar)
{
    strncpy(name, oth.name, Min(SizeU32(kNAME_SIZE), (SizeU32)strlen(oth.name)));
    name[Min(SizeU32(kNAME_SIZE), (SizeU32)strlen(oth.name))] = 0;
    printf("Test dummy [%p] constructed from other [%s, %f, %p]\n",
           this, oth.name, scalar, &oth);
}

TestDummy::~TestDummy()
{
    printf("Test dummy [%p] destructor called [%s, %f]\n",
           this, name, scalar);
}

TestDummy& TestDummy::operator=(const TestDummy& oth)
{
    if (this == &oth)
        return *this;

    scalar = oth.scalar;
    strncpy(name, oth.name, Min(SizeU32(kNAME_SIZE), (SizeU32)strlen(oth.name)));
    name[Min(SizeU32(kNAME_SIZE), (SizeU32)strlen(oth.name))] = 0;
    printf("Test dummy [%p] operator= called from other [%s, %f, %p]\n",
           this, oth.name, scalar, &oth);
    return *this;
}

void TestDummy::PrintInfo()
{
    printf("Test dummy [%p] info [%s, %f]\n",
           this, name, scalar);
}

} // end of cgdl
