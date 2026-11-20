#include <bits/stdc++.h>
using namespace std;

void ator(int s)
{
    vector<pair<int, string>> romanNumerals = {
        {1000, "M"},
        {900, "CM"},
        {500, "D"},
        {400, "CD"},
        {100, "C"},
        {90, "XC"},
        {50, "L"},
        {40, "XL"},
        {10, "X"},
        {9, "IX"},
        {5, "V"},
        {4, "IV"},
        {1, "I"}};

    string result = "";
    for (auto &[value, numeral] : romanNumerals)
    {
        while (s >= value)
        {
            s -= value;
            result += numeral;
        }
    }
    cout << result << "\n";
}

void rtoa(string s)
{
    unordered_map<char, int> romanValue = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}};

    int y = 0;
    for (int i = 0; s[i]; i++)
    {
        if (romanValue[s[i + 1]] && romanValue[s[i]] < romanValue[s[i + 1]])
        {
            y += romanValue[s[i + 1]] - romanValue[s[i]];
            ++i;
        }
        else
        {
            y += romanValue[s[i]];
        }
    }
    cout << y << "\n";
}

int main()
{
    string s;
    while (getline(cin, s))
    {
        if (isdigit(s[0]))
        {
            ator(stoi(s));
        }
        else
        {
            rtoa(s);
        }
    }
    return 0;
}