#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

enum
{
    UNVISITED = -1
};
typedef long long ll;

void Kosaraju(int u, int pass, vi &dfs_num, vector<vii> AL, vector<vii> AL_T,
              vi &S, vi &scc)
{ // O(V+E)
    dfs_num[u] = 1;
    auto &neighbor = (pass == 1) ? AL[u] : AL_T[u];
    for (auto &[v, w] : neighbor)
    {
        if (dfs_num[v] == UNVISITED)
        {
            Kosaraju(v, pass, dfs_num, AL, AL_T, S, scc);
        }
    }
    S.push_back(u);
    scc.push_back(u);
}

int main()
{
    int N;
    cin >> N;
    cin.ignore();
    vector<pair<string, pair<string, unordered_set<string>>>> starwars;
    for (int i = 0; i < N; i++)
    {
        string karakter, bahasaSpeak;
        unordered_set<string> bahasaUnderstand;
        string line;
        getline(cin, line);
        istringstream ss(line);

        string word;
        int j = 0;
        while (getline(ss, word, ' '))
        {
            if (j == 0)
            {
                karakter = word;
            }
            else if (j == 1)
            {
                bahasaSpeak = word;
            }
            else
            {
                bahasaUnderstand.insert(word);
            }
            j++;
        }

        starwars.push_back(make_pair(karakter, make_pair(bahasaSpeak, bahasaUnderstand)));
    }

    int dfsNumberCounter, numSCC;
    vector<vii> AL(N), AL_T(N);
    vi S, visited;
    stack<int> St;

    auto bitpack = [](int i, int j)
    {
        return i | (j << 16);
    };

    unordered_set<ll> edgesSet;

    for (int i = 0; i < starwars.size(); i++)
    {
        auto [karakterI, bahasaI] = starwars[i];
        for (int j = 0; j < starwars.size(); j++)
        {
            if (i == j)
            {
                continue;
            }
            auto [karakterJ, bahasaJ] = starwars[j];

            if (edgesSet.count(bitpack(i, j)))
            {
                continue;
            }

            if (bahasaI.first == bahasaJ.first)
            {
                AL[i].push_back({j, 1});
                AL[j].push_back({i, 1});

                edgesSet.insert(bitpack(i, j));
                edgesSet.insert(bitpack(j, i));

                AL_T[j].push_back({i, 1});
                AL_T[i].push_back({j, 1});
            }
            else if (bahasaJ.second.count(bahasaI.first))
            {
                edgesSet.insert(bitpack(i, j));

                AL[i].push_back({j, 1});
                AL_T[j].push_back({i, 1});
            }
        }
    }

    vi dfs_num(N, UNVISITED);
    for (int u = 0; u < N; u++)
    { // O(V+E) 
        if (dfs_num[u] == UNVISITED)
        {
            vi scc;
            Kosaraju(u, 1, dfs_num, AL, AL_T, S, scc);
        }
    }

    numSCC = 0;
    dfs_num.assign(N, UNVISITED);

    vector<vi> sccs;
    for (int i = N - 1; i >= 0; i--)
    {  // O(V+E) 
        if (dfs_num[S[i]] == UNVISITED)
        {
            vi scc;
            ++numSCC, Kosaraju(S[i], 2, dfs_num, AL, AL_T, S, scc);
            sccs.push_back(scc);
        }
    }

    int maxSizeSCC = 0;

    for (int i = 0; i < sccs.size(); i++)
    {
        maxSizeSCC = max(maxSizeSCC, (int)sccs[i].size());
    }

    cout << N - maxSizeSCC << "\n";
}
