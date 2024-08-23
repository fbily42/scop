#ifndef VEC4_HPP
#define VEC4_HPP

#include "colors.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

class Vec4
{
	private:

		float _x, _y, _z, _w;

	public:

		Vec4();
		Vec4(float x, float y, float z, float w);
		Vec4(const Vec4& obj);
		~Vec4();

		float	getX() const;
		float	getY() const;
		float	getZ() const;
		float	getW() const;

		void	setX(float x);
		void	setY(float y);
		void	setZ(float z);
		void	setW(float w);

		Vec4&	operator=(const Vec4& rhs);
		Vec4	operator-(const Vec4& rhs) const;
		Vec4	operator+(const Vec4& rhs) const;
		Vec4	operator*(float scalar) const;

		float	dot(const Vec4& v) const;
		float	magnitude() const;
		Vec4	normalize() const;

		std::ostream&	operator<<(std::ostream& os) const;
};

#endif