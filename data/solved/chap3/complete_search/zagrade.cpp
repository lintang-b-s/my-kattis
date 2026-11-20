#include <bits/stdc++.h>
using namespace std;

int LSONE(int s)
{
    return s & -(s);
}

int main()
{
    string input;
    cin >> input;
    stack<pair<char, int>> st;

    vector<pair<int, int>> pairs;

    for (int i = 0; i < input.size(); i++)
    {

        if (input[i] == '(')
        {
            st.push({'(', i});
        }
        else if (input[i] == ')')
        {

            pairs.push_back({st.top().second, i});
            st.pop();
        }
    }

    int n = pairs.size();

    vector<vector<int>> subsets;
    for (int mask = 0; mask < (1 << n); mask++)
    { // O(2^n)
        vector<int> subset;
        int m = mask;
        while (m)
        {
            int two_pow_j = LSONE(m);
            int j = __builtin_ctz(two_pow_j);
            subset.push_back(j);
            m -= two_pow_j;
        }
        subsets.push_back(subset);
    }

    set<string> outputs;
    for (int i = 0; i < subsets.size(); i++)
    {
        auto subset = subsets[i];
        if (subset.size() == 0)
        {
            continue;
        }
        string output = input;
        for (int j = 0; j < subset.size(); j++)
        {
            auto pair = pairs[subset[j]];
            output[pair.first] = ' ';
            output[pair.second] = ' ';
        }

        string correct = "";
        for (char c : output)
        {

            if (c != ' ')
            {
                correct += c;
            }
        }

        outputs.insert(correct);
    }
    for (auto o : outputs)
    {
        cout << o << endl;
    }
}