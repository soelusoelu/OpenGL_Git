#include "Matrix4.h"
#include "Vector3.h"
#include "MathUtility.h"
#include <memory>

Matrix4::Matrix4() :
    m {
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f
    } {
}

Matrix4::Matrix4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44) {
    m[0][0] = m11;
    m[0][1] = m12;
    m[0][2] = m13;
    m[0][3] = m14;

    m[1][0] = m21;
    m[1][1] = m22;
    m[1][2] = m23;
    m[1][3] = m24;

    m[2][0] = m31;
    m[2][1] = m32;
    m[2][2] = m33;
    m[2][3] = m34;

    m[3][0] = m31;
    m[3][1] = m32;
    m[3][2] = m33;
    m[3][3] = m34;
}

Matrix4& Matrix4::setIdentity() {
    static const Matrix4 identity(
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f
    );
    *this = identity;
    return *this;
}

Matrix4& Matrix4::setScale(const Vector3& v) {
    Matrix4 temp(
        v.x, 0.f, 0.f, 0.f,
        0.f, v.y, 0.f, 0.f,
        0.f, 0.f, v.z, 0.f,
        0.f, 0.f, 0.f, 1.f
    );
    return temp;
}

Matrix4& Matrix4::setRotateX(float angle) {
    Matrix4 temp(
        1.f, 0.f, 0.f, 0.f,
        0.f, Math::cos(angle), Math::sin(angle), 0.f,
        0.f, -Math::sin(angle), Math::cos(angle), 0.f,
        0.f, 0.f, 0.f, 1.f
    );
    return temp;
}

Matrix4& Matrix4::setRotateY(float angle) {
    Matrix4 temp(
        Math::cos(angle), 0.f, -Math::sin(angle), 0.f,
        0.f, 1.f, 0.f, 0.f,
        Math::sin(angle), 0.f, Math::cos(angle), 0.f,
        0.f, 0.f, 0.f, 1.f
    );
    return temp;
}

Matrix4& Matrix4::setRotateZ(float angle) {
    Matrix4 temp(
        Math::cos(angle), Math::sin(angle), 0.f, 0.f,
        -Math::sin(angle), Math::cos(angle), 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f
    );
    return temp;
}

Matrix4& Matrix4::setTranslate(const Vector3& v) {
    Matrix4 temp(
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        v.x, v.y, v.z, 1.f
    );
    return temp;
}

Matrix4& Matrix4::setPerspective(float fov, float aspect, float near, float far) {
    float f = 1.f / Math::tan((fov / 2.f));
    Matrix4 temp(
        f / aspect, 0.f, 0.f, 0.f,
        0.f, f, 0.f, 0.f,
        0.f, 0.f, (far + near) / (near - far), -1.f,
        0.f, 0.f, (2 * far * near) / (near - far), 0.f
    );
    return temp;
}

Matrix4& Matrix4::setLookAt(const Vector3& eye, const Vector3& at, const Vector3& up) {
    Vector3 e = (at - eye);
    e.normalize();
    Vector3 v = up.cross(e);
    v.normalize();
    Vector3 u = e.cross(v);
    u.normalize();

    Matrix4 temp(
        v.x, u.x, e.x, 0.0f,
        v.y, u.y, e.y, 0.0f,
        v.z, u.z, e.z, 0.0f,
        -eye.dot(v), -eye.dot(u), -eye.dot(e), 1.0f
    );
    return temp;
}

Vector3 Matrix4::transform(const Vector3& v) const {
    //Vector3 result(
    //    v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0],
    //    v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1],
    //    v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2]
    //);
    float temp[4] = {
        { v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0] },
        { v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1] },
        { v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2] },
        { v.x * m[0][3] + v.y * m[1][3] + v.z * m[2][3] + m[3][3] },
    };
    Vector3 result(temp[0] / temp[3], temp[1] / temp[3], temp[2] / temp[3]);
    return result;
}

Vector3 Matrix4::transformNormal(const Vector3& v) const {
    return Vector3();
}

Matrix4& Matrix4::operator*=(const Matrix4& m) {
    *this = *this * m;
    return *this;
}

