#ifndef __MY_MATH_H__
#define __MY_MATH_H__

#include <algorithm>
using namespace std;

const float EPS = 1e-5;
const float INF = 1e5;

struct Interval{
    float l, r;
    // constructor
    Interval(float a = 0.0f, float b = 1.0f) : l(a), r(b) {}
    // overload =
    void operator = (const Interval &a){
        l = a.l;
        r = a.r;
    }
    // intersect
    static Interval Intersection(const Interval &a, const Interval &b){
        if (a.l > a.r + EPS || b.l > b.r + EPS) {
            return Interval(1.0f, 0.0f);
        }
        if (a.l > b.r + EPS || b.l > a.r + EPS) {
            return Interval(1.0f, 0.0f);
        }
        return Interval(max(a.l, b.l), min(a.r, b.r));
    }
    void Intersect(const Interval &a){
        *this = Intersection(*this, a);
    }
};

#endif 