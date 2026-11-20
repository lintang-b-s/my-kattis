#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, t, m;
    cin >> n >> t >> m;
    int probLastBlood[n][2];     // for each problem store (time,teamId) that win last blood prize
    bool teamACSubmission[t][n]; // for each team store each problem ac submission (1 if AC, 0 if wrong answer)
    memset(teamACSubmission, 0, sizeof(teamACSubmission));
    memset(probLastBlood, -1, sizeof(probLastBlood));

    for (int submission = 0; submission < m; submission++)
    {
        int time, teamID;
        string verdict;
        char problem;
        cin >> time >> teamID >> problem >> verdict;
        if (verdict == "Yes")
        {
            int probIdx = problem - 'A';

            int teamIDx = teamID - 1;
            bool prevTeamProblemSub = teamACSubmission[teamIDx][probIdx];
            if (prevTeamProblemSub != false)
            {
                // cannot send submission again after prev submission is AC
                continue;
            }
            if (probLastBlood[probIdx][0] <= time)
            {
                probLastBlood[probIdx][0] = time;
                probLastBlood[probIdx][1] = teamID;
            }
            teamACSubmission[teamIDx][probIdx] = true;
        }
    }

    for (int prob = 0; prob < n; prob++)
    {
        int lastBloodTime = probLastBlood[prob][0];
        int lastBloodTeamID = probLastBlood[prob][1];
        if (lastBloodTime != -1 and lastBloodTeamID != -1)
        {
            cout << char(prob + 'A') << " " << lastBloodTime << " " << lastBloodTeamID << endl;
        }
        else
        {
            cout << char(prob + 'A') << " " << "-" << " " << "-" << endl;
        }
    }
}