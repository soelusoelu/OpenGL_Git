#include "Vector3.h"
#include "MathUtility.h"

Vector3::Vector3() :
    x(0.f),
    y(0.f),
    z(0.f) {
}

Vector3::Vector3(float X, float Y, float Z) :
    x(X),
    y(Y),
    z(Z) {
}

float Vector3::length() const {
    return Math::sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::normalize() {
    float l = length();
    if (l != 0) {
        x /= l;
        y /= l;
        z /= l;
    }
    return *this;
}

float Vector3::dot(const Vector3& v) const {
    return (x * v.x + y * v.y + z * v.z);
}

Vector3 Vector3::cross(const Vector3& v) const {
    return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

Vector3 Vector3::operator+() const {
    return *this;
}

Vector3 Vector3::operator-() const {
    return Vector3(-x, -y, -z);
}

Vector3& Vector3::operator+=(const Vector3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vector3& Vector3::operator*=(float s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

Vector3& Vector3::operator/=(float s) {
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

const Vector3 operator+(const Vector3& v1, const Vector3& v2) {
    return Vector3(v1.x + v2.x, v1.y + v1.y, v1.z + v2.z);
}

const Vector3 operator-(const Vector3& v1, const Vector3& v2) {
    return Vector3(v1.x - v2.x, v1.y - v1.y, v1.z - v2.z);
}

const Vector3 operator*(const Vector3& v, float s) {
    return Vector3(v.x * s, v.y * s, v.z * s);
}

const Vector3 operator*(float s, const Vector3& v) {
    return Vector3(v.x * s, v.y * s, v.z * s);
}

const Vector3 operator/(const Vector3& v, float s) {
    return Vector3(v.x / s, v.y / s, v.z / s);
}
