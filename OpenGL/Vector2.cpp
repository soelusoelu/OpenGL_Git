#include "Vector2.h"
#include "MathUtility.h"

Vector2::Vector2() :
    x(0.f),
    y(0.f) {
}

Vector2::Vector2(float X, float Y) :
    x(X),
    y(Y) {
}

float Vector2::length() const {
    return Math::sqrt(x * x + y * y);
}

Vector2 Vector2::normalize() {
    float l = length();
    if (l != 0) {
        x /= l;
        y /= l;
    }
    return *this;
}

float Vector2::dot(const Vector2& v) const {
    return (x * v.x + y * v.y);
}

float Vector2::cross(const Vector2& v) const {
    return (x * v.y - y * v.x);
}

Vector2 Vector2::operator+() const {
    return *this;
}

Vector2 Vector2::operator-() const {
    return Vector2(-x, -y);
}

Vector2& Vector2::operator+=(const Vector2& v) {
    x += v.x;
    y += v.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

Vector2& Vector2::operator*=(float s) {
    x *= s;
    y *= s;
    return *this;
}

Vector2& Vector2::operator/=(float s) {
    x /= s;
    y /= s;
    return *this;
}

const Vector2 operator+(const Vector2& v1, const Vector2& v2) {
    return Vector2(v1.x + v2.x, v1.y + v1.y);
}

const Vector2 operator-(const Vector2& v1, const Vector2& v2) {
    return Vector2(v1.x - v2.x, v1.y - v1.y);
}

const Vector2 operator*(const Vector2& v, float s) {
    return Vector2(v.x * s, v.y * s);
}

const Vector2 operator*(float s, const Vector2& v) {
    return Vector2(v.x * s, v.y * s);
}

const Vector2 operator/(const Vector2& v, float s) {
    return Vector2(v.x / s, v.y / s);
}
