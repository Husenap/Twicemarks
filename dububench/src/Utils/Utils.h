#pragma once

#include <cmath>
#include <random>

__forceinline float Floor(const float& f) { return std::floorf(f); }
__forceinline float Sqrt(const float& f) { return std::sqrtf(f); }

template<typename T, typename U>
__forceinline float Max(const T& a, const U& b) { return b < a ? a : b; }

template<typename T, typename U>
__forceinline float Min(const T& a, const U& b) { return a < b ? a : b; }

template<typename T>
__forceinline float Abs(const T& f) { return f > 0.f ? f : -f; }

template<typename T>
__forceinline T Mod(const T& x, const T& y) { return x - y * Floor(x/y); }

__forceinline float Cos(const float& f) { return std::cosf(f); }
__forceinline float Sin(const float& f) { return std::sinf(f); }

__forceinline float Step(const float& edge, const float& x) { return x < edge ? 0.f : 1.f; }
template<typename T>
__forceinline float Saturate(const T& f) { return Max(0, Min(1, f)); }
template<typename T>
__forceinline float Clamp(const T& f, const T& lower, const T& upper) { return Max(lower, Min(upper, f)); }
template<typename T>
__forceinline T Lerp(const T& a, const T& b, const float& t) { return a + (b - a) * t; }
template<typename T>
__forceinline T Smoothstep(const T& a, const T& b, const float& f)
{
	float t = Saturate((f - a) / (b - a));
	return t*t*(3.f - 2.f * t);
}

__forceinline float Random() { return rand() / (float)RAND_MAX; }

const static float PI = 3.1415926535898f;
const static float TAU = (2.0f*PI);
const static float PHI = (Sqrt(5.f)*0.5f + 0.5f);
