#include <bits/stdc++.h>
using namespace std;

// josephus problem brute force

int main()
{
    string lagu;
    getline(cin, lagu);

    istringstream ss(lagu);
    string word;
    int k = 0;
    while (getline(ss, word, ' '))
    {
        k++;
    }

    int n;
    cin >> n;
    vector<string> bocils;
    for (int i = 0; i < n; i++)
    {
        string bocil;
        cin >> bocil;
        bocils.push_back(bocil);
    }

    int i = 0;
    int mulai = 0;
    vector<string> teams1, teams2;
    while (n > 1)
    { // O(n^2)
        auto bocil = bocils[(mulai + k - 1) % n];
        if (i % 2 == 0)
        {
            teams1.push_back(bocil);
        }
        else
        {
            teams2.push_back(bocil);
        }
        int next = 0;
        for (int j = 0; j < n; j++)
        {
            if (bocils[j] == bocil)
            {
                next = j;
            }
        }

        bocils.erase(bocils.begin() + (mulai + k - 1) % n);
        n = bocils.size();
        mulai = next % n;
        i++;
    }
    if (i % 2 == 0)
    {
        teams1.push_back(bocils[0]);
    }
    else
    {
        teams2.push_back(bocils[0]);
    }

    cout << teams1.size() << endl;
    for (auto t : teams1)
    {
        cout << t << endl;
    }
    cout << teams2.size() << endl;
    for (auto t : teams2)
    {
        cout << t << endl;
    }
}