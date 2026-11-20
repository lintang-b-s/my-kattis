#include <bits/stdc++.h>
using namespace std;
// https://open.kattis.com/problems/rationalsequence2?tab=metadata

int main()
{
    int P;
    cin >> P;
    for (int i = 0; i < P; i++)
    {
        int K, p, q;
        cin >> K;
        string pq;

        int j = 0;
        cin >> pq;
        
        istringstream ss(pq);

        while (getline(ss, pq, '/'))
        {

            if (j == 0)
            {
                p = stoi(pq);
                j++;
            }
            else
            {
                q = stoi(pq);
            }
        }

        vector<int> path(0); // left = 0, right = 1
        while (p != 1 || q != 1)
        {
            if (p < q)
            {
                q = q - p;
                path.push_back(0);
            }
            else
            {
                p = p - q;
                path.push_back(1);
            }
        }
        reverse(path.begin(), path.end());

        int n = 1;
        for (int l = 0; l < path.size(); l++)
        {

            int lr = path[l];
            if (lr == 0)
            {
                n *= 2;
            }
            else
            {
                n = n * 2 + 1;
            }
        }

        cout << K << " " << n << endl;
    }
}