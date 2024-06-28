#include "vec4.hpp"

Vec4::Vec4() : _x(0), _y(0), _z(0), _w(0) {}

Vec4::Vec4(float x, float y, float z, float w) : _x(x), _y(y), _z(z), _w(w) {}

Vec4::Vec4(const Vec4& obj) {
	*this = obj;
}

Vec4::~Vec4() {}

float Vec4::getX() const {
	return (this->_x);
}

float Vec4::getY() const {
	return (this->_y);
}

float Vec4::getZ() const {
	return (this->_z);
}

float Vec4::getW() const {
	return (this->_w);
}

void Vec4::setX(float x) {
	this->_x = x;
}

void Vec4::setY(float y) {
	this->_y = y;
}

void Vec4::setZ(float z) {
	this->_z = z;
}

void Vec4::setW(float w) {
	this->_w = w;
}

Vec4& Vec4::operator=(const Vec4& rhs) {
	
	if (this != &rhs) {
		this->_x = rhs._x;
		this->_y = rhs._y;
		this->_z = rhs._z;
		this->_w = rhs._w;
	}
	return (*this);
}

Vec4 Vec4::operator-(const Vec4& rhs) const {
	return (Vec4(_x - rhs._x, _y - rhs._y, _z - rhs._z, _w - rhs._w));
}

Vec4 Vec4::operator+(const Vec4& rhs) const {
	return (Vec4(_x + rhs._x, _y + rhs._y, _z + rhs._z, _w - rhs._w));
}

Vec4 Vec4::operator*(float scalar) const {
	return (Vec4(_x * scalar, _y * scalar, _z * scalar, _w));
}

std::ostream& Vec4::operator<<(std::ostream& os) const {
	os << "(" << _x << ", " << _y << ", " << _z << ", " << _w << ")";
	return os;
}

float Vec4::dot(const Vec4& v) const {
	return (_x * v._x + _y * v._y + _z * v._z);
}

float Vec4::magnitude() const {
	return (std::sqrt(_x * _x + _y * _y + _z * _z + _w * _w));
}

Vec4 Vec4::normalize() const {
	float mag = magnitude();
	if (mag == 0) {
		throw std::runtime_error("Cannot normalize a vector with magnitude 0.");
	}
	return (Vec4(_x / mag, _y / mag, _z / mag, _w));
}
