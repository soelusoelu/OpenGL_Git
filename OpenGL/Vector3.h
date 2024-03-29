#ifndef _VECTOR3_H_
#define _VECTOR3_H_

struct Vector3 {
    float x;
    float y;
    float z;

    Vector3();
    Vector3(float X, float Y, float Z);

    float length() const;
    Vector3 normalize();
    float dot(const Vector3& v) const;
    Vector3 cross(const Vector3& v) const;

    Vector3 operator+() const;
    Vector3 operator-() const;
    Vector3& operator+=(const Vector3& v);
    Vector3& operator-=(const Vector3& v);
    Vector3& operator*=(float s);
    Vector3& operator/=(float s);

    friend const Vector3 operator+(const Vector3& v1, const Vector3& v2);
    friend const Vector3 operator-(const Vector3& v1, const Vector3& v2);
    friend const Vector3 operator*(const Vector3& v, float s);
    friend const Vector3 operator*(float s, const Vector3& v);
    friend const Vector3 operator/(const Vector3& v, float s);
};

#endif // !_VECTOR3_H_
