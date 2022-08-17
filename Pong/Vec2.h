#pragma once
#ifndef _VEC2
#define _VEC2

namespace math {
	template <typename T=float>
	class Vec2 {
	public:
		union { T x, w; };
		union { T y, h; };
		Vec2<T>() : x(), y() {}
		Vec2<T>(T x, T y) : x(x), y(y) {}
		Vec2 operator + (Vec2 const& rhs) {
			return Vec2(x + rhs.x, y + rhs.y);
		}
		Vec2 operator += (Vec2 const& rhs) {
			x += rhs.x;
			y += rhs.y;
			return *this;
		}
		Vec2 operator * (T rhs) {
			return Vec2(x * rhs, y * rhs);
		}
	};
}
#endif