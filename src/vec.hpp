#ifndef VEC3_H
#define VEC3_H



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

        double length() const;
        double len_sq() const;
    };


};

#endif