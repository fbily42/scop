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

		Mat4(); // Identity matrix
		Mat4(const std::array<std::array<float, 4>, 4>& m);
		Mat4(const Mat4 &obj);
		~Mat4();

		Mat4&	operator=(const Mat4& rhs);
		Mat4	operator*(const Mat4& rhs) const;
		Vec4	operator*(const Vec4& rhs) const;

		const float*	getFirstElement() const;

		static Mat4	translate(const Vec3& v);
		static Mat4	rotate(float angle, const Vec3& axis);
		static Mat4	scale(const Vec3& v);
		static Mat4	perspective(float fov, float aspect, float near, float far);
		static Mat4	lookAt(const Vec3& eye, const Vec3& center, const Vec3& up);
		static Mat4 transformObject(const std::vector<Vec3>& vertices, float rotationAngle, const Vec3& rotationAxis);
};

#endif