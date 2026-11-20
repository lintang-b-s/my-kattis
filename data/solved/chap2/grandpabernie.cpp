#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    unordered_map<string, vector<int>> memoriKakek;
    for (int i = 0; i < n; i++)
    { // O(n)
        string negara;
        int tahunBerkunjung;
        cin >> negara >> tahunBerkunjung;
        if (memoriKakek.find(negara) == memoriKakek.end())
        {
            vector<int> tahunBerkunjungNegara = {tahunBerkunjung};
            memoriKakek[negara] = tahunBerkunjungNegara;
        }
        else
        {
            memoriKakek[negara].push_back(tahunBerkunjung);
        }
    }

    for (auto &[negaraYangKakekKunjungi, tahuns] : memoriKakek)
    {
        sort(tahuns.begin(), tahuns.end());
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    { // O(q)
        string negara;
        int k;
        cin >> negara >> k;
        cout << memoriKakek[negara][k-1] <<endl;
    }
}