const Matrix4 operator*(const Matrix4& m1, const Matrix4& m2) {
    Matrix4 result;
    result.m[0][0] =
        m1.m[0][0] * m2.m[0][0] +
        m1.m[0][1] * m2.m[1][0] +
        m1.m[0][2] * m2.m[2][0] +
        m1.m[0][3] * m2.m[3][0];

    result.m[0][1] =
        m1.m[0][0] * m2.m[0][1] +
        m1.m[0][1] * m2.m[1][1] +
        m1.m[0][2] * m2.m[2][1] +
        m1.m[0][3] * m2.m[3][1];

    result.m[0][2] =
        m1.m[0][0] * m2.m[0][2] +
        m1.m[0][1] * m2.m[1][2] +
        m1.m[0][2] * m2.m[2][2] +
        m1.m[0][3] * m2.m[3][2];

    result.m[0][3] =
        m1.m[0][0] * m2.m[0][3] +
        m1.m[0][1] * m2.m[1][3] +
        m1.m[0][2] * m2.m[2][3] +
        m1.m[0][3] * m2.m[3][3];

    result.m[1][0] =
        m1.m[1][0] * m2.m[0][0] +
        m1.m[1][1] * m2.m[1][0] +
        m1.m[1][2] * m2.m[2][0] +
        m1.m[1][3] * m2.m[3][0];

    result.m[1][1] =
        m1.m[1][0] * m2.m[0][1] +
        m1.m[1][1] * m2.m[1][1] +
        m1.m[1][2] * m2.m[2][1] +
        m1.m[1][3] * m2.m[3][1];

    result.m[1][2] =
        m1.m[1][0] * m2.m[0][2] +
        m1.m[1][1] * m2.m[1][2] +
        m1.m[1][2] * m2.m[2][2] +
        m1.m[1][3] * m2.m[3][2];

    result.m[1][3] =
        m1.m[1][0] * m2.m[0][3] +
        m1.m[1][1] * m2.m[1][3] +
        m1.m[1][2] * m2.m[2][3] +
        m1.m[1][3] * m2.m[3][3];

    result.m[2][0] =
        m1.m[2][0] * m2.m[0][0] +
        m1.m[2][1] * m2.m[1][0] +
        m1.m[2][2] * m2.m[2][0] +
        m1.m[2][3] * m2.m[3][0];

    result.m[2][1] =
        m1.m[2][0] * m2.m[0][1] +
        m1.m[2][1] * m2.m[1][1] +
        m1.m[2][2] * m2.m[2][1] +
        m1.m[2][3] * m2.m[3][1];

    result.m[2][2] =
        m1.m[2][0] * m2.m[0][2] +
        m1.m[2][1] * m2.m[1][2] +
        m1.m[2][2] * m2.m[2][2] +
        m1.m[2][3] * m2.m[3][2];

    result.m[2][3] =
        m1.m[2][0] * m2.m[0][3] +
        m1.m[2][1] * m2.m[1][3] +
        m1.m[2][2] * m2.m[2][3] +
        m1.m[2][3] * m2.m[3][3];

    result.m[3][0] =
        m1.m[3][0] * m2.m[0][0] +
        m1.m[3][1] * m2.m[1][0] +
        m1.m[3][2] * m2.m[2][0] +
        m1.m[3][3] * m2.m[3][0];

    result.m[3][1] =
        m1.m[3][0] * m2.m[0][1] +
        m1.m[3][1] * m2.m[1][1] +
        m1.m[3][2] * m2.m[2][1] +
        m1.m[3][3] * m2.m[3][1];

    result.m[3][2] =
        m1.m[3][0] * m2.m[0][2] +
        m1.m[3][1] * m2.m[1][2] +
        m1.m[3][2] * m2.m[2][2] +
        m1.m[3][3] * m2.m[3][2];

    result.m[3][3] =
        m1.m[3][0] * m2.m[0][3] +
        m1.m[3][1] * m2.m[1][3] +
        m1.m[3][2] * m2.m[2][3] +
        m1.m[3][3] * m2.m[3][3];

    return result;
}

const Vector3 operator*(const Vector3& v, const Matrix4& m) {
    Vector3 result(
        v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0],
        v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1],
        v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2]
    );
    return result;
}
