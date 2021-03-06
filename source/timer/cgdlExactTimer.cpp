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
Purpose: Exact timer implementation.
Changes (date, description):
    2021-10-13  creation from scratch
//-----------------------------------------------------------------------------

*/

#include <windows.h>
#include <x86intrin.h>
#include "timer/cgdlExactTimer.h"
#include "shared/cgdlIntegers.h"
#include "shared/cgdlMathUtils.h"

namespace cgdl {

//-----------------------------------------------------------------------------
static __inline__ SizeU64 rdtsc()
{
    return __rdtsc();
}

//-----------------------------------------------------------------------------
ExactTimer::ExactTimer() :
    tickStart_(0),
    timeElapsed_(0.0),
    tickDuration_(0.0)
{

}

//-----------------------------------------------------------------------------
bool ExactTimer::Initialize()
{
    EvaluateTickResolution();
    tickStart_ = rdtsc();
    return true;
}

//-----------------------------------------------------------------------------
void ExactTimer::EvaluateTickResolution()
{
    LARGE_INTEGER pcFreq;
    LARGE_INTEGER pcCount;
    LARGE_INTEGER pcCount0;

    ::QueryPerformanceCounter(&pcCount0);
    ::QueryPerformanceFrequency(&pcFreq);

#ifndef CGDL_FREQPORTION_POW_OF_TWO_IN_EXACTTIMER
#define CGDL_FREQPORTION_POW_OF_TWO_IN_EXACTTIMER 4u
#endif
    LONGLONG freqPortion = pcFreq.QuadPart >> CGDL_FREQPORTION_POW_OF_TWO_IN_EXACTTIMER;
    SizeU64 tsc0 = rdtsc();
    do
        ::QueryPerformanceCounter(&pcCount);
    while (pcCount.QuadPart - pcCount0.QuadPart < freqPortion);
    SizeU64 tsc = rdtsc();
    SizeU64 ticksPerSecond = PowOf2(CGDL_FREQPORTION_POW_OF_TWO_IN_EXACTTIMER) * (tsc - tsc0);
    tickDuration_ = 1.0 / ticksPerSecond;
}

//-----------------------------------------------------------------------------
double ExactTimer::UpdateTimeElapsed()
{
    SizeU64 tsc = rdtsc();
    timeElapsed_ = (tsc - tickStart_) * tickDuration_;

    return timeElapsed_;
}

//-----------------------------------------------------------------------------
void ExactTimer::Sleep(CountU32 ms)
{
    ::Sleep(ms);
}
} // end of cgdl
