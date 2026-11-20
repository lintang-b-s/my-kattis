#include <bits/stdc++.h>

using namespace std;

// https://open.kattis.com/problems/musicyourway?tab=metadata

int main()
{
    unordered_map<string, int> attributes;
    vector<string> attrArr;
    vector<vector<string>> songs;
    string cols;

    while (true)
    {
        if (!getline(cin, cols))
        {
            break;
        }

        if (cols.size() == 0)
        {
            continue;
        }

        attributes.clear();
        attrArr.clear();
        songs.clear();

        int attrCount = 0;
        istringstream ss(cols);
        string attr;
        while (getline(ss, attr, ' '))
        {
            attributes[attr] = attrCount;
            attrCount++;
            attrArr.push_back(attr);
        }

        int m;
        cin >> m;
        for (int i = 0; i < m; i++)
        {
            vector<string> song;
            for (int j = 0; j < attributes.size(); j++)
            {
                string val;
                cin >> val;
                song.push_back(val);
            }
            songs.push_back(song);
        }

        int n;
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            string attrQuery;
            cin >> attrQuery;

            int attrId = attributes[attrQuery];
            stable_sort(songs.begin(), songs.end(), [attrId](vector<string> a, vector<string> b)
                        { return a[attrId] < b[attrId]; });

            for (int j = 0; j < attrArr.size(); j++)
            {
                cout << attrArr[j];
                if (j < attrCount - 1)
                {
                    cout << " ";
                }
            }

            cout << endl;
            for (int j = 0; j < m; j++)
            {
                for (int k = 0; k < songs[j].size(); k++)
                {
                    cout << songs[j][k];
                    if (k < songs[j].size() - 1)
                    {
                        cout << " ";
                    }
                }
                cout << endl;
            }
            cout << endl;
        }
    }

    return 0;
}
