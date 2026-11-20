#include <bits/stdc++.h>

using namespace std;

int main()
{
    cin.tie(NULL);
    cout.tie(NULL);

    unordered_map<string, int> votes;
    string pilihanKandidat;
    while (getline(cin, pilihanKandidat))
    {
        if (pilihanKandidat == "***")
        {
            break;
        }
        votes[pilihanKandidat]++;
    }
    int max = -1;

    string pemenang = "";
    bool putaranKedua = false;
    for (auto [kandidat, jumlahVote] : votes)
    { // O(len(votes))
        if (jumlahVote > max)
        {
            max = jumlahVote;
            pemenang = kandidat;
            putaranKedua = false;
        }
        else if (jumlahVote == max)
        {
            putaranKedua = true;
        }
    }
    if (!putaranKedua)
    {
        cout << pemenang << endl;
    }else {
        cout << "Runoff!" << endl;
    }
}