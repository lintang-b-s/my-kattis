#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, p, k;
    cin >> n >> p >> k;

    vector<double> speedupTime(n);
    for (int i = 0; i < n; i++)
    {
        cin >> speedupTime[i];
    }

    double tot = 0;
    tot += speedupTime[0] - 0;
    speedupTime.push_back(k);
    for (int i = 1; i <= n; i++)
    {
        tot += (speedupTime[i] - speedupTime[i - 1]) * ((100.0 + i * p) / 100.0);
    }

    cout << fixed << setprecision(10) << tot << endl;
}