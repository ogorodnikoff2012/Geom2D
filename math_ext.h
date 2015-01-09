#ifndef MATH_EXT_H
#define MATH_EXT_H

namespace geom2d
{

double eps();
double toRadians(const double deg);
double toDegrees(const double rad);
bool equal(const double a, const double b);
int signum(double a);
double max(double a, double b);

}

#endif // MATH_EXT_H
