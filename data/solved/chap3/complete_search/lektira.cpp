#include <bits/stdc++.h>
using namespace std;

int main()
{
    string word;
    cin >> word;
    string word1, word2, word3;
    int n = word.size();
    vector<string> words;
    // O(n^3)
    for (int i = 1; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            word1 = word.substr(0, i);
            word2 = word.substr(i, j - i);
            word3 = word.substr(j, n - j);

            int n1 = word1.size();
            int n2 = word2.size();
            int n3 = word3.size();

            int l = 0, r = n1 - 1;
            while (l <= r)
            {
                swap(word1[l], word1[r]);
                l++,
                    r--;
            }

            l = 0, r = n2 - 1;
            while (l <= r)
            {
                swap(word2[l], word2[r]);
                l++, r--;
            }

            l = 0, r = n3 - 1;
            while (l <= r)
            {
                swap(word3[l], word3[r]);
                l++, r--;
            }
            words.push_back(word1 + word2 + word3);
        }
    }
    sort(words.begin(), words.end());
    cout << words[0] << endl;
}