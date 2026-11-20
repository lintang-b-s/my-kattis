#include <bits/stdc++.h>
using namespace std;

const double INF = 1e9;
const double EPS = 1e-9;

double DEG_to_RAD(double d) { return d * M_PI / 180.0; }

double RAD_to_DEG(double r) { return r * 180.0 / M_PI; }

struct point
{
    double x, y;
    point() { x = y = 0.0; }
    point(double _x, double _y) : x(_x), y(_y) {}
    bool operator<(point other) const
    {
        if (fabs(y - other.y) > EPS)
            return y < other.y;
        return x < other.x;
    }

    bool operator==(point other) const
    {
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
    }
};

struct vec
{
    double x, y;
    vec(double _x, double _y) : x(_x), y(_y) {}
};

double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

vec toVec(const point &a, const point &b)
{
    return vec(b.x - a.x, b.y - a.y);
}

bool ccw(point p, point q, point r)
{
    return cross(toVec(p, q), toVec(p, r)) > EPS;
}
bool collinear(point p, point q, point r)
{
    return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
}

vector<point> CH_Andrew(vector<point> &pts)
{
    int n = pts.size();
    int k = 0;
    vector<point> H(2 * n);

    sort(pts.begin(), pts.end());

    for (int i = 0; i < n; i++)
    {
        while ((k >= 2) && (!ccw(H[k - 2], H[k - 1], pts[i])))
        {
            k--;
        }

        H[k++] = pts[i];
    }

    int t = k + 1;
    for (int i = n - 2; i >= 0; i--)
    {
        while ((k >= t) && (!ccw(H[k - 2], H[k - 1], pts[i])))
        {
            k--;
        }

        H[k++] = pts[i];
    }

    H.resize(k);
    return H;
}

double area(const vector<point> pts)
{
    double ans = 0.0;
    for (int i = 0; i < pts.size() - 1; i++)
    {

        ans += (pts[i].x * pts[i + 1].y - pts[i + 1].x * pts[i].y);
    }

    return fabs(ans) / 2.0;
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

        vector<point> pts;

        for (int i = 0; i < n; i++)
        {
            double x, y;
            cin >> x >> y;
            point p({x, y});
            pts.push_back(p);
        }

        auto ch = CH_Andrew(pts);
        double ans = area(ch);
        cout << ans << "\n";
    }
}