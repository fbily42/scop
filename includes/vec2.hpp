#ifndef VEC2_HPP
#define VEC2_HPP

#include "colors.h"
#include <iostream>

class Vec2
{
	private:

		float _x, _y;

	public:

		Vec2();
		Vec2(float x, float y);
		Vec2(const Vec2& obj);
		~Vec2();

		float 	getX() const;
		float 	getY() const;
		void	setX(float x);
		void	setY(float y);

		Vec2&	operator=(const Vec2& rhs);
};

#endif