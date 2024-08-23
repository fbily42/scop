#include "vec2.hpp"

Vec2::Vec2() : _x(0), _y(0) {};

Vec2::Vec2(float x, float y) : _x(x), _y(y) {}

Vec2::Vec2(const Vec2& obj) {
	*this = obj;
}

Vec2::~Vec2() {}

float Vec2::getX() const {
	return (this->_x);
}

float Vec2::getY() const {
	return (this->_y);
}

void Vec2::setX(float x) {
	this->_x = x;
}

void Vec2::setY(float y) {
	this->_y = y;
}

Vec2& Vec2::operator=(const Vec2& rhs) {
	
	if (this != &rhs) {
		this->_x = rhs._x;
		this->_y = rhs._y;
	}
	return (*this);
}