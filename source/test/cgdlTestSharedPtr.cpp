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
Purpose: Test shared pointers..
Changes (date, description):
    2021-10-10  creation from scratch
//-----------------------------------------------------------------------------

*/

#include <stdio.h>
#include <conio.h>
#include <string.h>


#include "test/cgdlTestDummy.h"
#include "memory/cgdlSharedPtr.h"

void Test()
{
    cgdl::SharedPtr<cgdl::TestDummy> p0(new cgdl::TestDummy("Carl", 3.14f));
    cgdl::SharedPtr<cgdl::TestDummy> p1(new cgdl::TestDummy("Gabriel", 3.14f));
    cgdl::SharedPtr<cgdl::TestDummy> p2(new cgdl::TestDummy("Daniel", 3.14f));
    cgdl::SharedPtr<cgdl::TestDummy> p3(new cgdl::TestDummy("Luis", 3.14f));

    cgdl::SharedPtr<cgdl::TestDummy> p4(new cgdl::TestDummy("Carl", 3.14f * 2));
    cgdl::SharedPtr<cgdl::TestDummy> p5(new cgdl::TestDummy("Gabriel", 3.14f * 2));
    cgdl::SharedPtr<cgdl::TestDummy> p6(new cgdl::TestDummy("Daniel", 3.14f * 2));
    cgdl::SharedPtr<cgdl::TestDummy> p7(new cgdl::TestDummy("Luis", 3.14f * 2));

    cgdl::SharedPtr<cgdl::TestDummy> p8(new cgdl::TestDummy("Carl", 3.14f * 3));
    cgdl::SharedPtr<cgdl::TestDummy> p9(new cgdl::TestDummy("Gabriel", 3.14f * 3));
    cgdl::SharedPtr<cgdl::TestDummy> p10(new cgdl::TestDummy("Daniel", 3.14f * 3));
    cgdl::SharedPtr<cgdl::TestDummy> p11(new cgdl::TestDummy("Luis", 3.14f * 3));

    cgdl::SharedPtr<cgdl::TestDummy> p12(new cgdl::TestDummy("Carl", 3.14f * 4));
    cgdl::SharedPtr<cgdl::TestDummy> p13(new cgdl::TestDummy("Gabriel", 3.14f * 4));
    cgdl::SharedPtr<cgdl::TestDummy> p14(new cgdl::TestDummy("Daniel", 3.14f * 4));
    cgdl::SharedPtr<cgdl::TestDummy> p15(new cgdl::TestDummy("Luis", 3.14f * 4));

    p3 = nullptr;
    p14 = nullptr;
    p7 = nullptr;

    cgdl::SharedPtr<cgdl::TestDummy> p16(new cgdl::TestDummy("Carl", 3.14f * 5));
    cgdl::SharedPtr<cgdl::TestDummy> p17(new cgdl::TestDummy("Gabriel", 3.14f * 5));
    cgdl::SharedPtr<cgdl::TestDummy> p18(new cgdl::TestDummy("Daniel", 3.14f * 5));
    cgdl::SharedPtr<cgdl::TestDummy> p19(new cgdl::TestDummy("Luis", 3.14f * 5));
    printf("Press any key to continue...");
    getch();
}

int main(int argc, char** argv)
{
    Test();
    // quit trigger
    printf("Press any key to quit...");
    getch();
    return 0;
}

