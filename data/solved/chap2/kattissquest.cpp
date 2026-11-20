#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long int ll;
int main()
{
    int N;
    cin >> N;
    map<int, priority_queue<int>> quests;
    for (int i = 0; i < N; i++)
    {
        string cmdType;
        int E, G;
        int X;
        cin >> cmdType;
        if (cmdType == "add")
        {
            cin >> E >> G;

            quests[E].push(G); // O(logM), M=jumlah quests dengan energy berbeda
        }
        else
        {
            cin >> X;

            ll gold = 0;

            while (true)
            {
                if (quests.size() == 0)
                {
                    break;
                }
                auto biggestEnQuest = quests.lower_bound(X); // O(logM)

                if (biggestEnQuest == quests.end())
                {
                    --biggestEnQuest;
                }
                while (biggestEnQuest != quests.begin() && (*biggestEnQuest).first > X)
                {
                    --biggestEnQuest;
                }

                int currE = (*biggestEnQuest).first;
                auto &currGold = (*biggestEnQuest).second;
                if (currE > X)
                {
                    break;
                }
                X -= currE;
                gold += currGold.top();
                currGold.pop(); // O(logQ), Q= #quests dengan energy currE
                if (currGold.empty())
                {
                    quests.erase(biggestEnQuest); // O(logM)
                }
            }
            cout << gold << endl;
        }
    }

    // WA, karena quests dengan energy sama bisa ada lebih dari 1
    // cin >> N;
    // map<int, int> quests;
    // for (int i = 0; i < N; i++)
    // { // O(NlogN)
    //     string cmdType;
    //     int E, G;
    //     int X;
    //     cin >> cmdType;
    //     if (cmdType == "add")
    //     {
    //         cin >> E >> G;
    //         quests[E] = G; // O(logN)
    //     }
    //     else
    //     {
    //         cin >> X;

    //         int gold = 0;

    //         while (true)
    //         {
    //             if (quests.size() == 0)
    //             {
    //                 break;
    //             }
    //             auto biggestEnQuest = quests.lower_bound(X);

    //             while ((biggestEnQuest != quests.begin() && (*biggestEnQuest).first > X) || biggestEnQuest == quests.end())
    //             {
    //                 --biggestEnQuest;
    //             }

    //             int currE = (*biggestEnQuest).first;
    //             int currGold = (*biggestEnQuest).second;
    //             if (currE > X)
    //             {
    //                 break;
    //             }
    //             X -= currE;
    //             gold += currGold;
    //             quests.erase(biggestEnQuest);
    //         }
    //         cout << gold << endl;
    //     }
    // }
}