#ifndef INTERVAL_H
#define INTERVAL_H

#include "utils.hpp"

namespace rt {
    class Interval {
    public:
        double min, max;
        static const Interval empty, universe;

        Interval();
        Interval(double minimum, double maximum);

        double size() const;
        bool contains(double x) const;
        bool surrounds(double x) const;
        double clamp(double x) const;
    };
};

#endif