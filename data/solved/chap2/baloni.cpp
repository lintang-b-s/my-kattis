#include <bits/stdc++.h>

using namespace std;
// https://open.kattis.com/problems/baloni?tab=metadata

int main()
{
    int n;
    cin >> n;

    vector<int> arrows(n + 1, 0);

    int tembakPanah = 0;
    for (int i = 0; i < n; i++)
    { // O(n)
        int tinggiBalon;
        cin >> tinggiBalon;
        if (arrows[tinggiBalon] > 0)
        {
            arrows[tinggiBalon]--;
        }
        else
        {
            tembakPanah++;
        }

        arrows[tinggiBalon-1]++;
    }
    cout << tembakPanah;
}
