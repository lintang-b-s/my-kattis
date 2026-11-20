#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    cin >> N;

    cin.ignore();

    for (int i = 0; i < N; i++)
    {
        string s;
        getline(cin, s);
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        int freq[95] = {0};
        for (int j = 0; j < s.size(); j++)
        { // O(len(s))
            freq[s[j] - ' ']++;
        }

        bool pangram = true;
        int missingsChar[26];
        memset(missingsChar, 0, sizeof(missingsChar));

        for (int j = 97; j < 97 + 26; j++)
        { // 26 ops
            int freqId = j - 32;
            if (freq[freqId] == 0)
            {
                pangram = false;
                missingsChar[j - 'a'] = 1;
            }
        }

        if (pangram)
        {
            cout << "pangram" << endl;
        }
        else
        {
            cout << "missing ";
            for (int j = 0; j < 26; j++)
            { /// 26 ops
                if (missingsChar[j] == 1)
                {
                    char misChar = j + 97;
                    cout << misChar;
                }
            }
            cout << endl;
        }
    }
}