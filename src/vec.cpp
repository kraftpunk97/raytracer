#include <cmath>
#include "vec.hpp"

namespace rt {
    Vec3::Vec3() {
        e[0] = 0;
        e[1] = 0;
        e[2] = 0;
    }

    Vec3::Vec3(double x, double y, double z) {
        e[0] = x;
        e[1] = y;
        e[2] = z;
    }

    double Vec3::x() const { return e[0]; }
    double Vec3::y() const { return e[1]; }
    double Vec3::z() const { return e[2]; }

    double Vec3::operator[](int i) const { return e[i]; }
    double& Vec3::operator[](int i) { return e[i]; }

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

    Vec3& Vec3::operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    Vec3& Vec3::operator/=(double t) {
        e[0] /= t;
        e[1] /= t;
        e[2] /= t;
        return *this;
    }

    double Vec3::len_sq() const { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }
    double Vec3::length() const { return std::sqrt(Vec3::len_sq()); }
};