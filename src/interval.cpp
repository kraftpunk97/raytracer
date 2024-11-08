#include "interval.hpp"

namespace rt {
    Interval::Interval() {
        min = -inf;
        max =  inf;
    }

    Interval::Interval(double minimum, double maximum) {
        min = minimum; max = maximum;
    }

    double Interval::size() const { return max - min; }

    bool Interval::contains(double x) const { return min <= x && x <= max; }
    bool Interval::surrounds(double x) const { return min < x && x < max; }
    double Interval::clamp(double x) const {
        if (x < min) { return min; }
        if (x > max) { return max; }
        return x;
    }
    
    const Interval Interval::empty = Interval(inf, -inf);
    const Interval Interval::universe = Interval(-inf, inf);
};