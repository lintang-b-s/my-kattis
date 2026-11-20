#include <bits/stdc++.h>

using namespace std;
// https://open.kattis.com/problems/conversationlog?tab=metadata
int main()
{
    cin.tie(NULL);
    cout.tie(NULL);
    int M;
    cin >> M;
    cin.ignore();
    unordered_map<string, int> wordFreq;
    unordered_map<string, set<string>> kataYangDipakaiUser;

    set<string> setPengguna;

    for (int i = 0; i < M; i++)
    {
        string thread;
        getline(cin, thread);

        istringstream ss(thread);

        bool name = true;
        string threadWord;
        string namaUser = "";
        while (getline(ss, threadWord, ' '))
        {
            if (name)
            {
                namaUser = threadWord;
                setPengguna.insert(namaUser);
                name = false;

                continue;
            }
            wordFreq[threadWord]++;
            kataYangDipakaiUser[threadWord].insert(namaUser);
        }
    }

    vector<pair<string, int>> listKataKata;

    for (auto [word, freq] : wordFreq)
    {
        if (kataYangDipakaiUser[word].size() == setPengguna.size())
        {
            listKataKata.push_back({word, freq});
        }
    }

    sort(listKataKata.begin(), listKataKata.end(), [](pair<string, int> a, pair<string, int> b)
         {
        if (a.second != b.second) {
            
            return a.second > b.second;
        }
        return a.first < b.first; });

    for (auto [word, freq] : listKataKata)
    {
        cout << word << endl;
    }
    if (listKataKata.size() == 0)
    {
        cout << "ALL CLEAR" << endl;
    }
}