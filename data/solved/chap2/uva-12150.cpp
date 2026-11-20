#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    while (cin>>n){ 

        vector<int> res(n,-1);

        if (n == 0) break;

        // current = prev - P
        // prev = current + P
        bool ok = true;
        for (int i=0; i < n; i++ ) {
            int C;
            int P;
            cin >> C >> P;
            int prev = i + P;
            if (prev < 0 || prev >= n) {
                ok = false;
            } else if (res[prev] != -1) {
                ok = false;
            }else {
                res[prev] = C;
            }
        }

        if (!ok) {
            cout << "-1\n";
        }else {
            for (int i =0; i < n; i++){ 
                cout << res[i];
                if (i < n-1) {
                    cout << " ";
                }
            }
            cout << "\n";
        }
   }

    return 0;
}