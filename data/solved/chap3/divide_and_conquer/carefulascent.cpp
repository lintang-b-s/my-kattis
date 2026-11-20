#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/carefulascent

struct pelindung
{
    double l, u, f;
};

const double EPS = 1e-11;

double waktu_vertikal(double ubound, double lbound, double vy, double f)
{
    return ((ubound - lbound) / vy) * f;
}

bool terbang_tinggi_dan_melampauinya(vector<pelindung> &segments, double vx, double xf)
{
    double tot_waktu_multiplier = 0.0;
    for (auto s : segments)
    {
        tot_waktu_multiplier += waktu_vertikal(s.u, s.l, 1, s.f);
    }

    return vx * tot_waktu_multiplier >= xf;
}

double bsta_kecepatan_hori(vector<pelindung> &segments, double xf)
{ // O(log(1e9/EPS))
    double best_kecepatan_hori = 0.0;
    double low = 0.0, high = 1e9;
    while (fabs(high - low) > EPS)
    {
        double mid_vx = (low + high) / 2;
        if (terbang_tinggi_dan_melampauinya(segments, mid_vx, xf))
        {
            best_kecepatan_hori = mid_vx;
            high = mid_vx;
        }
        else
        {
            low = mid_vx;
        }
    }

    return best_kecepatan_hori;
}

int main()
{
    double xf, yf, n;
    vector<pelindung> pelindungs;
    cin >> xf >> yf;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        double l, u, f;
        cin >> l >> u >> f;
        pelindung pp{l, u, f};
        pelindungs.push_back(pp);
    }

    sort(pelindungs.begin(), pelindungs.end(), [](pelindung a, pelindung b)
         { return a.l < b.l; });

    yf = abs(yf);
    double t = yf / 1.0;

    vector<pelindung> segments;
    if (n == 0)
    {
        segments.push_back({0, yf, 1.0});
    }
    else
    {

        segments.push_back({0, pelindungs[0].l, 1.0});

        for (int i = 0; i < n; i++)
        {
            segments.push_back(pelindungs[i]);
            if (i + 1 < n && pelindungs[i].u < pelindungs[i + 1].u)
            {
                segments.push_back({pelindungs[i].u, pelindungs[i + 1].l, 1.0});
            }
        }

        segments.push_back({pelindungs[n - 1].u, yf, 1.0});
    }

    cout.precision(12);

    int sign = (xf < 0) ? -1.0 : 1.0;

    cout << sign * bsta_kecepatan_hori(segments, abs(xf)) << endl; // O(log(1e9/EPS))
}