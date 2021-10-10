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
Purpose: Testing cstdio FILE wrapper.
Changes (date, description):
    2021-10-10  creation from scratch
//-----------------------------------------------------------------------------

*/

#include <stdio.h>
#include <conio.h>

#define CGDL_CSTDIOFILE_DEBUG_CHECK_AUTOCLOSING
#include "file_io/cgdlCStdioFile.h"

void Test()
{
    cgdl::cstdio::File f;
    if (f.Open(L"../data/1.txt", L"rb"))
    {
        char buf[8] = {};
        f.Read(buf, 4);
        printf("Read from \"../data/1.txt\":\n%s\n\n", buf);
    }

}

int main(int argc, char** argv)
{
    Test();
    // quit trigger
    printf("Press any key to quit...");
    getch();
    return 0;
}

