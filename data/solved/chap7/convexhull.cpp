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

// vector<point> CH_Graham(vector<point> &Pts)
// { // O(n log n)
//     vector<point> P(Pts);
//     int n = (int)P.size();

//     int P0 = min_element(P.begin(), P.end()) - P.begin();
//     swap(P[0], P[P0]);

//     sort(++P.begin(), P.end(), [&](point a, point b)
//          { return ccw(P[0], a, b); });

//     if (n <= 3)
//     {

//         return P;
//     }

//     vector<point> S({P[n - 1], P[0], P[1]});
//     int i = 2;
//     while (i < n)
//     {
//         int j = (int)S.size() - 1;
//         if (ccw(S[j - 1], S[j], P[i]) )
//         {
//             S.push_back(P[i]);
//             i++;
//         }
//         else
//         {
//             S.pop_back();
//         }
//     }

//     if (S.front() == S.back())
//     {
//         S.erase(S.begin());
//     }

//     return S;
// }
vector<point> CH_Graham(vector<point> P)
{
    int n = P.size();
    if (n <= 1) return P;

    int P0 = min_element(P.begin(), P.end()) - P.begin();
    swap(P[0], P[P0]);

    sort(P.begin() + 1, P.end(), [&](point a, point b)
    {
        double c = cross(toVec(P[0], a), toVec(P[0], b));
        if (fabs(c) > EPS) return c > 0;
        return hypot(a.x - P[0].x, a.y - P[0].y) <
               hypot(b.x - P[0].x, b.y - P[0].y);
    });

    vector<point> S;
    for (auto &p : P)
    {
        while (S.size() >= 2 &&
               cross(toVec(S[S.size()-2], S.back()),
                     toVec(S[S.size()-2], p)) <= EPS)
            S.pop_back();
        S.push_back(p);
    }

    return S;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    while (cin >> n)
    {
        if (n == 0)
        {
            break;
        }
        vector<point> pts;

        set<point> pset;
        for (int i = 0; i < n; i++)
        {
            double x, y;
            cin >> x >> y;
            point P{x, y};
            if (pset.find(P) == pset.end())
            {
                pset.insert(P);
                pts.push_back({x, y});
            }
        }

        vector<point> ch = CH_Graham(pts);

        if (n > 3)
        {
            cout << ch.size() << "\n";

            for (int i = 0; i < ch.size(); i++)
            {
                auto p = ch[i];
                cout << p.x << " " << p.y << "\n";
            }
        }
        else if (n == 3)
        {
            cout << ch.size() << "\n";

            for (int i = 0; i < ch.size(); i++)
            {
                auto p = ch[i];
                cout << p.x << " " << p.y << "\n";
            }
        }
        else
        {
            cout << ch.size() << "\n";

            for (int i = 0; i < ch.size(); i++)
            {
                auto p = ch[i];
                cout << p.x << " " << p.y << "\n";
            }
        }
    }
}
