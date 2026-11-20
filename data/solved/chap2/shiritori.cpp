#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;
    cin >> N;
    unordered_set<string> kataTerucapkan;
    int pecundang = 1;
    bool adil = true;
    char lastChar = '-';

    for (int i = 0; i < N; i++)
    { // O(N)
        string kata;
        cin >> kata;
        if (kataTerucapkan.find(kata) != kataTerucapkan.end() ||
            (lastChar != '-' && kata[0] != lastChar))
        {
            if ((i % 2) == 0)
            {
                pecundang = 1;
            }
            else
            {
                pecundang = 2;
            }
            adil = false;
            break;
        }

        kataTerucapkan.insert(kata);
        lastChar = kata[kata.size() - 1];
    }

    if (!adil)
    {
        cout << "Player " << pecundang << " lost" << endl;
    }
    else
    {
        cout << "Fair Game" << endl;
    }
}