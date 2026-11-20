#include <bits/stdc++.h>

using namespace std;

int main()
{
    cin.tie(NULL);
    cout.tie(NULL);

    map<int, pair<string, string>> perintahPerintah;

    int variables[26] = {0};

    vector<int> lines(0);
    string cmd;
    while (getline(cin, cmd))
    {

        istringstream ss(cmd);

        string word;

        int line = 0;
        string cmdType = "";
        ss >> line;
        lines.push_back(line);

        string isiCmd = "";
        int i = 0;
        string varName = "";
        ss >> cmdType;

        getline(ss, isiCmd);
        if (!isiCmd.empty() && isiCmd[0] == ' ')
        {
            isiCmd.erase(isiCmd.begin());
        }

        perintahPerintah[line] = {cmdType, isiCmd};
    }

    sort(lines.begin(), lines.end());

    unordered_map<int, int> lineToIdx;
    for (int i = 0; i < lines.size(); i++)
    {

        lineToIdx[lines[i]] = i;
    }

    int idx = 0;

    int currentLabel = lines[idx];

    while (true)
    {
        currentLabel = lines[idx];

        auto cmdL = perintahPerintah[currentLabel];
        if (cmdL.first == "LET")
        {
            string isiCmd = cmdL.second;
            int varValue = 0;

            istringstream ss(isiCmd);

            string namaVariabel = "";

            int i = 0;
            string eq = "", x = "", operation = "", y = "";
            ss >> namaVariabel >> eq >> x;

            if (isalpha(x[0]))
            {
                varValue = variables[x[0] - 'A'];
            }
            else
            {
                varValue = stoi(x);
            }

            if (ss >> operation >> y)
            {

                if (isalpha(y[0]))
                {
                    if (operation == "+")
                    {
                        varValue += variables[y[0] - 'A'];
                    }
                    else if (operation == "-")
                    {
                        varValue -= variables[y[0] - 'A'];
                    }
                    else if (operation == "*")
                    {
                        varValue *= variables[y[0] - 'A'];
                    }
                    else if (operation == "/")
                    {
                        varValue /= variables[y[0] - 'A'];
                    }
                }
                else
                {
                    if (operation == "+")
                    {
                        varValue += stoi(y);
                    }
                    else if (operation == "-")
                    {
                        varValue -= stoi(y);
                    }
                    else if (operation == "*")
                    {
                        varValue *= stoi(y);
                    }
                    else if (operation == "/")
                    {
                        varValue /= stoi(y);
                    }
                }
            }

            variables[namaVariabel[0] - 'A'] = varValue;
        }
        else if (cmdL.first == "PRINT")
        {
            if (cmdL.second[0] == '"')
            {
                cout << cmdL.second.substr(1, cmdL.second.size() - 2);
            }
            else
            {
                cout << variables[cmdL.second[0] - 'A'];
            }
        }
        else if (cmdL.first == "PRINTLN")
        {
            if (cmdL.second[0] == '"')
            {
                cout << cmdL.second.substr(1, cmdL.second.size() - 2) << endl;
            }
            else
            {
                cout << variables[cmdL.second[0] - 'A'] << endl;
            }
        }
        else if (cmdL.first == "IF")
        {
            string isiCmd = cmdL.second;
            int varValue = 0;

            istringstream ss(isiCmd);

            bool gotoo = false;
            bool conditionTrue = false;

            string var = "", op = "", rhs = "", then = "", gotooS = "", gotoLine = "";
            ss >> var >> op >> rhs >> then >> gotooS >> gotoLine;

            if (isalpha(var[0]))
            {
                varValue = variables[var[0] - 'A'];
            }
            else
            {
                varValue = stoi(var);
            }

            int rightVal = 0;

            if (isalpha(rhs[0]))
            {
                rightVal = variables[rhs[0] - 'A'];
            }
            else
            {
                rightVal = stoi(rhs);
            }

            if (op == "=")
            {
                conditionTrue = varValue == rightVal;
            }
            else if (op == ">")
            {
                conditionTrue = varValue > rightVal;
            }
            else if (op == "<")
            {
                conditionTrue = varValue < rightVal;
            }
            else if (op == "<>")
            {
                conditionTrue = varValue != rightVal;
            }
            else if (op == "<=")
            {
                conditionTrue = varValue <= rightVal;
            }
            else if (op == ">=")
            {
                conditionTrue = varValue >= rightVal;
            }

            if (conditionTrue)
            {
                currentLabel = stoi(gotoLine);
                idx = lineToIdx[currentLabel];
                continue;
            }
        }
        if (idx == lines.size() - 1)
        {
            break;
        }
        idx++;
    }
}