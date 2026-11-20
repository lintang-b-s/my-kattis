#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef long long ll;

/*
https://open.kattis.com/problems/galaxyquest2?tab=metadata

solution:
source: https://icpcarchive.github.io/Europe%20Contests/Northwestern%20Europe%20Regional%20Contest%20(NWERC)/2023%20Northwestern%20Europe%20Regional%20Contest/solution.pdf

let:
x_i = time for traverse the segment-i using acceleration/decceleration
d_i = segment-i length
decelerationTime_{i}=accelerationTime_{i}=x_i

total fuel time = \sum_{i} accelerationTime_{i} + deccelerationTime_{i} = 2 * \sum_{i} x_i

for each segment we accelerate, then constant velocity, then deccelerate, so:
constantSpeedTime_{i}= \frac{d_i - x_i^2}{x_i}  = \frac{d_i}{x_i} - x_i

total time take to traverse the segment-i =  accelerationTime_{i}+deccelerationTime_{i}+constantSpeedTime_{i}
                                          = x_i + x_i + (\frac{d_i}{x_i} - x_i)
                                          = \frac{d_i}{x_i} + x_i

the problem ask minimum fuel to take: \min 2 *\sum_{i} x_i , with constraint: time to reach the target < t
this is a constrained optimization problem, can be solved using langrange multiplier: https://tutorial.math.lamar.edu/classes/calciii/lagrangemultipliers.aspx

\min 2 * \sum_{i} x_i, with constraint: \sum_{i} \frac{d_i}{x_i} + x_i <= t

using langrange multiplier:


1. grad(2 * \sum_{i} x_i) = \lambda * grad( \sum_{i} \frac{d_i}{x_i} + x_i ) , grad() = gradient vector

2. \sum_{i} \frac{d_i}{x_i} + x_i  = t

solve this eq (1):
for each i we have:
2 = (1 - \frac{d_i}{x_i^2}) * lambda
with alg. manip., we get:

x_i = \frac{sqrt(d_i) }{ sqrt(1- \frac{2}{\lambda}) }
let c = \frac{1}{sqrt(1- \frac{2}{\lambda})}

x_i = c *sqrt(d_i)   (3)


subtituting eq (3) to eq (2) & doing some alg. manip., we get:
c + \frac{1}{c} = \frac{t}{\sum_{i} sqrt(d_i)} (4)

let q = \frac{t}{\sum_{i} sqrt(d_i)}

using abc formula, we get:
c = \frac{q +- \sqrt(q^2-4)}{2}

bcs we want to find \min 2 *\sum_{i} x_i = 2 * \min  * \sum_{i} c *sqrt(d_i)

we use the min c:
c = cLangrange (in this program) = \frac{q - \sqrt(q^2-4)}{2}

for calc \min \sum_{i} sqrt(d_i) , we can use dijkstra algorithm

if q^2 - 4 < 0, then return impossible (impossible to reach planet terget)
else:  just return the  2 * \min  * \sum_{i} cLangrange *sqrt(d_i)


*/

struct planet
{
    ll x, y, z;
};

const double EPS = 1e-6;

ld abcFormula(ld a, ld b, ld c)
{
    if (b * b + EPS < 4 * a * c)
    {
        return -1; // undefined/impossible
    }
    return (-b - sqrt(b * b - 4 * a * c)) / 2 * a;
}

ld getFuel(ld sumSqrtDist, ll t)
{
    if ((sumSqrtDist - 0) < EPS)
    {
        return -1;
    }
    ld q = t / sumSqrtDist;

    ld cLangrange = abcFormula(1, -q, 1); // sqrt(1- \frac{2}{\lambda}), dimana \lambda adlh langrange multiplier
    if (cLangrange == -1)
    {
        return -1;
    }
    ld fuel = 2 * sumSqrtDist * cLangrange;
    return fuel;
}

int main()
{
    int n, m, q;
    cin >> n >> m >> q;
    vector<planet> galaxy;

    auto eucDist = [](planet a, planet b) -> ld
    {
        ld xx = (a.x - b.x);
        ld yy = (a.y - b.y);
        ld zz = (a.z - b.z);
        ld dist = sqrt(xx * xx + yy * yy + zz * zz);
        return dist;
    };

    for (int i = 0; i < n; i++)
    {
        ll x, y, z;
        cin >> x >> y >> z;
        galaxy.push_back({x, y, z});
    }

    vector<vector<pair<ll, ld>>> adjList(n);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;

        auto planetU = galaxy[u];
        auto planetV = galaxy[v];

        ld dist = sqrt(eucDist(planetU, planetV));
        adjList[u].push_back({v, dist});
        adjList[v].push_back({u, dist});
    }

    auto dijkstra = [&](ll s)
    {
        unordered_map<ll, ld> dist;
        priority_queue<pair<ld, ll>, vector<pair<ld, ll>>, greater<pair<ld, ll>>> pq;

        dist[s] = 0;
        pq.emplace(0, s);

        while (!pq.empty())
        { // O((m+n) log n)
            auto [uDist, u] = pq.top();
            pq.pop();

            if (uDist > dist[u])
            {
                continue;
            }

            for (auto [v, vDist] : adjList[u])
            {
                if (!dist.count(v) || (dist.count(v) && uDist + vDist < dist[v]))
                {
                    dist[v] = uDist + vDist;
                    pq.emplace(dist[v], v);
                }
            }
        }

        return dist;
    };

    int s = 0;

    auto sumSqrtDist = dijkstra(s);

    cout.precision(12);
    for (int i = 0; i < q; i++)
    { // O(q)
        int target, t;
        cin >> target >> t;
        target--;

        auto fuel = getFuel(sumSqrtDist[target], t);

        if (fuel == -1)
        {
            cout << "impossible" << "\n";
        }
        else
        {
            cout << fuel << "\n";
        }
    }
}