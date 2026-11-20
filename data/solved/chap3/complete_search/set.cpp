#include <bits/stdc++.h>
using namespace std;

struct cardType
{
    int a;
    char b, c, d;
};

int main()
{

    cardType cards[12];
    for (int i = 0; i < 12; i++)
    {
        string card;
        cin >> card;

        int num = card[0] - '0';
        cardType cc{num, card[1], card[2], card[3]};
        cards[i] = cc;
    }

    vector<vector<int>> res;

    // 12^3
    for (int i = 0; i < 12; i++)
    {
        for (int j = i + 1; j < 12; j++)
        {
            for (int k = j + 1; k < 12; k++)
            {
                bool valid = true;
                auto c1 = cards[i];
                auto c2 = cards[j];
                auto c3 = cards[k];
                if (!((c1.a != c2.a && c1.a != c3.a && c2.a != c3.a) || (c1.a == c2.a && c1.a == c3.a && c2.a == c3.a)))
                {
                    valid = false;
                }
                if (!((c1.b != c2.b && c1.b != c3.b && c2.b != c3.b) || (c1.b == c2.b && c1.b == c3.b && c2.b == c3.b)))
                {
                    valid = false;
                }

                if (!((c1.c != c2.c && c1.c != c3.c && c2.c != c3.c) || (c1.c == c2.c && c1.c == c3.c && c2.c == c3.c)))
                {
                    valid = false;
                }

                if (!((c1.d != c2.d && c1.d != c3.d && c2.d != c3.d) || (c1.d == c2.d && c1.d == c3.d && c2.d == c3.d)))
                {
                    valid = false;
                }

                if (valid)
                {
                    res.push_back({i + 1, j + 1, k + 1});
                }
            }
        }
    }

    sort(res.begin(), res.end(), [](vector<int> a, vector<int> b)
         {
             if (a[0] != b[0])
             {
                 return a[0] < b[0];
             }
             else if (a[1] != b[1])
             {
                 return a[1] < b[1];
             }
             return a[2] < b[2]; });

    if (res.empty())
    {
        cout << "no sets" << endl;
    }
    for (int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res[i].size(); j++)
        {
            cout << res[i][j];
            if (j < res[i].size() - 1)
            {
                cout << " ";
            }
        }
        cout << endl;
    }
}
