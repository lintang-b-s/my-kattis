#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    while (getline(cin, s))
    {
        istringstream ss(s);
        string is = "";
        vector<int> as;
        int maxi = 0;
        while (getline(ss, is, ' '))
        {
            int i = stoi(is);
            as.push_back(i);
            maxi = max(maxi, i);
        }

        int n = as.size();

        bool distSet[maxi + 1];
        memset(distSet, false, sizeof distSet);
        distSet[0] = true;

        sort(as.begin(), as.end());

        bool notARuler = false;
        // O(n^2)
        for (int i = 0; i < n; i++)
        {
            int a = as[i];
            for (int j = i + 1; j < n; j++)
            {
                int b = as[j];
                int dist = abs(b - a);

                if (distSet[dist])
                {
                    cout << "not a ruler" << endl;
                    i = n;
                    notARuler = true;
                    break;
                }

                distSet[dist] = true;
            }
        }

        if (notARuler)
        {
            continue;
        }

        vector<int> missingDist;

        for (int dist = 1; dist <= maxi; dist++)
        {
            if (distSet[dist] == 0)
            {
                missingDist.push_back(dist);
            }
        }

        if (missingDist.size() == 0)
        {
            cout << "perfect";
        }
        else
        {
            cout << "missing";
            for (int i = 0; i < missingDist.size(); i++)
            {
                int dist = missingDist[i];
                cout << " " << dist;
            }
        }
        cout << endl;
    }
}