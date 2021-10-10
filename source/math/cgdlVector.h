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
Purpose: math vector implementation.
Changes (date, description):
    2021-10-10  creation from scratch
//-----------------------------------------------------------------------------

*/
#ifndef CGDL_MATH_VECTOR_H_INCLUDED
#define CGDL_MATH_VECTOR_H_INCLUDED

#include "shared/cgdlIntegers.h"
#include "shared/cgdlMathUtils.h"

namespace cgdl {
namespace math {


//-----------------------------------------------------------------------------
template <typename T, CountU32 N>
class Vector
{

public:
    Vector();
    Vector(T x, T y, T z, T w);
    Vector(T x, T y, T z);
    Vector(T x, T y);

    T LengthSquared() const;
    T Length() const;
    T Normalize(T epsilon = T(0.000001));

    Vector<T, N> operator-() const;
    Vector<T, N>& operator+=(Vector<T, N>& oth);
    Vector<T, N>& operator-=(Vector<T, N>& oth);
    Vector<T, N>& operator*=(T scalar);

    T& operator[](IndexU32 index);
    T operator[](IndexU32 index) const;
    T components_[N];
};


//-----------------------------------------------------------------------------
template <typename T, CountU32 N>
inline Vector<T, N>::Vector()
{
    for (IndexU32 i = 0; i < N; ++i)
    {
        components_[i] = T(0);
    }
}

//-----------------------------------------------------------------------------
template <typename T, CountU32 N>
inline Vector<T, N>::Vector(T x, T y, T z, T w)
{
    components_[0] = x;
    components_[1] = y;
    components_[2] = z;
    components_[3] = w;
}

//-----------------------------------------------------------------------------
template <typename T, CountU32 N>
inline Vector<T, N>::Vector(T x, T y, T z)
{
    components_[0] = x;
    components_[1] = y;
    components_[2] = z;
}

//-----------------------------------------------------------------------------
template <typename T, CountU32 N>
inline Vector<T, N>::Vector(T x, T y)
{
    components_[0] = x;
    components_[1] = y;
}

//-----------------------------------------------------------------------------
template <typename T, CountU32 N>
inline T Vector<T, N>::LengthSquared() const
{
    T s = T(0);
    for (IndexU32 i = 0; i < N; ++i)
    {
        s += components_[i] * components_[i];
    }
    return s;
}

//-----------------------------------------------------------------------------
template <typename T, CountU32 N>
inline T Vector<T, N>::Length() const
{
    return Sqrt(LengthSquared());
}

//-----------------------------------------------------------------------------
template <typename T, CountU32 N>
inline T Vector<T, N>::Normalize(T epsilon)
{
    T oldLen = Length();
    if (oldLen <= epsilon)
    {
        for (IndexU32 i = 1; i < N; ++i)
            components_[i] = T(0);
        components_[0] = T(1);
        return oldLen;
    }

    (*this) *= T(1) / oldLen;
    return oldLen;
}

//-----------------------------------------------------------------------------
template <typename T, CountU32 N>
inline Vector<T, N> Vector<T, N>::operator-() const
{
    Vector<T, N> v(*this);
    v *= T(-1);
    return v;
}

//-----------------------------------------------------------------------------
template <typename T, CountU32 N>
inline Vector<T, N>& Vector<T, N>::operator+=(Vector<T, N>& oth)
{
    for (IndexU32 i = 0; i < N; ++i)
    {
        components_[i] += oth[i];
    }
    return *this;
}

//-----------------------------------------------------------------------------
template <typename T, CountU32 N>
inline Vector<T, N>& Vector<T, N>::operator-=(Vector<T, N>& oth)
{
    for (IndexU32 i = 0; i < N; ++i)
    {
        components_[i] -= oth[i];
    }
    return *this;
}

//-----------------------------------------------------------------------------
template <typename T, CountU32 N>
inline Vector<T, N>& Vector<T, N>::operator*=(T scalar)
{
    for (IndexU32 i = 0; i < N; ++i)
    {
        components_[i] *= scalar;
    }
    return *this;
}

//-----------------------------------------------------------------------------
template <typename T, CountU32 N>
inline T& Vector<T, N>::operator[](IndexU32 index)
{
    return components_[index];
}

//-----------------------------------------------------------------------------
template <typename T, CountU32 N>
inline T Vector<T, N>::operator[](IndexU32 index) const
{
    return components_[index];
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// Outer operators

//-----------------------------------------------------------------------------
template <typename T, CountU32 N>
inline Vector<T, N> operator+(const Vector<T, N>& v1, const Vector<T, N>& v2)
{
    Vector<T, N> vr;
    for (IndexU32 i = 0; i < N; ++i)
    {
        vr[i] = v1[i] + v2[i];
    }
    return vr;
}

//-----------------------------------------------------------------------------
template <typename T, CountU32 N>
inline Vector<T, N> operator-(const Vector<T, N>& v1, const Vector<T, N>& v2)
{
    Vector<T, N> vr;
    for (IndexU32 i = 0; i < N; ++i)
    {
        vr[i] = v1[i] - v2[i];
    }
    return vr;
}

//-----------------------------------------------------------------------------
template <typename T, CountU32 N>
inline Vector<T, N> operator*(const Vector<T, N>& v, T scalar)
{
    Vector<T, N> vr;
    for (IndexU32 i = 0; i < N; ++i)
    {
        vr[i] = v[i] * scalar;
    }
    return vr;
}

//-----------------------------------------------------------------------------
template <typename T, CountU32 N>
inline Vector<T, N> operator*(T scalar, const Vector<T, N>& v)
{
    return v * scalar;
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// Length squared

//-----------------------------------------------------------------------------
// 4
//-----------------------------------------------------------------------------
template <>
inline float Vector<float, 4>::LengthSquared() const
{
    return  components_[0] * components_[0] +
            components_[1] * components_[1] +
            components_[2] * components_[2] +
            components_[3] * components_[3];
}

template <>
inline double Vector<double, 4>::LengthSquared() const
{
    return  components_[0] * components_[0] +
            components_[1] * components_[1] +
            components_[2] * components_[2] +
            components_[3] * components_[3];
}

template <>
inline DataS32 Vector<DataS32, 4>::LengthSquared() const
{
    return  components_[0] * components_[0] +
            components_[1] * components_[1] +
            components_[2] * components_[2] +
            components_[3] * components_[3];
}

//-----------------------------------------------------------------------------
// 3
//-----------------------------------------------------------------------------
template <>
inline float Vector<float, 3>::LengthSquared() const
{
    return  components_[0] * components_[0] +
            components_[1] * components_[1] +
            components_[2] * components_[2];
}

template <>
inline double Vector<double, 3>::LengthSquared() const
{
    return  components_[0] * components_[0] +
            components_[1] * components_[1] +
            components_[2] * components_[2];
}

template <>
inline DataS32 Vector<DataS32, 3>::LengthSquared() const
{
    return  components_[0] * components_[0] +
            components_[1] * components_[1] +
            components_[2] * components_[2];
}

//-----------------------------------------------------------------------------
// 2
//-----------------------------------------------------------------------------
template <>
inline float Vector<float, 2>::LengthSquared() const
{
    return  components_[0] * components_[0] +
            components_[1] * components_[1];
}

template <>
inline double Vector<double, 2>::LengthSquared() const
{
    return  components_[0] * components_[0] +
            components_[1] * components_[1];
}

template <>
inline DataS32 Vector<DataS32, 2>::LengthSquared() const
{
    return  components_[0] * components_[0] +
            components_[1] * components_[1];
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// typedefs

typedef Vector<float, 4> Vector4f;
typedef Vector<float, 3> Vector3f;
typedef Vector<float, 2> Vector2f;

typedef Vector<double, 4> Vector4d;
typedef Vector<double, 3> Vector3d;
typedef Vector<double, 2> Vector2d;

typedef Vector<ByteU8, 4> Vector4u8;
typedef Vector<ByteU8, 3> Vector3u8;
typedef Vector<ByteU8, 2> Vector2u8;

} // end of math
} // end of cgdl
#endif // CGDL_MATH_VECTOR_H_INCLUDED
