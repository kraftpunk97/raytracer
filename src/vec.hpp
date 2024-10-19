#ifndef VEC_H
#define VEC_H

#include <iostream>

namespace rt {

    class Vec3 {
    public:
        float e[3];

        // Constructors
        Vec3();
        Vec3(float e0, float e1, float e2);

        float x() const;
        float y() const;
        float z() const;

        float operator[](int i) const;
        float& operator[](int i);

        Vec3 operator-() const;

        Vec3& operator+=(const Vec3& v);
        Vec3& operator-=(const Vec3 &v);
        Vec3& operator*=(float t);
        Vec3& operator/=(float t);

        float length() const;
        float len_sq() const;
    };

    // Vector Utility Functions
    inline std::ostream& operator<<(std::ostream& out, const Vec3& v);
    inline Vec3 operator+(const Vec3& v1, const Vec3& v2);
    inline Vec3 operator-(const Vec3& v1, const Vec3& v2);
    inline Vec3 operator*(const Vec3& v1, const Vec3& v2);
    inline Vec3 operator*(const Vec3& v, float t);
    inline Vec3 operator*(float t, const Vec3& v);
    inline Vec3 operator/(const Vec3& v, float t);
    inline float dot(const Vec3& v1, const Vec3& v2);
    inline Vec3 cross(const Vec3& v1, const Vec3& v2);
    inline Vec3 unit_vector(const Vec3& v);
};
#endif