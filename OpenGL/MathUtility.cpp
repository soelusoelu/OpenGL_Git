#include "MathUtility.h"
#include <cmath>

const float Math::PI = 3.1415926535897932384626433832795f;

float Math::sqrt(float x) {
    return sqrtf(x);
}

float Math::sin(float degree) {
    return sinf(toRadian(degree));
}

float Math::cos(float degree) {
    return cosf(toRadian(degree));
}

float Math::tan(float degree) {
    return tanf(toRadian(degree));
}

float Math::toRadian(float degree) {
    return degree * PI / 180.f;
}

float Math::toDegree(float radian) {
    return radian * 180.f / PI;
}
