#include <bits/stdc++.h>
using namespace std;

int main()
{
    unordered_map<int, int> bahasaTamuPesta;
    int n;
    cin >> n;

    cin.ignore();

    string input;
    getline(cin, input);
    istringstream  ss(input);

    string number = "";

    bool akward = false;

    int minAwkwardness = 1<< 30;
    int pos = 0;
    while (getline(ss, number, ' '))
    {
        int language = stoi(number);
        if (bahasaTamuPesta.find(language) != bahasaTamuPesta.end())
        {
            if (abs(pos - bahasaTamuPesta[language]) < minAwkwardness)
            {
                minAwkwardness = abs(pos - bahasaTamuPesta[language]);
                akward=true;
            }

        }

        bahasaTamuPesta[language] = pos;
        pos++;
    }
    
    if (!akward) {
        cout << pos << endl;
    }else {
        cout << minAwkwardness << endl;
    }
}