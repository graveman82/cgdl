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
Purpose: Testing log.
Changes (date, description):
    2021-10-10  creation from scratch
//-----------------------------------------------------------------------------

*/

#include <stdio.h>
#include <conio.h>

#include "debug/cgdlLog.h"

void Test()
{
    cgdl::Log::Instance() << "Engine initialization...\n";
    cgdl::Log::Instance().Tab(1) << "Graphics initialization...\n";
    cgdl::Log::Instance().Tab(2) << "Material system initialization...\n";
    cgdl::Log::Instance().Tab(2) << "Material system initialization...failed!\n";
    cgdl::Log::Instance().Tab(1) << "Graphics initialization...failed\n";
    cgdl::Log::Instance() << "Engine initialization...failed!\n";
    cgdl::Log::Instance().Flush();
    // check for cgdl_log.txt in bin, open with Notepad++.
}

int main(int argc, char** argv)
{
    Test();
    // quit trigger
    printf("Press any key to quit...");
    getch();
    return 0;
}
