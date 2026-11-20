#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin>>N;

    for (int casse=0; casse<N; casse++) {
        vector<set<int>> friendss(3);


        for (int i=0; i<3; i++) {
            int n; 
            cin >>n ;
            while (n--) {
                int val;
                cin >> val;
                friendss[i].insert(val);
            }
        }

        unordered_map<int, int> freq;
        for (int i=0; i<3; i++)  {
            for (auto val: friendss[i]) {
                freq[val]++;
            }
        }       
        
        vector<vector<int>> unique(3);
        for (int i=0; i<3; i++)  {
            for (auto val: friendss[i]) {
                if (freq[val] == 1){
                    unique[i].push_back(val);
                }
            }
            sort(unique[i].begin(), unique[i].end());
        }       

        int best=0;
        for (int i=0;i<3;i++) {
            best = max(best, (int)unique[i].size());
        }

        cout << "Case #" << casse+1 << ":\n";
        for (int i = 0; i < 3; i++) {
            if ((int)unique[i].size() == best) {
                cout << i+1 << " " << unique[i].size();
                for (auto x : unique[i]) cout << " " << x;
                cout << "\n";
            }
        }
    }

    return 0;
}