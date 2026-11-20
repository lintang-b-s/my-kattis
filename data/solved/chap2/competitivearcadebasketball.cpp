#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL);
    cout.tie(NULL);
    int n, p, m;
    cin >> n >> p >> m;
    cin.ignore();
    unordered_map<string, int> skorPemain;
    vector<string> pemains;
    for (int i = 0; i < n; i++)
    {
        string pemain;
        getline(cin, pemain);
        skorPemain[pemain] = 0;
        pemains.push_back(pemain);
    }

    for (int i = 0; i < m; i++)
    {
        string pemain;
        int skor;
        cin >> pemain >> skor;
        skorPemain[pemain] += skor;
    }

    bool adaPemenang = false;
    for (auto nama : pemains)
    {
        if (skorPemain[nama] >= p)
        {
            cout << nama << " wins!" << endl;
            adaPemenang=true;
        }
    }
    if (!adaPemenang) {
        cout << "No winner!" << endl;
    }
}