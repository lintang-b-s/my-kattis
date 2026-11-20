#include <bits/stdc++.h>

using namespace std;

int main()
{
    cin.tie(NULL);
    cout.tie(NULL);

    int freq[94];
    memset(freq, 0, sizeof(freq));

    string s;
    cin >> s;

    for (int i = 0; i < s.size(); i++)
    { // O(len(s))
        freq[s[i] - '!']++;
    }

    int lowercaseCount = 0, uppercaseCount = 0;
    int symbolCount = 0;

    for (int i = 0; i < 94; i++)
    { // 94 operations
        int asciiId = i + 33;
        if (asciiId >= 65 && asciiId <= 90)
        {
            uppercaseCount += freq[i];
        }
        else if (asciiId >= 97 && asciiId <= 122)
        {
            lowercaseCount += freq[i];
        }
        else if (asciiId != 95)
        {
            symbolCount += freq[i];
        }
    }

    cout << (double)freq[95 - 33] / (double)s.size() << endl;
    cout << (double)lowercaseCount / (double)s.size() << endl;
    cout << (double)uppercaseCount / (double)s.size() << endl;
    cout << (double)symbolCount / (double)s.size() << endl;
}