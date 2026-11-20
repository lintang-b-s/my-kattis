#include <bits/stdc++.h>
using namespace std;

typedef long long ull;

// https://open.kattis.com/problems/subway2?tab=metadata
int main()
{
    ull sx, sy, tx, ty;
    cin >> sx >> sy >> tx >> ty;
    cin.ignore();

    int sid = 0;
    int tid = 1;
    vector<pair<ull, ull>> allCoords;
    allCoords.push_back(make_pair(sx, sy));
    allCoords.push_back(make_pair(tx, ty));
    unordered_map<int, unordered_set<int>> subwayLineEdges;

    int vid = 2;
    string line;
    while (getline(cin, line))
    {
        istringstream ss(line);

        // vector<pair<int, int>> subwayLines;
        vector<string> subway;
        string coord;
        while (getline(ss, coord, ' '))
        {
            subway.push_back(coord);
        }

        for (int i = 0; i < subway.size(); i += 2)
        {
            if (stoi(subway[i]) == -1 && stoi(subway[i + 1]) == -1)
            {
                break;
            }
            if (i < subway.size() - 4)
            {
                subwayLineEdges[vid].insert(vid + 1);
            }
            if (i > 0)
            {
                subwayLineEdges[vid].insert(vid - 1);
            }

            allCoords.push_back(make_pair(stoi(subway[i]), stoi(subway[i + 1])));
            vid += 1;
        }
    }

    int n = allCoords.size();

    vector<vector<pair<int, double>>> adjList(n);

    for (int i = 0; i < n; i++)
    { // O(n^2)
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                continue;
            }
            double speed = (double)10.0 * ((double)1000.0 / (double)60.0);

            if (subwayLineEdges.count(i) && subwayLineEdges.count(j) && subwayLineEdges[i].count(j))
            {
                speed = (double)40.0 * ((double)1000.0 / (double)60.0);
            }

            auto [ux, uy] = allCoords[i];
            auto [vx, vy] = allCoords[j];
            double distx = (double)(vx - ux);
            double disty = (double)(vy - uy);
            double didist = distx * distx + disty * disty;
            double time = sqrt(didist) / speed;
            adjList[i].push_back(make_pair(j, time));
        }
    }

    unordered_map<int, double> time;
    time[sid] = 0;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.emplace(0, sid);

    while (!pq.empty())
    { // O((m+n) log n), m=jumlah edges = n(n-1)/2 karena complete graph
      //
        auto [udist, u] = pq.top();
        pq.pop();

        if (udist > time[u])
        {
            continue;
        }

        for (auto [v, vw] : adjList[u])
        {
            if (!time.count(v) || (time.count(v) && time[u] + vw < time[v]))
            {
                time[v] = time[u] + vw;
                pq.emplace(time[v], v);
            }
        }
    }
    cout << (ull)round(time[tid]) << "\n";
}