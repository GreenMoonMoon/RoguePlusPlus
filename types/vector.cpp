#include "vector.h"
#include <cmath>


float Vector2::SquaredLength() const {
    return x * x + y * y;
}

float Vector2::Length() const {
    return sqrt(SquaredLength());
}

float Vector2::Dot(const Vector2 &other) const {
    return x*other.x + y*other.y;
}

Vector2 Vector2::Perpendicular() const {
    return {y, -x};
}

Vector2 Vector2::Normalized() const {
    auto length = Length();
    return {x / length, y / length};
}

void Vector2::Normalize() {
    auto length = Length();
    x /= length;
    y /= length;
}

float Vector3::SquaredLength() const {
    return x * x + y * y + z * z;
}

float Vector3::Length() const {
    return sqrt(SquaredLength());
}

float Vector3::Dot(const Vector3 &other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::Cross(const Vector3 &other) const {
    return {y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x};
}

Vector3 Vector3::Normalized() const {
    auto length = Length();
    return {x / length, y / length, z / length};
}

void Vector3::Normalize() {
    auto length = Length();
    x /= length;
    y /= length;
    z /= length;
}
