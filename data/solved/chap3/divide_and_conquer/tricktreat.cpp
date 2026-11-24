#include <bits/stdc++.h>
using namespace std;
struct point
{
    double x, y;
};
const double INF = 1e9;

double sq_euclidean_dist(double x1, double y1, double x2, double y2)
{
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

double last_child_sqdist(double ox, vector<point> points)
{
    double d = -INF;
    for (auto p : points)
    {
        d = max(sq_euclidean_dist(ox, 0, p.x, p.y), d);
    }
    return d;
}

double ternary_search(vector<point> points, double hi, double lo)
{ // O(log(hi-lo))
    for (int i = 0; i < 100; ++i)
    {
        double delta = (hi - lo) / 3.0;
        double m1 = lo + delta;
        double m2 = hi - delta;
        (last_child_sqdist(m1, points) > last_child_sqdist(m2, points)) ? lo = m1 : hi = m2;
    }
    return lo;
}

int main()
{
    int n;
    while (cin >> n)
    {
        if (n == 0)
        {
            break;
        }

        vector<point> points(n);
        double hi = -INF;
        double lo = INF;
        for (int i = 0; i < n; i++)
        {
            cin >> points[i].x >> points[i].y;
            hi = max(hi, points[i].x);
            lo = min(lo, points[i].x);
        }

        auto ox = ternary_search(points, hi, lo);
        auto last_child = points[n - 1];
        auto dist = sqrt(last_child_sqdist(ox, points));

        cout << fixed << setprecision(10) << ox << " " << dist << endl;
    }
}