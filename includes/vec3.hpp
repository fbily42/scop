#ifndef VEC3_HPP
#define VEC3_HPP

#include "colors.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

class Vec3
{
	private:

		float _x, _y, _z;

	public:

		Vec3();
		Vec3(float x, float y, float z);
		Vec3(const Vec3& obj);
		~Vec3();

		float 	getX() const;
		float 	getY() const;
		float 	getZ() const;

		void	setX(float x);
		void	setY(float y);
		void	setZ(float z);

		Vec3&	operator=(const Vec3& rhs);
		Vec3	operator-(const Vec3& rhs) const;
		Vec3	operator+(const Vec3& rhs) const;
		Vec3	operator*(float scalar) const;
		Vec3&	operator+=(const Vec3& rhs);
		Vec3&	operator-=(const Vec3& rhs);


		float	dot(const Vec3& v) const;
		Vec3	cross(const Vec3& v) const;
		float	magnitude() const;
		Vec3	normalize() const;

		std::ostream& operator<<(std::ostream& os) const;
};


#endif