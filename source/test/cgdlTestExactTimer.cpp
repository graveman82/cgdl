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
Purpose: Testing exact timer.
Changes (date, description):
    2021-10-13  creation from scratch
//-----------------------------------------------------------------------------

*/

#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string>
#include "timer/cgdlExactTimer.h"

namespace cgdl {

void Test()
{
    ExactTimer timer;
    timer.Initialize();
    std::string s;
    /* Set timer on your smartphone to one minute, type "start" and press Enter (at keyboard) and
    play button (in smartphone timer app) simultaneously.
    */
    while (s != "start")
    {
        std::cin >> s;
        timer.Sleep(100);
    }
    double t0 = timer.UpdateTimeElapsed();

    /* Type "stop" and press Enter (at keyboard) when time is over in smartphone timer app.
    */
    while (s != "stop")
    {
        std::cin >> s;
    }

    double t1 = timer.UpdateTimeElapsed();
    printf("elapsed %g seconds\n", t1 - t0);
}
} // end of cgdl

int main(int argc, char** argv)
{
    cgdl::Test();
    // quit trigger
    printf("Press any key to quit...");
    getch();
    return 0;
}
