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

Mat4::~Mat4() {}

Mat4::Mat4(const Mat4& obj) {
	*this = obj;
}

Mat4& Mat4::operator=(const Mat4& rhs) {
	if (this != &rhs) {
		_m = rhs._m;
	}
	return *this;
}

Mat4 Mat4::operator*(const Mat4& rhs) const {
	Mat4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result._m[i][j] = 0;
			for (int k = 0; k < 4; k++) {
				result._m[i][j] += _m[i][k] * rhs._m[k][j];
			}
		}
	}
	return result;
}

const float* Mat4::getFirstElement() const {
	return &this->_m[0][0];
}

Vec4 Mat4::operator*(const Vec4& rhs) const {
	return Vec4(
		_m[0][0] * rhs.getX() + _m[0][1] * rhs.getY() + _m[0][2] * rhs.getZ() + _m[0][3] * rhs.getW(),
		_m[1][0] * rhs.getX() + _m[1][1] * rhs.getY() + _m[1][2] * rhs.getZ() + _m[1][3] * rhs.getW(),
		_m[2][0] * rhs.getX() + _m[2][1] * rhs.getY() + _m[2][2] * rhs.getZ() + _m[2][3] * rhs.getW(),
		_m[3][0] * rhs.getX() + _m[3][1] * rhs.getY() + _m[3][2] * rhs.getZ() + _m[3][3] * rhs.getW()
	);
}

Mat4 Mat4::translate(const Vec3& v) {

	std::array<std::array<float, 4>, 4> translationMatrix = {{
        {1, 0, 0, v.getX()},
        {0, 1, 0, v.getY()},
        {0, 0, 1, v.getZ()},
        {0, 0, 0, 1}
    }};
    return Mat4(translationMatrix);
}

Mat4 Mat4::scale(const Vec3& v) {
	std::array<std::array<float, 4>, 4> scaleMatrix = {{
		{v.getX(), 0, 0, 0},
		{0, v.getY(), 0, 0},
		{0, 0, v.getZ(), 0},
		{0, 0, 0, 1}
	}};
	return Mat4(scaleMatrix);
}

Mat4 Mat4::rotate(float angle, const Vec3& axis) {
    float rad = angle * M_PI / 180.0f;
    float c = std::cos(rad);
    float s = std::sin(rad);
    float x = axis.getX(), y = axis.getY(), z = axis.getZ();
	std::array<std::array<float, 4>, 4> rotateMatrix = {{
		{c + (1 - c) * x * x, (1 - c) * x * y - s * z, (1 - c) * x * z + s * y, 0},
        {(1 - c) * y * x + s * z, c + (1 - c) * y * y, (1 - c) * y * z - s * x, 0},
        {(1 - c) * z * x - s * y, (1 - c) * z * y + s * x, c + (1 - c) * z * z, 0},
        {0, 0, 0, 1}
	}};
	return Mat4(rotateMatrix);
}

Mat4 Mat4::perspective(float fov, float aspect, float near, float far) {
    float fovRad = fov * (M_PI / 180.0f);
	float tanHalfFov = std::tan(fovRad / 2);
    std::array<std::array<float, 4>, 4> perspectiveMatrix = {{
        {1 / (aspect * tanHalfFov), 0, 0, 0},
        {0, 1 / tanHalfFov, 0, 0},
        {0, 0, -(far + near) / (far - near), -2 * far * near / (far - near)},
        {0, 0, -1, 0}
    }};
	return Mat4(perspectiveMatrix);
}

Mat4 Mat4::lookAt(const Vec3& eye, const Vec3& center, const Vec3& up) {
    Vec3 f = (center - eye).normalize();
    Vec3 s = f.cross(up).normalize();
    Vec3 u = s.cross(f);

    Mat4 result = Mat4(); // Initialize with identity matrix
    result._m[0][0] = s.getX();
    result._m[0][1] = s.getY();
    result._m[0][2] = s.getZ();
    result._m[0][3] = -s.dot(eye);

    result._m[1][0] = u.getX();
    result._m[1][1] = u.getY();
    result._m[1][2] = u.getZ();
    result._m[1][3] = -u.dot(eye);

    result._m[2][0] = -f.getX();
    result._m[2][1] = -f.getY();
    result._m[2][2] = -f.getZ();
    result._m[2][3] = f.dot(eye);

    result._m[3][0] = 0;
    result._m[3][1] = 0;
    result._m[3][2] = 0;
    result._m[3][3] = 1;

    return result;
}