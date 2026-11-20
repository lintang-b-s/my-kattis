#include <bits/stdc++.h>
using namespace std;
int main()
{
    int b, k, g;
    cin >> b >> k >> g;
    double groups = k / g;
    int days = ceil((double)(b - 1) / groups);
    cout << days << endl;
}