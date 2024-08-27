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

const float* Mat4::getFirstElement() const {
	return &this->_m[0][0];
}

Mat4 Mat4::operator*(const Mat4& rhs) const {
	Mat4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result._m[i][j] = 0;
			for (int k = 0; k < 4; k++) {
				result._m[i][j] += rhs._m[i][k] * _m[k][j];
			}
		}
	}
	return result;
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

	Mat4 translationMatrix;

	translationMatrix._m[3][0] = v.getX();
    translationMatrix._m[3][1] = v.getY();
    translationMatrix._m[3][2] = v.getZ();

    return translationMatrix;
}

Mat4 Mat4::scale(const Vec3& v) {
	Mat4 scaleMatrix;

	scaleMatrix._m[0][0] = v.getX();
	scaleMatrix._m[1][1] = v.getY();
	scaleMatrix._m[2][2] = v.getZ();

	return scaleMatrix;
}

Mat4 Mat4::rotate(float angle, const Vec3& axis) {
    float rad = angle * M_PI / 180.0f;
    float c = std::cos(rad);
    float s = std::sin(rad);
    float x = axis.getX(), y = axis.getY(), z = axis.getZ();
	Mat4 rotateMatrix;

	rotateMatrix._m[0][0] = c + (1 - c) * x * x;
    rotateMatrix._m[0][1] = (1 - c) * x * y - s * z;
    rotateMatrix._m[0][2] = (1 - c) * x * z + s * y;

    rotateMatrix._m[1][0] = (1 - c) * y * x + s * z;
    rotateMatrix._m[1][1] = c + (1 - c) * y * y;
    rotateMatrix._m[1][2] = (1 - c) * y * z - s * x;

    rotateMatrix._m[2][0] = (1 - c) * z * x - s * y;
    rotateMatrix._m[2][1] = (1 - c) * z * y + s * x;
    rotateMatrix._m[2][2] = c + (1 - c) * z * z;

	return rotateMatrix;
}

Mat4 Mat4::perspective(float fov, float aspect, float near, float far) {
    float fovRad = fov * (M_PI / 180.0f);
	float tanHalfFov = std::tan(fovRad / 2.0f);

	Mat4 perspectiveMatrix;
	
	perspectiveMatrix._m[0][0] = 1.0f / (aspect * tanHalfFov);

    perspectiveMatrix._m[1][1] = 1.0f / tanHalfFov;

    perspectiveMatrix._m[2][2] = -(far + near) / (far - near);
    perspectiveMatrix._m[2][3] = -1.0f;

    perspectiveMatrix._m[3][2] = -(2.0f * far * near) / (far - near);
    perspectiveMatrix._m[3][3] = 0.0f;

	return perspectiveMatrix;
}

Mat4 Mat4::lookAt(const Vec3& eye, const Vec3& center, const Vec3& up) {
    Vec3 f = (center - eye).normalize();
    Vec3 s = f.cross(up).normalize();
    Vec3 u = s.cross(f);

    Mat4 result;

    result._m[0][0] = s.getX();
    result._m[1][0] = s.getY();
    result._m[2][0] = s.getZ();

    result._m[0][1] = u.getX();
    result._m[1][1] = u.getY();
    result._m[2][1] = u.getZ();

    result._m[0][2] = -f.getX();
    result._m[1][2] = -f.getY();
    result._m[2][2] = -f.getZ();

    result._m[3][0] = -s.dot(eye);
    result._m[3][1] = -u.dot(eye);
    result._m[3][2] = f.dot(eye);

    return result;
}

Mat4 Mat4::transformObject(const std::vector<Vec3>& vertices, float rotationAngle, const Vec3& rotationAxis) {
	Vec3 centroid = Vec3::computeCentroid(vertices);
    Mat4 translationToOrigin = Mat4::translate(-centroid);
    Mat4 rotation = Mat4::rotate(rotationAngle, rotationAxis);
    Mat4 translationBack = Mat4::translate(centroid);

    return translationBack * rotation * translationToOrigin;
}