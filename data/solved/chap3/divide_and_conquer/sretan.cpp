#include <bits/stdc++.h>
using namespace std;

int main()
{
    int k;
    cin >> k;
    string ans;
    for (int i = k + 1; i > 1; i /= 2)
    {
        if (i % 2 == 0)
        {
            ans += "4";
        }else {
            ans += "7";
        }
    }
    reverse(ans.begin(), ans.end());
    cout << ans << endl;
}