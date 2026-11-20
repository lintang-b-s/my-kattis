#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/traveltheskies?tab=metadata

int main()
{
    int k, n, m;
    cin >> k >> n >> m;

    int adj[n][k][k];
    for (int i = 0; i < n; i++)
    { // O(n*k^2)
        for (int j = 0; j < k; j++)
        {
            for (int q = 0; q < k; q++)
            {
                adj[i][j][q] = 0;
            }
        }
    }

    int arrival[n][k];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            arrival[i][j] = 0;
        }
    }

    for (int i = 0; i < m; i++)
    {
        int from, dest, day, capacity;
        cin >> from >> dest >> day >> capacity;
        adj[day - 1][from - 1][dest - 1] = capacity;
    }

    for (int i = 0; i < k * n; i++)
    {
        int airport, day, numPeople;
        cin >> airport >> day >> numPeople;
        arrival[day - 1][airport - 1] = numPeople;
    }

    bool optimal = true;

    for (int day = 0; day < n; day++)
    { // O(n*k^2)
        for (int from = 0; from < k; from++)
        {
            for (int destination = 0; destination < k; destination++)
            {
                if (from == destination)
                {
                    continue;
                }
                int flightCapacity = adj[day][from][destination];
                int peopleAtAirportThisDay = arrival[day][from];

                if (peopleAtAirportThisDay < flightCapacity)
                {
                    optimal = false;
                    break;
                }

                arrival[day][from] -= flightCapacity;

                if (day + 1 < n)
                {
                    arrival[day + 1][destination] += flightCapacity;
                }
            }

            int peopleAtAirportThisDayAfterFlights = arrival[day][from];
            // gak ada penerbangan di hari=day
            // tambahin ppl at this airport=from di hari berikutnya
            // atau seetelah semua penerbangan in this airport, di airport masih ada peoples
            arrival[day + 1][from] += peopleAtAirportThisDayAfterFlights;
        }
    }

    if (optimal)
    {
        cout << "optimal" << endl;
    }
    else
    {
        cout << "suboptimal" << endl;
    }
}