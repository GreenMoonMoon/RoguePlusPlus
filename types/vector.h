#ifndef RPP_VECTOR_H
#define RPP_VECTOR_H


struct Vector2 {
    float x;
    float y;

    Vector2(float x, float y) : x(x), y(y) {};

    ~Vector2() = default;

    [[nodiscard]] float SquaredLength() const;

    [[nodiscard]] float Length() const;

    [[nodiscard]] float Dot(const Vector2 &other) const;

    [[nodiscard]] Vector2 Perpendicular() const;

    [[nodiscard]] Vector2 Normalized() const;

    void Normalize();

    inline Vector2 operator+(const Vector2 &other) const {
        return {x + other.x, y + other.y};
    }

    inline Vector2 operator-(const Vector2 &other) const {
        return {x - other.x, y - other.y};
    }

    inline bool operator==(const Vector2 &other) const {
        return SquaredLength() == other.SquaredLength();
//        return (SquaredLength() - other.SquaredLength() == 0.0f);
    }

    inline Vector2 operator*(const float scalar) const {
        return {x * scalar, y * scalar};
    }
};

struct Vector3 {
    float x;
    float y;
    float z;

    Vector3(float x, float y, float z) : x(x), y(y) , z(z) {};

    ~Vector3() = default;

    [[nodiscard]] float SquaredLength() const;

    [[nodiscard]] float Length() const;

    [[nodiscard]] float Dot(const Vector3 &other) const;

    [[nodiscard]] Vector3 Cross(const Vector3 &other) const;

    [[nodiscard]] Vector3 Normalized() const;

    void Normalize();

    inline Vector3 operator+(const Vector3 &other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    inline Vector3 operator-(const Vector3 &other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    inline bool operator==(const Vector3 &other) const {
        return SquaredLength() == other.SquaredLength();
//        return (SquaredLength() - other.SquaredLength() == 0.0f);
    }

    inline Vector3 operator*(const float scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }
};

#endif //RPP_VECTOR_H
