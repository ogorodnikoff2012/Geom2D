#include <iostream>
#include <vector>
#include "vector.h"
#include "polygon.h"

using namespace std;

int main()
{
    fixed(cout);
    int n;
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

    for(int i = 0; i < v.size(); i++)
    {
        cout <<  v[i] << '\n';
    }


    return 0;
}
