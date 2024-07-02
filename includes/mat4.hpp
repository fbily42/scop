#ifndef MAT4_HPP
#define MAT4_HPP

#include "colors.h"
#include <iostream>
#include <array>
#include "vec3.hpp"
#include "vec4.hpp"

class Mat4
{
	private:

		std::array<std::array<float, 4>, 4> _m;

	public:

		Mat4();
		Mat4(const std::array<std::array<float, 4>, 4>& m);
		Mat4(const Mat4 &obj);
		~Mat4();

		Mat4& operator=(const Mat4& rhs);
		Mat4 operator*(const Mat4& rhs) const;
		Vec4 operator*(const Vec4& rhs) const;

		static Mat4 translate(const Vec3& v);
		static Mat4 rotate(float angle, const Vec4& axis);
		static Mat4 scale(const Vec3& v);
		static Mat4 perspective(float fov, float aspect, float near, float far);

};

#endif