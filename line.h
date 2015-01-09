#ifndef LINE_H
#define LINE_H

namespace geom2d {

class Vector;

class Line
{
public:
    double a, b, c;
    bool isValid;
    Line(const double a, const double b, const double c, const bool isValid = true) :
        a(a),
        b(b),
        c(c),
        isValid(isValid)
    {

    }

    Line(const bool isValid = true) :
        a(0),
        b(1),
        c(0),
        isValid(isValid)
    {

    }

    Line(const Vector &A, const Vector &B, const bool isValid = true);
    double dist(const Vector &A) const;
    Vector intersect(const Line &l) const;
    Line normalize();
    Line normalized() const;
    Vector getNormal() const;
    bool operator ||(const Line &l) const;
    int where(const Vector &v) const;
    bool operator ==(const Line &l) const;
    Vector projection(const Vector &v) const;
    void moveToVector(const Vector &v);
};
}
#endif // LINE_H
