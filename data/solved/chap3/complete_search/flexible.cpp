#include <bits/stdc++.h>
using namespace std;

int main()
{
    int maxwidth, p;
    cin >> maxwidth >> p;
    vector<int> partition;
    partition.push_back(0);
    for (int i = 0; i < p; i++)
    {
        int a;
        cin >> a;
        partition.push_back(a);
    }
    partition.push_back(maxwidth);

    int count = 0;

    set<int> rooms;
    for (int width = 1; width <= maxwidth; width++)
    { // O(maxwidth * p^2)
        for (int j = 0; j < partition.size(); j++)
        {
            for (int k = j + 1; k < partition.size(); k++)
            {
                if (partition[k] - partition[j] == width)
                {
                    rooms.insert(width);
                }
            }
        }
    }

    int i = 0;
    for (auto room : rooms)
    {
        cout << room;

        if (i < rooms.size() - 1)
        {
            cout << " ";
        }
        i++;
    }
}