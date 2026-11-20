#include <bits/stdc++.h>
using namespace std;

typedef unsigned char uc;

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    vector<int> res(n);
    for (int i = 0; i < n; i++)
    {
        auto a = arr[i];

        uc b = 0;
        for (int j = 0; j <= 255; j++)
        {
           
            uc sc = ((uc)b ^ ((uc)b << 1));
            if (sc == a)
            {
                res[i] = b;
            }
            b++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << res[i];
        if (i < n - 1)
        {
            cout << " ";
        }
    }
}