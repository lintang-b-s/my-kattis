#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin>>N;
    vector<string> students(N);
    for (int stud=0; stud<N; stud++) {
        string studName;
        cin >> studName;
        students[stud] = studName;
    }

    int q;
    cin >> q;
    while (q--) {
        int qPos;
        cin>>qPos;

        qPos--;

        if (students[qPos] != "?") {
            cout << students[qPos] << "\n";
            continue;
        }

        int leftDist = INT_MAX;
        string closestLeft = "";
        for (int i=qPos-1, dist=1; i>=0; i--, dist++) {
            if (students[i] != "?") {
                leftDist = dist;
                closestLeft = students[i];
                break;
            }
        }

        int rightDist = INT_MAX;
        string closestRight = "";
        for (int i=qPos+1, dist=1; i<N; i++, dist++) {
            if (students[i] != "?") {
                rightDist = dist;
                closestRight = students[i];
                break;
            }
        }

        string result = "";
        if (leftDist< rightDist ) {
            for (int i=0; i<leftDist; i++) {
                result += "right of ";
            }
            cout << result +  closestLeft << "\n";
        }else if( rightDist<leftDist ) {
            for (int i=0; i<rightDist; i++) {
                result += "left of ";
            }
            cout << result+ closestRight << "\n";
        }else if (leftDist == rightDist) {
            cout << "middle of " << closestLeft << " and " << closestRight << "\n";
        }
    }

  
    
    


    return 0;
}