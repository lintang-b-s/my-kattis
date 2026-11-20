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
        if (fabs(x - other.x) > EPS)
            return x < other.x;
        return y < other.y;
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

int sign(vec a, vec b)
{
    double cp = cross(a, b);
    if (cp < 0)
    {
        return -1;
    }
    else if (cp == 0)
    {
        return 0;
    }
    return 1;
}

bool collinear(point p, point q, point r)
{
    return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
}

vector<point> CH_Andrew(vector<point> &pts)
{// O(nlogn)
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

double eucdist(point a, point b)
{
    double xx = (a.x - b.x);
    double yy = (a.y - b.y);
    return sqrt(xx * xx + yy * yy);
};

// https://codeforces.com/blog/entry/133763
// O(n)
double all_anti_podal(int n, vector<point> &pts)
{
    int p1 = 0, p2 = 0;
    vector<pair<int, int>> res;

    vector<bool> vis(n, false);

    double diameter = 0.0;

    for (; p1 < n; p1++)
    {
        auto v1 = toVec(pts[p1], pts[(p1 + 1) % n]);

        while (p2 == p1 || p2 == (p1 + 1) % n ||
               sign(v1, toVec(pts[p2], pts[(p2 + 1) % n])) ==
                   sign(v1, toVec(pts[(p2 - 1 + n) % n], pts[p2])))
        {
            p2 = (p2 + 1) % n;
        }

        if (vis[p1])
        {
            continue;
        }

        vis[p1] = true;
        res.push_back({p1, p2});

        double apDiam = eucdist(pts[p1], pts[p2]);
        if (apDiam > diameter)
        {
            diameter = apDiam;
        }

        res.push_back({(p1 + 1) % n, p2});

        apDiam = eucdist(pts[(p1 + 1) % n], pts[p2]);
        if (apDiam > diameter)
        {
            diameter = apDiam;
        }

        // if both edges from p1 and p2 are parallel to each other
        if (cross(v1, toVec(pts[p2], pts[(p2 + 1) % n])) == 0)
        {
            res.push_back({p1, (p2 + 1) % n});
            res.push_back({(p1 + 1) % n, (p2 + 1) % n});

            apDiam = eucdist(pts[p1], pts[(p2 + 1) % n]);
            if (apDiam > diameter)
            {
                diameter = apDiam;
            }

            apDiam = eucdist(pts[(p1 + 1) % n], pts[(p2 + 1) % n]);
            if (apDiam > diameter)
            {
                diameter = apDiam;
            }

            vis[p2] = true;
        }
    }

    return diameter;
}

int main()
{
    int n;
    cin >> n;

    vector<point> pts;

    for (int i = 0; i < n; i++)
    {
        double x, y;
        cin >> x >> y;
        point p({x, y});
        pts.push_back(p);
    }
    cout.precision(12);

    if (pts.size() == 2)
    {
        double diameter = eucdist(pts[0], pts[1]);

        cout << diameter << "\n";
    }
    else
    {
        vector<point> ch = CH_Andrew(pts);
        ch.pop_back();
        if (ch.size() < 2)
        {
            cout << 0.0 << endl;
            return 0;
        }
        if (ch.size() == 2)
        {
            double diameter = eucdist(pts[0], pts[1]);

            cout << diameter << "\n";
            return 0;
        }

        double diameter = all_anti_podal(ch.size(), ch);

        cout << diameter << "\n";
    }
}