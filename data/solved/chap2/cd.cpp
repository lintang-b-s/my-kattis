#include <bits/stdc++.h>

using namespace std;
int main()
{
    int jack = 0, jill = 0;
    while (cin >> jack >> jill)
    {

        if (jack == 0 && jill == 0)
        {
            break;
        }

        unordered_set<int> jackCDs;

        for (int i = 0; i < jack; i++)
        {
            int a;
            cin >> a;

            jackCDs.insert(a);
        }

        int jackJillCDs = 0;

        for (int i = 0; i < jill; i++)
        {
            int a;
            cin >> a;

            if (jackCDs.find(a) != jackCDs.end())
            {
                jackJillCDs++;
            }
        }
        cout << jackJillCDs << endl;
    }
}