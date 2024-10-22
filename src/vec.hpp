#ifndef VEC_H
#define VEC_H

#include <iostream>

namespace rt {

    class Vec3 {
    public:
        double e[3];

        // Constructors
        Vec3();
        Vec3(double e0, double e1, double e2);

        double x() const;
        double y() const;
        double z() const;

        double operator[](int i) const;
        double& operator[](int i);

        Vec3 operator-() const;

        Vec3& operator+=(const Vec3& v);
        Vec3& operator-=(const Vec3 &v);
        Vec3& operator*=(double t);
        Vec3& operator/=(double t);

        static Vec3 random();
        static Vec3 random(double min, double max);

        double length() const;
        double len_sq() const;
    };

    // Vector Utility Functions
    
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

    inline Vec3 operator*(const Vec3& v, double t) {
        return Vec3(v.e[0]*t, v.e[1]*t, v.e[2]*t);
    }

    inline Vec3 operator*(double t, const Vec3& v) {
        return Vec3(v.e[0]*t, v.e[1]*t, v.e[2]*t);
    }

    inline Vec3 operator/(const Vec3& v, double t) {
        return Vec3(v.e[0]/t, v.e[1]/t, v.e[2]/t);
    }

    inline double dot(const Vec3& v1, const Vec3& v2) {
        return (v1.e[0]*v2.e[0])+(v1.e[1]*v2.e[1])+(v1.e[2]*v2.e[2]);
    }

    inline Vec3 cross(const Vec3& v1, const Vec3& v2) {
        return Vec3(v1.e[1]*v2.e[2]-v1.e[2]*v2.e[1],
                    v1.e[2]*v2.e[0]-v1.e[0]*v2.e[2],
                    v1.e[0]*v2.e[1]-v1.e[1]*v2.e[0]);
    }

    inline Vec3 unit_vector(const Vec3& v) {
        auto len = v.length();
        return Vec3(v.e[0], v.e[1], v.e[2])/len;
    }

    inline Vec3 random_unit_vector() {
        // Generate a random vector and check if its length is <= 1.
        
        Vec3 random_vector;
        double len_squared;
        do {
            random_vector = Vec3::random();
            len_squared = random_vector.len_sq();
        } while (len_squared>1 || len_squared<1e-160);  // Checking for underflow as well.
        return unit_vector(random_vector);
    }

    inline Vec3 random_on_hemisphere(const Vec3& normal) {
        // Generate a random unit vector, and check its dot with the 
        // normal.

        auto random_unit_vec = random_unit_vector();
        if (dot(random_unit_vec, normal) > 0) { return random_unit_vec; }
        else { return -random_unit_vec; }
    }

};
#endif