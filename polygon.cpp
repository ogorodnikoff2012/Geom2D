#include "polygon.h"
#include <cmath>
#include "math_ext.h"
#include <algorithm>
#include "line.h"
#include "vector.h"

using namespace std;
using namespace geom2d;

Polygon::Polygon(const std::vector<Vector> &points, const bool isValid_) :
    points(points)
{
    isValid = isValid_;
    for (int i = 0; i < (int) points.size(); i++)
    {
        isValid &= points[i].isValid;
    }
}

double Polygon::area() const
{
    if (!isValid)
    {
        return -100;
    }

    double ans = 0;
    int n = points.size();

    for (int i = 0; i < n - 1; i++)
    {
        ans += points[i] / (points[i + 1]);
    }

    ans += points[n - 1] / (points[0]);
    return fabs(ans / 2.0);
}

bool Polygon::isConvex() const
{
    if (!isValid)
    {
        return false;
    }
    int n = points.size();
    int sign = signum((points[1] - points[0]) / (points[n - 1] - points[0]));

    for (int i = 1; i < n - 1; i++)
    {
        if (signum((points[i + 1] - points[i]) / (points[i - 1] - points[i])) !=
                sign)
        {
            return false;
        }
    }

    return true;
}

bool Polygon::hasPoint(const Vector &v) const
{
    if (!(isValid && v.isValid))
    {
        return false;
    }

    double ans = 0;
    int n = points.size();

    for (int i = 0; i < n; i++)
        if (points[i] == v)
        {
            return true;
        }

    for (int i = 0; i < n - 1; i++)
    {
        ans += (points[i + 1] - v) ^ (points[i] - v);
    }

    ans += (points[0] - v) ^ (points[n - 1] - v);
    return !equal(ans, 0);
}

class HullComparator
{
public:
    Vector base;
    HullComparator(const Vector &base) :
        base(base)
    {

    }
    bool operator ()(const Vector &a, const Vector &b) const
    {
        Vector v1 = a - base, v2 = b - base;
        double c = v1 / v2;
        return c > 0 || (equal(c, 0) && v1.length() < v2.length());
    }
};

Polygon Polygon::convexHull() const
{
    if(!isValid)
    {
        return Polygon(false);
    }

    if (this->points.size() < 3)
    {
        return Polygon(this->points);
    }

    std::vector<Vector> points = this->points;
    int idx = 0;
    int n = points.size();

    for (int i = 1; i < n; i++)
        if (equal(points[i].y, points[idx].y) ? points[i].x < points[idx].x :
                points[i].y < points[idx].y)
        {
            idx = i;
        }

    std::swap(points[idx], points[0]);

    std::sort(points.begin() + 1, points.end(), HullComparator(points[0]));
    std::vector<Vector> stack;
    stack.push_back(points[0]);
    stack.push_back(points[1]);

    for (int i = 2; i < n; i++)
    {
        Vector A = points[i];
        Vector O = stack.back();
        Vector B = stack[stack.size() - 2];

        while (stack.size() > 1 && (A - O) / (B - O) < eps())
        {
            stack.pop_back();
            O = stack.back();
            B = stack[stack.size() - 2];
        }

        stack.push_back(A);
    }

    return Polygon(stack);
}

std::pair<Polygon, Polygon> Polygon::split(const Line &l) const
// l.where(): First -> -1; Second -> 1
{
    if (!(isValid && l.isValid))
    {
        return std::pair<Polygon, Polygon>(Polygon(false), Polygon(false));
    }

    vector<Vector> first, second;
    int lastWhere = l.where(points[0]);
    for (int i = 0; i < (int) points.size(); i++)
    {
        int where = l.where(points[i]);
        if (where * lastWhere == -1)
        {
            Vector intersection = l.intersect(Line(points[i], points[i-1]));
            first.push_back(intersection);
            second.push_back(intersection);
        }

        if (where != 1)
            first.push_back(points[i]);
        if (where != -1)
            second.push_back(points[i]);

        lastWhere = where;
    }

    int where = l.where(points[0]);
    if (where * lastWhere == -1)
    {
        Vector intersection = l.intersect(Line(points[0], points.back()));
        first.push_back(intersection);
        second.push_back(intersection);
    }

    pair<Polygon, Polygon> ans;
    ans.first.points = first;
    ans.first.isValid = first.size() >= 3;
    ans.second.points = second;
    ans.second.isValid = second.size() >= 3;
    return ans;
}

Polygon Polygon::intersection(const Polygon &p) const
{
    if (!(isValid && p.isValid))
    {
        return Polygon(false);
    }

    Polygon ans = p;
    for (int i = 0, n = points.size(); i < n; i++)
    {
        Vector A = points[i], B = points[(i + 1) % n];
        Line l(A, B);
        std::pair<Polygon, Polygon> pp = ans.split(l);
        if (l.where(points[(i + 2) % n]) == 1)
        {
            ans = pp.second;
        }
        else
        {
            ans = pp.first;
        }
    }

    ans.isValid &= ans.points.size() >= 3;

    return ans;
}
