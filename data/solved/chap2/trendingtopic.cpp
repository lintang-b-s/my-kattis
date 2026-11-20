#include <bits/stdc++.h>

using namespace std;

// https://open.kattis.com/problems/trendingtopic?tab=metadata

int main()
{

    string op;

    vector<unordered_map<string, int>> wordCountMap(1000);
    int day = 0;
    while (cin >> op)
    {
        if (op == "<text>")
        {

            string word;
            cin >> word;
            while (word != "</text>")
            {
                wordCountMap[day][word]++;
                cin >> word;
            }
            day++;
        }
        else
        {
            string gakepake;
            int k;
            cin >> k >> gakepake;

            vector<pair<string, int>> wordsCountV(0);

            int firstDay = day - 7;
            if (firstDay < 0)
            {
                firstDay = 0;
            }

            unordered_map<string, int> wordTotalFreq;
            for (int i = firstDay; i < day; i++)
            {// T(day)<= day*c = O(day). c=20000. max 20000 words per day
                for (auto [word, freq] : wordCountMap[i])
                {
                    if (word.size() < 4)
                    {
                        continue;
                    }
                    wordTotalFreq[word] += freq;
                }
            }

            for (auto [word, freq] : wordTotalFreq)
            {
                wordsCountV.push_back({word, freq});
            }

            sort(wordsCountV.begin(), wordsCountV.end(), [](pair<string, int> a, pair<string, int> b)
                 {
                if   (a.second != b.second) {
                    return a.second > b.second;
                }else 
                {
                    return a.first < b.first;
                } });

            int originalK = k;
            cout << "<top " << k << ">" << endl;
            int lastFreq = 0;

            // k=20000, The maximum number of different words that can appear is 20000
            for (int i = 0; i < k; i++)
            { // O(k)
                cout << wordsCountV[i].first << " " << wordsCountV[i].second << endl;
                lastFreq = wordsCountV[i].second;
            }
            while (k < wordsCountV.size() && wordsCountV[k].second == lastFreq)
            {
                cout << wordsCountV[k].first << " " << wordsCountV[k].second << endl;
                k++;
            }
            cout << "</top>" << endl;
        }
    }

    return 0;
}