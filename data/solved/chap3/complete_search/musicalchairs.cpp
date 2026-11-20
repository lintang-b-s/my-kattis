#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> opusNumber(n);
    vector<int> idOpus(n);

    for (int i = 0; i < n; i++)
    {
        cin >> opusNumber[i];
        idOpus[i] = i;
    }

    int mulai = 0;
    while (n > 1)
    { // O(n^2)

        auto opus = opusNumber[mulai];
        auto opusKeluar = opusNumber[(mulai + (opus - 1)) % n];
        auto id = idOpus[(mulai + (opus - 1)) % n];

        int next = 0;
        for (int j = 0; j < n; j++)
        {
            if (idOpus[j] == id)
            {
                next = j;
            }
        }

        opusNumber.erase(opusNumber.begin() + ((mulai + (opus - 1)) % n));
        idOpus.erase(idOpus.begin() + ((mulai + (opus - 1)) % n));

        n = opusNumber.size();
        mulai = next % n;
    }

    cout << idOpus[0] + 1 << endl;
}
