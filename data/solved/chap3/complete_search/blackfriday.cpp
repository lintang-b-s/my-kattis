#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;
const ll INF = ((ll)1 << 62) - 1;

int main()
{
    int n;
    cin >> n;
    vector<int> as;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        as.push_back(a);
    }

    int highestOutcome = 0;
    int highestOutcomeIdx = -1;

    for (int i = 0; i < n; i++)
    {
        int a = as[i];
        int counter = 0;
        for (int j = 0; j < n; j++)
        {
            if (as[j] == a)
            {
                counter++;
            }
        }
        if (counter == 1 && a > highestOutcome)
        {
            highestOutcome = a;
            highestOutcomeIdx = i;
        }
    }

    if (highestOutcomeIdx != -1)
    {
        cout << highestOutcomeIdx + 1 << endl;
    }
    else
    {
        cout << "none" << endl;
    }
}
