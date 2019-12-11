#ifndef _MATRIX4_H_
#define _MATRIX4_H_

class Vector3;

struct Matrix4 {
    float m[4][4];

    Matrix4();
    Matrix4(float m11, float m12, float m13, float m14,
            float m21, float m22, float m23, float m24,
            float m31, float m32, float m33, float m34,
            float m41, float m42, float m43, float m44);
    Matrix4& setIdentity();

    Matrix4& setScale(const Vector3& v);
    Matrix4& setRotateX(float angle);
    Matrix4& setRotateY(float angle);
    Matrix4& setRotateZ(float angle);
    Matrix4& setTranslate(const Vector3& v);

    Matrix4& setPerspective(float fov, float aspect, float near, float far);
    Matrix4& setLookAt(const Vector3& eye, const Vector3& at, const Vector3& up);

    //���W�ϊ�(�x�N�g���ƍs��̊|���Z������)
    Vector3 transform(const Vector3& v) const;
    //���W�ϊ�(�@���x�N�g���p�ŉ�]�݂̂ŕ��s�ړ��͂����Ȃ�)
    Vector3 transformNormal(const Vector3& v) const;

    Matrix4& operator*=(const Matrix4& m);
    friend const Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);
    friend const Vector3 operator*(const Vector3& v, const Matrix4& m);
};

#endif // !_MATRIX4_H_
