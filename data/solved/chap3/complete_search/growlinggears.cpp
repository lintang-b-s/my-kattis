#include <bits/stdc++.h>
using namespace std;

double getTorque(int a, int b, int c, double r)
{
    return -a * r * r + b * r + c;
}

int main()
{
    int q;
    cin >> q;

    for (int j = 0; j < q; j++)
    {
        int n;
        cin >> n;
        double maxtorq = -numeric_limits<double>::max();
        int bestgir = 1;
        for (int i = 0; i < n; i++)
        {
            int a, b, c;
            cin >> a >> b >> c;
            double rmax = b / (2.0 * a);
            double torque = getTorque(a, b, c, rmax);
            if (torque > maxtorq)
            {
                maxtorq = max(maxtorq, torque);
                bestgir = i + 1;
            }
        }
        cout << bestgir << endl;
    }
}