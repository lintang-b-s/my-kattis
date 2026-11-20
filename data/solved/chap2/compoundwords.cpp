#include <bits/stdc++.h>
using namespace std;

int main()
{
    string input;

    vector<string> words;
    while (getline(cin, input))
    {
        istringstream ss(input);

        string word;
        while (getline(ss, word, ' '))
        {
            words.push_back(word);
        }
    }

    int n = words.size();

    set<string> compoundWords;

    for (int i = 0; i < n; i++)
    { // O(n^2 * logn)
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                continue;
            }
            compoundWords.insert(words[i] + words[j]);
        }
    }

    for (auto ww : compoundWords)
    {
        cout << ww << endl;
    }
}