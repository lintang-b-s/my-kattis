#include <bits/stdc++.h>

using namespace std;

int main()
{
    cin.tie(NULL);
    cout.tie(NULL);
    int n, r;
    cin >> r >> n;

    bool rooms[r];
    memset(rooms, false, sizeof(rooms));

    for (int i = 0; i < n; i++)
    { // O(n)
        int a;
        cin >> a;
        rooms[a - 1] = true;
    }

    bool tooLate = true;
    for (int i = 0; i < r; i++)
    { // O(r)
        if (!rooms[i])
        {
            cout << i + 1 << endl;
            tooLate = false;
            break;
        }
    }
    if (tooLate)
    {
        cout << "too late" << endl;
    }
}