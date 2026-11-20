#include <bits/stdc++.h>

using namespace std;
// https://open.kattis.com/problems/alehouse?tab=metadata

int main()
{

    cin.tie(NULL);
    cout.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> peopleTimeIntervals;
    for (int i = 0; i < n; i++)
    {
        int arrival;
        int departure;
        cin >> arrival >> departure;
        peopleTimeIntervals.push_back(make_pair(max(arrival - k, 0), departure));
    }

    sort(peopleTimeIntervals.begin(), peopleTimeIntervals.end()); //wc: O(nlogn), n=jumlah people

    priority_queue<int, vector<int>, greater<int>> temansPq;
    int maxFriend = -1;
    for (int i = 0; i < peopleTimeIntervals.size(); i++) //wc: O(nlogn)
    {
        auto [arrival, departure] = peopleTimeIntervals[i];
        while (!temansPq.empty() && temansPq.top() < arrival)
        {
            temansPq.pop();
        }

        temansPq.push(departure);
        maxFriend = max((int)temansPq.size(), maxFriend);
    }
    cout << maxFriend << endl;
}