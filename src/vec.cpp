#include <cmath>
#include "vec.hpp"

namespace rt {
    Vec3::Vec3() {
        e[0] = 0;
        e[1] = 0;
        e[2] = 0;
    }

    Vec3::Vec3(float x, float y, float z) {
        e[0] = x;
        e[1] = y;
        e[2] = z;
    }

    float Vec3::x() const { return e[0]; }
    float Vec3::y() const { return e[1]; }
    float Vec3::z() const { return e[2]; }

    float Vec3::operator[](int i) const { return e[i]; }
    float& Vec3::operator[](int i) { return e[i]; }

    Vec3 Vec3::operator-() const { return Vec3(-e[0], -e[1], -e[2]); }

    Vec3& Vec3::operator+=(const Vec3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    Vec3& Vec3::operator-=(const Vec3& v) {
        e[0] -= v.e[0];
        e[1] -= v.e[1];
        e[2] -= v.e[2];
        return *this;
    }

    Vec3& Vec3::operator*=(float t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    Vec3& Vec3::operator/=(float t) {
        e[0] /= t;
        e[1] /= t;
        e[2] /= t;
        return *this;
    }

    float Vec3::len_sq() const { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }
    float Vec3::length() const { return std::sqrt(Vec3::len_sq()); }

    inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
        return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
    }

    inline Vec3 operator+(const Vec3& v1, const Vec3& v2) {
        return Vec3(v1.e[0]+v2.e[0], v1.e[1]+v2.e[1], v1.e[2]+v2.e[2]);
    }

    inline Vec3 operator-(const Vec3& v1, const Vec3& v2) {
        return Vec3(v1.e[0]-v2.e[0], v1.e[1]-v2.e[1], v1.e[2]-v2.e[2]);
    }

    inline Vec3 operator*(const Vec3& v1, const Vec3& v2) {
        return Vec3(v1.e[0]*v2.e[0], v1.e[1]*v2.e[1], v1.e[2]*v2.e[2]);
    }

    inline Vec3 operator*(const Vec3& v, float t) {
        return Vec3(v.e[0]*t, v.e[1]*t, v.e[2]*t);
    }

    inline Vec3 operator*(float t, const Vec3& v) {
        return Vec3(v.e[0]*t, v.e[1]*t, v.e[2]*t);
    }

    inline Vec3 operator/(const Vec3& v, float t) {
        return Vec3(v.e[0]/t, v.e[1]/t, v.e[2]/t);
    }

    inline float dot(const Vec3& v1, const Vec3& v2) {
        return (v1.e[0]*v2.e[0])+(v1.e[1]*v2.e[1])+(v1.e[2]*v2.e[2]);
    }

    inline Vec3 cross(const Vec3& v1, const Vec3& v2) {
        return Vec3(v1.e[1]*v2.e[2]-v1.e[2]*v2.e[1],
                    v1.e[2]*v2.e[0]-v1.e[0]*v2.e[2],
                    v1.e[0]*v2.e[1]-v1.e[1]*v2.e[0]);
    }

    inline Vec3 unit_vector(const Vec3& v) {
        auto len = v.length();
        return Vec3(v.e[0]/len, v.e[1]/len, v.e[2]/len);
    }
};