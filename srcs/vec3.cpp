#include "vec3.hpp"

Vec3::Vec3() : _x(0), _y(0), _z(0) {}

Vec3::Vec3(float x, float y, float z) : _x(x), _y(y), _z(z) {}

Vec3::Vec3(const Vec3& obj) {
	*this = obj;
}

Vec3::~Vec3() {}

float Vec3::getX() const {
	return (this->_x);
}

float Vec3::getY() const {
	return (this->_y);
}

float Vec3::getZ() const {
	return (this->_z);
}

void Vec3::setX(float x) {
	this->_x = x;
}

void Vec3::setY(float y) {
	this->_y = y;
}

void Vec3::setZ(float z) {
	this->_z = z;
}

Vec3& Vec3::operator=(const Vec3& rhs) {
	
	if (this != &rhs) {
		this->_x = rhs._x;
		this->_y = rhs._y;
		this->_z = rhs._z;
	}
	return (*this);
}

Vec3 Vec3::operator-(const Vec3& rhs) const {
	return (Vec3(_x - rhs._x, _y - rhs._y, _z - rhs._z));
}

Vec3 Vec3::operator+(const Vec3& rhs) const {
	return (Vec3(_x + rhs._x, _y + rhs._y, _z + rhs._z));
}

Vec3 Vec3::operator*(float scalar) const {
	return (Vec3(_x * scalar, _y * scalar, _z * scalar));
}

std::ostream& Vec3::operator<<(std::ostream& os) const {
	os << "(" << _x << ", " << _y << ", " << _z << ")";
	return os;
}

float Vec3::dot(const Vec3& v) const {
	return (_x * v._x + _y * v._y + _z * v._z);
}

Vec3 Vec3::cross(const Vec3& v) const {
	return (Vec3(
            _y * v._z - _z * v._y,
            _z * v._x - _x * v._z,
            _x * v._y - _y * v._x
        ));
}

float Vec3::magnitude() const {
	return (std::sqrt(_x * _x + _y * _y + _z * _z));
}

Vec3 Vec3::normalize() const {
	float mag = magnitude();
	if (mag == 0) {
		throw std::runtime_error("Cannot normalize a vector with magnitude 0.");
	}
	return (Vec3(_x / mag, _y / mag, _z / mag));
}
