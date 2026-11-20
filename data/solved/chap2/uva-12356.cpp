#include <bits/stdc++.h>
using namespace std;

int main() {
    int S, B;
    while (cin>>S>>B){
        if (S == 0 && B == 0) {
            break;
        }
        vector<int> left(S+2), right(S+2);
        for (int i=1;i<=S;i++) {
            left[i] = i-1;
            right[i] = i+1;
        }

        for (int i=0; i<B;i++) {
            int L, R;
            cin >> L >> R;

            int leftAlive = left[L];
            int rightAlive = right[R];
            
            if (leftAlive < 1) {
                cout << "* ";
            }else {
                cout << leftAlive << " ";
            }

            if (rightAlive > S) {
                cout << "*\n";
            }else {
                cout << rightAlive << "\n";
            }

            if (leftAlive >=1) {
                right[leftAlive] = rightAlive;
            }
            if (rightAlive <=S) {
                left[rightAlive] = leftAlive;
            }
        } 

        cout << "-\n";
   }

    return 0;
}