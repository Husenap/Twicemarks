#pragma once

#ifndef __SDF_H__
#	define __SDF_H__

#	include "Vmath.h"

namespace sdf {

//*================================*
//*== HELPER FUNCTIONS / DEFINES ==*
//*================================*

__forceinline float Sgn(const float& x) {
	return (x < 0.f) ? -1.f : 1.f;
}
__forceinline vec2 Sgn(const vec2& v) {
	return vec2((v.x < 0.f) ? -1.f : 1.f, (v.y < 0.f) ? -1.f : 1.f);
}

__forceinline float Square(const float& x) {
	return x * x;
}
__forceinline vec2 Square(const vec2& x) {
	return x * x;
}
__forceinline vec3 Square(const vec3& x) {
	return x * x;
}

__forceinline float LengthSqr(const vec3& v) {
	return dot(v, v);
}

//*==================================*
//*== Primitive Distance Functions ==*
//*==================================*

__forceinline float FSphere(const vec3& p, const float& r) {
	return length(p) - r;
}

__forceinline float FPlane(const vec3& p, const vec3& n, const float& d) {
	return dot(p, n) - d;
}

__forceinline float FBoxCheap(const vec3& p, const vec3& b) {
	return Vmax(Abs(p) - b);
}

__forceinline float FBox(const vec3& p, const vec3& b) {
	vec3 d = Abs(p) - b;
	return length(Max(d, vec3zero)) + Vmax(Min(d, vec3zero));
}

__forceinline float FBoxRound(const vec3& p, const vec3& b, const float& r) {
	return FBox(p, b - r) - r;
}

__forceinline float FBox2Cheap(const vec2& p, const vec2& b) {
	return Vmax(Abs(p) - b);
}

__forceinline float FBox2(const vec2& p, const vec2& b) {
	vec2 d = Abs(p) - b;
	return length(Max(d, vec2zero)) + Vmax(Min(d, vec2zero));
}

__forceinline float FCorner(const vec2& p) {
	return length(Max(p, vec2zero)) + Vmax(Min(p, vec2zero));
}

__forceinline float FBlob(const vec3& q) {
	vec3 p = Abs(q);
	if (p.x < Max(p.y, p.z)) p = {p.y, p.z, p.x};
	if (p.x < Max(p.y, p.z)) p = {p.y, p.z, p.x};
	float b = Max(Max(Max(dot(p, normalize(vec3(1.f))), dot({p.x, p.z}, normalize(vec2(PHI + 1.f, 1.f)))),
					  dot({p.y, p.x}, normalize(vec2(1.f, PHI)))),
				  dot({p.x, p.z}, normalize(vec2(1.f, PHI))));
	float l = length(p);
	return l - 1.5f - 0.2f * (1.5f / 2.f) * cos(Min(sqrt(1.01f - b / l) * (PI * 4.f), PI));
}

__forceinline float FCylinder(const vec3& p, const float& r, const float& h) {
	return Max(length({p.x, p.z}) - r, Abs(p.y) - h);
}

__forceinline float FCapsule(const vec3& p, const float& r, const float& c) {
	return Lerp(length({p.x, p.z}) - r, length(vec3(p.x, Abs(p.y) - c, p.z)) - r, Step(c, Abs(p.y)));
}

__forceinline float FLineSegment(const vec3& p, const vec3& a, const vec3& b, const float& r) {
	vec3 ab = b - a;
	float t = Saturate(dot(p - a, ab) / dot(ab, ab));
	return length((ab * t + a) - p) - r;
}

__forceinline float FTorus(const vec3& p, float smallRadius, float largeRadius) {
	return length(vec2(length({p.x, p.z}) - largeRadius, p.y)) - smallRadius;
}

__forceinline float FCircle(const vec3& p, float r) {
	float l = length({p.x, p.z}) - r;
	return length(vec2(p.y, l)) - 1e-3f;
}

__forceinline float FDisc(const vec3& p, float r) {
	float l = length({p.x, p.z}) - r;
	return (l < 0.f ? Abs(p.y) : length(vec2(p.y, l))) - 1e-5f;
}

__forceinline float FHexagonCircumcircle(const vec3& p, const float& r, const float& h) {
	vec3 q = Abs(p);

	return Max(q.y - h, Max(q.x * sqrt(3.f) * 0.5f + q.z * 0.5f, q.z) - r);
}

__forceinline float FHexagonIncircle(const vec3& p, const float& r, const float& h) {
	return FHexagonCircumcircle(p, r * sqrt(3.f) * 0.5f, h);
}

//*===================================*
//*== Domain Manipulation Operators ==*
//*===================================*

__forceinline void Rotate(vec2& p, const float& a) {
	p = Cos(a) * p + Sin(a) * vec2(p.y, -p.x);
}
__forceinline void R45(vec2& p) {
	p = (p + vec2(p.y, -p.x)) * sqrt(0.5f);
}

__forceinline float Mod1(float& p, const float& size) {
	float halfSize = size * 0.5f;
	float c = Floor((p + halfSize) / size);
	p = Mod(p + halfSize, size) - halfSize;
	return c;
}

__forceinline float ModMirror1(float& p, const float& size) {
	float halfSize = size * 0.5f;
	float c = Floor((p + halfSize) / size);
	p = Mod(p + halfSize, size) - halfSize;
	p *= Mod(c, 2.f) * 2.f - 1.f;
	return c;
}

__forceinline float ModSingle1(float& p, const float& size) {
	float halfSize = size * 0.5f;
	float c = Floor((p + halfSize) / size);
	if (p >= 0.f) {
		p = Mod(p + halfSize, size) - halfSize;
	}
	return c;
}

__forceinline float ModInterval1(float& p, const float& size, const float& start, const float& stop) {
	float halfSize = size * 0.5f;
	float c = Floor((p + halfSize) / size);
	p = Mod(p + halfSize, size) - halfSize;
	if (c > stop) {
		p += size * (c - stop);
		c = stop;
	}
	if (c < start) {
		p += size * (c - start);
		c = start;
	}
	return c;
}

__forceinline float ModPolar(vec2& p, const float& repititions) {
	float angle = 2.f * PI / repititions;
	float a = atan2(p.y, p.x) + angle / 2.f;
	float r = length(p);
	float c = Floor(a / angle);
	a = Mod(a, angle) - angle / 2.f;
	p = vec2(cos(a), sin(a)) * r;

	if (Abs(c) >= repititions / 2.f) c = Abs(c);
	return c;
}

__forceinline vec2 Mod2(vec2& p, const vec2& size) {
	vec2 halfSize = size * 0.5f;
	vec2 c = Floor((p + halfSize) / size);
	p = Mod(p + halfSize, size) - halfSize;
	return c;
}

__forceinline vec2 ModMirror2(vec2& p, const vec2& size) {
	vec2 halfSize = size * 0.5f;
	vec2 c = Floor((p + halfSize) / size);
	p = Mod(p + halfSize, size) - halfSize;
	p *= Mod(c, vec2(2.f)) * 2.f - 1.f;
	return c;
}

__forceinline vec3 Mod3(vec3& p, const vec3& size) {
	vec3 halfSize = size * 0.5f;
	vec3 c = Floor((p + halfSize) / size);
	p = Mod(p + halfSize, size) - halfSize;
	return c;
}

__forceinline float Mirror(float& p, const float& dist) {
	float s = Sgn(p);
	p = Abs(p) - dist;
	return s;
}

__forceinline vec2 MirrorOctant(vec2& p, const vec2& dist) {
	vec2 s = Sgn(p);
	Mirror(p.x, dist.x);
	Mirror(p.y, dist.y);
	if (p.y > p.x) {
		p = {p.y, p.x};
	}
	return s;
}

__forceinline float Reflect(vec3& p, const vec3& planeNormal, float offset) {
	float t = dot(p, planeNormal) + offset;
	if (t < 0.f) {
		p = p - (2.f * t) * planeNormal;
	}
	return Sgn(t);
}

//*==================================*
//*== Object Combination Operators ==*
//*==================================*

__forceinline float OpUnion(const float& a, const float& b) {
	return Min(a, b);
}
__forceinline float OpIntersection(const float& a, const float& b) {
	return Max(a, b);
}
__forceinline float OpDifference(const float& a, const float& b) {
	return Max(a, -b);
}

__forceinline float OpUnionChamfer(const float& a, const float& b, const float& r) {
	return Min(Min(a, b), (a - r + b) * sqrt(0.5f));
}
__forceinline float OpIntersectionChamfer(const float& a, const float& b, const float& r) {
	return Max(OpIntersection(a, b), (a + r + b) * sqrt(0.5f));
}
__forceinline float OpDifferenceChamfer(const float& a, const float& b, const float& r) {
	return OpIntersectionChamfer(a, -b, r);
}

__forceinline float OpUnionRound(const float& a, const float& b, const float& r) {
	vec2 u = Max(vec2(r - a, r - b), vec2(0.f, 0.f));
	return Max(r, Min(a, b)) - length(u);
}
__forceinline float OpIntersectionRound(const float& a, const float& b, const float& r) {
	vec2 u = Max(vec2(r + a, r + b), vec2zero);
	return Min(-r, OpIntersection(a, b)) + length(u);
}
__forceinline float OpDifferenceRound(const float& a, const float& b, const float& r) {
	return OpIntersectionRound(a, -b, r);
}

__forceinline float OpUnionColumns(const float& a, const float& b, const float& r, const float& n) {
	vec2 p = vec2(a, b);
	float columnRadius = r * sqrt(2.f) / ((n - 1) * 2.f + sqrt(2.f));

	R45(p);

	p.x -= sqrt(2.f) / 2.f * r;
	p.x += columnRadius * sqrt(2.f);

	if (Mod(n, 2.f) == 1.f) {
		p.y += columnRadius;
	}

	Mod1(p.y, columnRadius * 2.f);

	float result = length(p) - columnRadius;
	result = Min(result, p.x);
	result = Min(result, a);
	return Min(result, b);
}

__forceinline float OpDifferenceColumns(const float& _a, const float& b, const float& r, const float& n) {
	float a = -_a;
	float m = Min(a, b);

	if ((a < r) && (b < r)) {
		vec2 p = vec2(a, b);
		float columnRadius = r * sqrt(2.f) / ((n - 1) * 2.f + sqrt(2.f));

		R45(p);

		p.y += columnRadius;
		p.x -= sqrt(2.f) / 2.f * r;
		p.x += -columnRadius * sqrt(2.f) / 2.f;

		if (Mod(n, 2.f) == 1.f) {
			p.y += columnRadius;
		}

		Mod1(p.y, columnRadius * 2.f);

		float result = -length(p) + columnRadius;
		result = Max(result, p.x);
		result = Min(result, a);
		return -Min(result, b);
	} else {
		return -m;
	}
}

__forceinline float OpIntersectionColumns(const float& a, const float& b, const float& r, const float& n) {
	return OpDifferenceColumns(a, -b, r, n);
}

__forceinline float OpUnionStairs(const float& a, const float& b, const float& r, const float& n) {
	float s = r / n;
	float u = b - r;
	return Min(Min(a, b), 0.5f * (u + a + Abs((Mod(u - a + s, 2.f * s)) - s)));
}
__forceinline float OpIntersectionStairs(const float& a, const float& b, const float& r, const float& n) {
	return -OpUnionStairs(-a, -b, r, n);
}
__forceinline float OpDifferenceStairs(const float& a, const float& b, const float& r, const float& n) {
	return -OpUnionStairs(-a, b, r, n);
}

__forceinline float OpUnionSoft(const float& a, const float& b, const float& r) {
	float e = Max(r - Abs(a - b), 0.f);
	return Min(a, b) - e * e * 0.25f / r;
}

__forceinline float OpPipe(const float& a, const float& b, const float& r) {
	return length(vec2(a, b)) - r;
}

__forceinline float OpEngrave(const float& a, const float& b, const float& r) {
	return Max(a, (a + r - Abs(b)) * sqrt(0.5f));
}

__forceinline float OpGroove(const float& a, const float& b, const float& ra, const float& rb) {
	return Max(a, Min(a + ra, rb - Abs(b)));
}

__forceinline float OpTongue(const float& a, const float& b, const float& ra, const float& rb) {
	return Min(a, Max(a - ra, Abs(b) - rb));
}

} /* namespace sdf */

#endif