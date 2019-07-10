#pragma once

#ifndef __VEC_H__
#define __VEC_H__

#pragma warning(disable: 4201)
// ==========================
// ========== vec2 ==========
// ==========================
struct vec2 {
	vec2() :x(0.f), y(0.f) {}
	vec2(float _x, float _y) : x(_x), y(_y){}
	vec2(float _v) : x(_v), y(_v){}

	__forceinline vec2 operator+(const vec2& v) const { return { x + v.x, y + v.y }; }
	__forceinline vec2 operator-(const vec2& v) const { return { x - v.x, y - v.y }; }
	__forceinline vec2 operator*(const vec2& v) const { return { x * v.x, y * v.y }; }
	__forceinline vec2 operator/(const vec2& v) const { return { x / v.x, y / v.y }; }
	__forceinline vec2 operator-() const { return { -x, -y }; }
	__forceinline void operator+=(const vec2& v) { x += v.x; y += v.y; }
	__forceinline void operator-=(const vec2& v) { x -= v.x; y -= v.y; }
	__forceinline void operator+=(const float& f) { x += f; y += f; }
	__forceinline void operator-=(const float& f) { x -= f; y -= f; }
	__forceinline void operator*=(const vec2& v) { x *= v.x; y *= v.y; }
	__forceinline void operator/=(const vec2& v) { x /= v.x; y /= v.y; }
	__forceinline void operator*=(const float& f) { x *= f; y *= f; }
	__forceinline void operator/=(const float& f) { x /= f; y /= f; }

	union {
		struct { float x; float y; };
		struct { float r; float g; };
	};
};
const vec2 vec2zero;

__forceinline vec2 operator+(const vec2& v, const float& f) { return { v.x+f, v.y+f }; }
__forceinline vec2 operator+(const float& f, const vec2& v) { return v + f; }
__forceinline vec2 operator-(const vec2& v, const float& f) { return v + (-f); }
__forceinline vec2 operator-(const float& f, const vec2& v) { return v - f; }
__forceinline vec2 operator*(const vec2& v, const float& f) { return { v.x*f, v.y*f }; }
__forceinline vec2 operator*(const float& f, const vec2& v) { return v * f; }
__forceinline vec2 operator/(const vec2& v, const float& f) { return v * (1.f / f); }
__forceinline vec2 operator/(const float& f, const vec2& v) { return v / f; }

// ==========================
// ========== vec3 ==========
// ==========================
struct vec3 {
	vec3() :x(0.f), y(0.f), z(0.f) {}
	vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z){}
	vec3(float _v) : x(_v), y(_v), z(_v){}

	__forceinline vec3 operator+(const vec3& v) const { return { x + v.x, y + v.y, z + v.z }; }
	__forceinline vec3 operator-(const vec3& v) const { return { x - v.x, y - v.y, z - v.z }; }
	__forceinline vec3 operator*(const vec3& v) const { return { x * v.x, y * v.y, z * v.z }; }
	__forceinline vec3 operator/(const vec3& v) const { return { x / v.x, y / v.y, z / v.z }; }
	__forceinline vec3 operator-() const { return { -x, -y, -z }; }
	__forceinline void operator+=(const vec3& v) { x += v.x; y += v.y; z += v.z; }
	__forceinline void operator-=(const vec3& v) { x -= v.x; y -= v.y; z -= v.z; }
	__forceinline void operator+=(const float& f) { x += f; y += f; z += f; }
	__forceinline void operator-=(const float& f) { x -= f; y -= f; z -= f; }
	__forceinline void operator*=(const float& f) { x *= f; y *= f; z *= f; }
	__forceinline void operator/=(const float& f) { x /= f; y /= f; z /= f; }

	union {
		struct { float x; float y; float z; };
		struct { float r; float g; float b; };
	};
};
const vec3 vec3zero;

__forceinline vec3 operator+(const vec3& v, const float& f) { return { v.x+f, v.y+f, v.z+f }; }
__forceinline vec3 operator+(const float& f, const vec3& v) { return v + f; }
__forceinline vec3 operator-(const vec3& v, const float& f) { return v + (-f); }
__forceinline vec3 operator-(const float& f, const vec3& v) { return v - f; }
__forceinline vec3 operator*(const vec3& v, const float& f) { return { v.x*f, v.y*f, v.z*f }; }
__forceinline vec3 operator*(const float& f, const vec3& v) { return v * f; }
__forceinline vec3 operator/(const vec3& v, const float& f) { return v * (1.f / f); }
__forceinline vec3 operator/(const float& f, const vec3& v) { return v / f; }

// ==========================
// ========== vec4 ==========
// ==========================
struct vec4 {
	vec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w){}
	vec4(float _v) : x(_v), y(_v), z(_v), w(_v){}

	__forceinline vec4 operator+(const vec4& v) const { return { x + v.x, y + v.y, z + v.z, w + v.w }; }
	__forceinline vec4 operator-(const vec4& v) const { return { x - v.x, y - v.y, z - v.z, w - v.w }; }
	__forceinline vec4 operator-() const { return { -x, -y, -z, -w }; }
	__forceinline void operator+=(const vec4& v) { x += v.x; y += v.y; z += v.z; w += v.w; }
	__forceinline void operator-=(const vec4& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; }
	__forceinline void operator+=(const float& f) { x += f; y += f; z += f; w += f; }
	__forceinline void operator-=(const float& f) { x -= f; y -= f; z -= f; w -= f; }
	__forceinline void operator*=(const vec4& v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; }
	__forceinline void operator/=(const vec4& v) { x /= v.x; y /= v.y; z /= v.z; w /= v.w; }
	__forceinline void operator*=(const float& f) { x *= f; y *= f; z *= f; w *= f; }
	__forceinline void operator/=(const float& f) { x /= f; y /= f; z /= f; w /= f; }

	union {
		struct { float x; float y; float z; float w; };
		struct { float r; float g; float b; float a; };
	};
};

__forceinline vec4 operator+(const vec4& v, const float& f) { return { v.x+f, v.y+f, v.z+f, v.w+f }; }
__forceinline vec4 operator+(const float& f, const vec4& v) { return v + f; }
__forceinline vec4 operator-(const vec4& v, const float& f) { return v + (-f); }
__forceinline vec4 operator-(const float& f, const vec4& v) { return v - f; }
__forceinline vec4 operator*(const vec4& v, const float& f) { return { v.x*f, v.y*f, v.z*f, v.w*f }; }
__forceinline vec4 operator*(const float& f, const vec4& v) { return v * f; }
__forceinline vec4 operator/(const vec4& v, const float& f) { return v * (1.f / f); }
__forceinline vec4 operator/(const float& f, const vec4& v) { return v / f; }




#pragma warning(default: 4201)

#endif
