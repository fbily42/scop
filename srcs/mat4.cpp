#include "mat4.hpp"

Mat4::Mat4() {
	_m = {{
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	}};
}

Mat4::Mat4(const std::array<std::array<float, 4>, 4>& m) : _m(m) {}

Mat4::Mat4(const Mat4& obj) {
	*this = obj;
}

Mat4& Mat4::operator=(const Mat4& rhs) {
	if (this != &rhs) {
		_m = rhs._m;
	}
	return *this;
}