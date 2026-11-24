#include <bits/stdc++.h>
using namespace std;
// https://open.kattis.com/problems/suspensionbridges

double EPS = 1e-8;

double hitung_sag(double d, double a)
{
    double sag = a * cosh(d / (2 * a)) - a;
    return sag;
}

double bsta_sag_jembatan(double d, double s)
{
    double low = 0, high = 1e9;
    double a = 0;

    for (int i = 0; i < 100000; i++)
    { // O(log(hi-lo))
        double mid = (low + high) / 2;
        double coba_sag = hitung_sag(d, mid);
        if (coba_sag >= s)
        {
            a = mid;
            low = mid;
        }
        else
        {
            high = mid;
        }
    }

    return 2 * a * sinh(d / (2 * a));
}

int main()
{
    double d, s;
    cin >> d >> s;
    cout.precision(12);
    cout << bsta_sag_jembatan(d, s) << endl;
}
