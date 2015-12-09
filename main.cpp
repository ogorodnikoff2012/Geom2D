#include <iostream>
#include <vector>
#include <string>
#include "vector.h"
#include "line.h"
#include "polygon.h"

using namespace std;
using namespace geom2d;

Polygon readPolygon(istream &in)
{
    int n;
    in >> n;
    vector<Vector> v;

    for (int i = 0; i < n; i++)
    {
        Vector A;
        in >> A;
        v.push_back(A);
    }

    return Polygon(v);
}

void writePolygon(ostream &out, const Polygon &p)
{
    if(!p.isValid)
    {
        out << "This polygon doesn't exist.\n";
        return;
    }

    vector<Vector> v = p.points;

    for(int i = 0; i < (int) v.size(); i++)
    {
        out <<  v[i] << '\n';
    }
}

bool color = false;
bool convexHull = false;
bool help = false;

int genConvexHull();

int main()
{
    Vector A(0, 0), B(1, 1);
    Line l(A, B);
    l.moveToVector(Vector(2, 1));
    cout << l.a << ' ' << l.b << ' ' << l.c << '\n';
    return 0;
}

int hrenmain(int argc, char *argv[])
{
    for(int i = 0; i < argc; i++)
    {
        if(string(argv[i]) == "-c")
        {
            color = true;
        }

        if(string(argv[i]) == "-h")
        {
            convexHull = true;
        }

        if(string(argv[i]) == "-?")
        {
            help = true;
        }
    }

    if(help)
    {
        cout << "Usage: " << string(argv[0]) << " [-?] [-c] [-h]\n"
                "Use the key -? to see this help.\n"
                "Use the key -c to enable color IO (not available on some terminals).\n"
                "Use the key -h to run another example.\n";
        return 0;
    }

    if(convexHull)
    {
        genConvexHull();
        return 0;
    }

    fixed(cout);
    if(color)    cout << "\x1b[33m";  // Yellow foreground
    cout << "This is a demo program. \n"
            "It searches an intersection of two convex polygons. ";
    if(color)    cout << "\x1b[37m";  // White foreground
    cout << "O(mn)";
    if(color)    cout << "\x1b[33m";  // Yellow foreground
    cout << "\n";

    cout << "Write the number of first polygon's vertices and their coordinates:\n";
    if(color)    cout << "\x1b[32m"; // Green foreground
    Polygon p1 = readPolygon(cin);
    if(color)    cout << "\x1b[33m"; // Yellow foreground

    cout << "Write the number of second polygon's vertices and their coordinates:\n";
    if(color)    cout << "\x1b[32m"; // Green foreground
    Polygon p2 = readPolygon(cin);
    if(color)    cout << "\x1b[33m"; // Yellow foreground

    cout << "Their intersection:\n";
    if(color)    cout << "\x1b[32m"; // Green foreground
    writePolygon(cout, p1.intersection(p2));
    if(color)    cout << "\x1b[0m"; // Restore default
    return 0;
}

int genConvexHull()
{
    fixed(cout);

    if(color)    cout << "\x1b[33m";  // Yellow foreground
    cout << "This is a demo program. \n"
            "It searches a convex hull for a set of points. ";
    if(color)    cout << "\x1b[37m";  // White foreground
    cout << "O(n log n)";
    if(color)    cout << "\x1b[33m";  // Yellow foreground
    cout << "\n";

    int n;
    cout << "Write the number of points and their coordinates:\n";
    if(color)    cout << "\x1b[32m"; // Green foreground
    cin >> n;
    vector<Vector> v;

    for (int i = 0; i < n; i++)
    {
        Vector A;
        cin >> A;
        v.push_back(A);
    }

    Polygon p(v);
    p = p.convexHull();
    v = p.points;

    if(color)    cout << "\x1b[33m"; // Yellow foreground
    cout << "Convex hull's vertices:\n";

    if(color)    cout << "\x1b[32m"; // Green foreground
    for(int i = 0; i < (int) v.size(); i++)
    {
        cout << v[i] << '\n';
    }

    if(color)    cout << "\x1b[0m"; // Restore default
    return 0;
}
