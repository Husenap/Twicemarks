#pragma once

#include "Utils.h"
#include "Vec.h"

__forceinline float Vmax(const vec2& v) { return Max(v.x, v.y); }
__forceinline float Vmax(const vec3& v) { return Max(v.x, Max(v.y, v.z)); }
__forceinline float Vmax(const vec4& v) { return Max(Max(v.x, v.y), Max(v.z, v.w)); }
__forceinline float Vmin(const vec2& v) { return Min(v.x, v.y); }
__forceinline float Vmin(const vec3& v) { return Min(v.x, Min(v.y, v.z)); }
__forceinline float Vmin(const vec4& v) { return Min(Min(v.x, v.y), Min(v.z, v.w)); }

__forceinline vec2 Max(const vec2& a, const vec2& b) { return vec2(Max(a.x, b.x), Max(a.y, b.y)); }
__forceinline vec3 Max(const vec3& a, const vec3& b) { return vec3(Max(a.x, b.x), Max(a.y, b.y), Max(a.z, b.z)); }
__forceinline vec2 Min(const vec2& a, const vec2& b) { return vec2(Min(a.x, b.x), Min(a.y, b.y)); }
__forceinline vec3 Min(const vec3& a, const vec3& b) { return vec3(Min(a.x, b.x), Min(a.y, b.y), Min(a.z, b.z)); }

__forceinline vec2 Abs(const vec2& v) { return vec2(Abs(v.x), Abs(v.y)); }
__forceinline vec3 Abs(const vec3& v) { return vec3(Abs(v.x), Abs(v.y), Abs(v.z)); }
__forceinline vec4 Abs(const vec4& v) { return vec4(Abs(v.x), Abs(v.y), Abs(v.z), Abs(v.w)); }

__forceinline vec2 Floor(const vec2& v) { return vec2(Floor(v.x), Floor(v.y)); }
__forceinline vec3 Floor(const vec3& v) { return vec3(Floor(v.x), Floor(v.y), Floor(v.z)); }
__forceinline vec4 Floor(const vec4& v) { return vec4(Floor(v.x), Floor(v.y), Floor(v.z), Floor(v.w)); }

__forceinline vec2 Saturate(const vec2& v) { return vec2(Saturate(v.x), Saturate(v.y)); }
__forceinline vec3 Saturate(const vec3& v) { return vec3(Saturate(v.x), Saturate(v.y), Saturate(v.z)); }
__forceinline vec4 Saturate(const vec4& v) { return vec4(Saturate(v.x), Saturate(v.y), Saturate(v.z), Saturate(v.w)); }

__forceinline float dot(const vec2& a, const vec2& b) { return a.x*b.x + a.y*b.y; }
__forceinline float length(const vec2& v) { return Sqrt(dot(v, v)); }
__forceinline vec2 normalize(const vec2& v) { return v / length(v); }

__forceinline float dot(const vec3& a, const vec3& b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
__forceinline float length(const vec3& v) { return Sqrt(dot(v, v)); }
__forceinline vec3 normalize(const vec3& v) { return v / length(v); }
