#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool is_vowel(char c)
{
    return (c == 'A' || c == 'I' || c == 'E' || c == 'O' || c == 'U' || c == 'v');
}

bool is_consonant(char c)
{
    return !is_vowel(c) && c != '_';
}

// O(2^n), n = number of blank chars. backtracking recursion tree 2 children nodes each node with height=n. pruning gak ngaruh ke upper bound nya
void backtrack(int i, string ss, vector<int> blank_pos, ll &count, bool with_l)
{
    if (i == blank_pos.size())
    {

        ll curr = 1;

        for (int j = 0; j < blank_pos.size(); j++)
        {
            if (ss[blank_pos[j]] == 'c')
            {
                if (with_l)
                {
                    curr *= 21;
                }
                else
                {
                    curr *= 20;
                }
            }
            else if (ss[blank_pos[j]] == 'v')
            {

                curr *= 5;
            }
        }

        count += curr;

        return;
    }

    int pos = blank_pos[i];

    bool is_valid = true;
    ss[pos] = 'v';
    if (pos > 0 && pos + 1 < ss.size())
    {
        if (is_vowel(ss[pos + 1]) && is_vowel(ss[pos - 1]))
        {
            is_valid = false;
        }
    }
    if (pos > 1)
    {
        if (is_vowel(ss[pos - 1]) && is_vowel(ss[pos - 2]))
        {
            is_valid = false;
        }
    }

    if (pos + 2 < ss.size())
    {
        if (is_vowel(ss[pos + 1]) && is_vowel(ss[pos + 2]))
        {
            is_valid = false;
        }
    }

    if (is_valid)
    {
        backtrack(i + 1, ss, blank_pos, count, with_l);
    }
    ss[pos] = '_';

    is_valid = true;
    ss[pos] = 'c';
    if (pos > 0 && pos + 1 < ss.size())
    {
        if (is_consonant(ss[pos + 1]) && is_consonant(ss[pos - 1]))
        {
            is_valid = false;
        }
    }
    if (pos > 1)
    {
        if (is_consonant(ss[pos - 1]) && is_consonant(ss[pos - 2]))
        {
            is_valid = false;
        }
    }

    if (pos + 2 < ss.size())
    {
        if (is_consonant(ss[pos + 1]) && is_consonant(ss[pos + 2]))
        {
            is_valid = false;
        }
    }

    if (is_valid)
    {
        backtrack(i + 1, ss, blank_pos, count, with_l);
    }
    ss[pos] = '_';
}

int main()
{
    string ss;
    cin >> ss;
    vector<int> blank_pos;
    int contains_l = false;
    for (int i = 0; i < ss.size(); i++)
    {
        if (ss[i] == '_')
        {
            blank_pos.push_back(i);
        }
        else if (ss[i] == 'L')
        {
            contains_l = true;
        }
    }
    bool is_valid = true;
    for (int j = 1; j < ss.size() - 1; j++)
    {
        if (is_consonant(ss[j + 1]) && is_consonant(ss[j]) && is_consonant(ss[j - 1]))
        {
            is_valid = false;
        }

        if (is_vowel(ss[j + 1]) && is_vowel(ss[j]) && is_vowel(ss[j - 1]))
        {
            is_valid = false;
        }
    }
    if (!is_valid)
    {
        cout << 0 << endl;
        return 0;
    }

    if (contains_l)
    {
        ll count_without_l = 0;
        backtrack(0, ss, blank_pos, count_without_l, true);
        cout << count_without_l << endl;
        return 0;
    }

    ll count_with_l = 0;
    backtrack(0, ss, blank_pos, count_with_l, true);
    ll count_without_l = 0;
    backtrack(0, ss, blank_pos, count_without_l, false);

    cout << count_with_l - count_without_l << endl;
}