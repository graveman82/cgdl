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
Purpose: Exact timer definition.
Changes (date, description):
    2021-10-13  creation from scratch
//-----------------------------------------------------------------------------

*/
#ifndef CGDL_TIMER_EXACTTIMER_H_INCLUDED
#define CGDL_TIMER_EXACTTIMER_H_INCLUDED

#include "shared/cgdlIntegers.h"

namespace cgdl {


//-----------------------------------------------------------------------------
class ExactTimer
{
public:
    ExactTimer();
    bool Initialize();
    double UpdateTimeElapsed();
    double TimeElapsed() const { return timeElapsed_; }
    void Sleep(CountU32 ms);

private:
    void EvaluateTickResolution();

    SizeU64 tickStart_;
    double timeElapsed_;
    double tickDuration_; // in seconds
};


} // end of cgdl
#endif // CGDL_TIMER_EXACTTIMER_H_INCLUDED
