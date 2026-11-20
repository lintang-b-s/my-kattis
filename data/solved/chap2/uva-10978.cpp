#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    while (cin>>N){
        if (N == 0) {
            break;
        }

        vector<string> circle(N, "");
        

        int lastPtr = 0;
        for (int i=0; i<N; i++){ 
            string val, card;
            cin >> val >> card;
            int cardLen = card.size();
            int j = lastPtr;
            int counter = 1;
            while (true) {
                if (counter == cardLen && circle[j%N] == "") {
                    circle[j%N] = val;
                    lastPtr = (j+1)%N;
                    break;
                }
                if (circle[j%N] == "") {
                    j = (j+1)%N;
                    counter++;
                }else {
                    j = (j+1)%N;
                }
            }
        }

        for (int i=0; i<N; i++) {
            cout << circle[i];
            if (i < N-1) {
                cout << " ";
            }
        }
        cout << "\n";
   }

    return 0;
}