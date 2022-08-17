#pragma once
#ifndef _VECMATH
#define _VECMATH

//Initialization of the "math" namespace, where the Vec2<T> and Vec3<T> template classes are implemented
namespace math {
	//The "Vec2" template class encapsulates the idea of creating a 2D vector.
	template <typename T>
	class Vec2 {
	public:
		//Data members
		union { T x, w; };
		union { T y, h; };
		//Constructors
		Vec2<T>() : x(), y() {}
		Vec2<T>(T x, T y) : x(x), y(y) {}
		Vec2<T>(T value) : x(value), y(value) {}
		//Operator overloading, to enable some basic (and the appropriate for the project) math and bool operations
		//Vector Addition
		Vec2<T> operator + (Vec2<T> const& rhs) {
			return Vec2(x + rhs.x, y + rhs.y);
		}
		//Addition assignment
		Vec2<T> operator += (Vec2<T> const& rhs) {
			x += rhs.x;
			y += rhs.y;
			return *this;
		}
		//Vector-scalar multiplication 
		Vec2<T> operator * (T rhs) {
			return Vec2<T>(x * rhs, y * rhs);
		}
		//Scalar division
		Vec2<T> operator / (T rhs) {
			Vec2<T> lhs;
			lhs.x = x / rhs;
			lhs.y = y / rhs;
			return lhs;
		}
		//Copy Assignment operator
		Vec2<T> & operator = (const Vec2<T>& rhs) {
			x = rhs.x;
			y = rhs.y;
			return *this;
		}
		//Equality operator
		bool operator == (const Vec2<T>& rhs) {
			return x == rhs.x && y == rhs.y;
		}
		//Inequality operator
		bool operator != (const Vec2<T>& rhs) {
			return x != rhs.x || y != rhs.y;
		}
	};

	//The "Vec3" template class encapsulates the idea of creating a 3D vector. Unlike the Vec2 class, the Vec3 will be used for a better data represantation.
	template <typename T>
	class Vec3 {
	public:
		//Data Members
		union { T x, r; };
		union { T y, g; };
		union { T z, b; };
		//Constructors
		Vec3<T>() : x(), y(), z() {}
		Vec3<T>(T value) : x(value), y(value), z(value) {}
		Vec3<T>(T x, T y, T z) : x(x), y(y), z(z) {}
		//The appropriate for the project, operator overloading
		//Data access operator. Returns the index-th element of the vector
		T& operator [] (size_t index) { return *((T*)this + index); }
		//Copy assignment operator
		Vec3<T>& operator = (const Vec3<T>& rhs) {
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			return *this;
		}
		//Equality Operator
		bool operator == (const Vec3<T>& rhs) { return x == rhs.x && y == rhs.y && z == rhs.z; }
		//Inequality Operator
		bool operator != (const Vec3<T>& rhs) { return x != rhs.x || y != rhs.y || z != rhs.z; }
	};
}
#endif