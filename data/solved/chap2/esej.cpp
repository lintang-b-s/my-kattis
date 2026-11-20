#include <bits/stdc++.h>
using namespace std;

int main()
{
    srand(time(0));

    int A, B;
    cin >> A >> B;
    int diff = B - A;

    string alphabet = "abcdefghijklmnopqrstuvwxyz";

    int maxWordEssayRand = A + rand() % (B - A + 1);

    bool selesai = false;
    vector<string> essayWords;
    unordered_set<string> kamus;
    int jumlahKata = 0;
    while (!selesai)
    {
        if (jumlahKata >= maxWordEssayRand && kamus.size() >= B / 2)
        {
            selesai = true;
            break;
        }
        int panjangKata = (rand() % 15);
        string kata = "";
        panjangKata += 1;

        for (int i = 0; i < panjangKata; i++)
        {
            int randomChar = rand() % 26;
            kata += alphabet[randomChar];
        }

        if (kamus.find(kata) == kamus.end())
        {
            kamus.insert(kata);
            essayWords.push_back(kata);
            jumlahKata++;
        }
    }

    string essay = "";
    for (int i = 0; i < essayWords.size(); i++)
    {
        essay += essayWords[i];
        if (i < essayWords.size() - 1)
        {
            essay += " ";
        }
    }
    cout << essay << endl;
}
