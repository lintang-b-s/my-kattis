#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/addingwords?tab=metadata

int main()
{
    cin.tie(NULL);
    cout.tie(NULL);
    string input;

    unordered_map<string, int> variableToVal;
    unordered_map<int, string> valToVariable;

    while (getline(cin, input))
    {
        if (input == "clear")
        {
            variableToVal.clear();
            valToVariable.clear();
            continue;
        }

        bool definition = false;
        bool valueDef = false;
        istringstream ss(input);

        string variableToDefined = "";

        queue<string> variablesToCalc;

        string word = "";
        while (getline(ss, word, ' '))
        {
            if (word == "def")
            {
                definition = true;
                continue;
            }
            else if (word == "calc")
            {
                definition = false;
                continue;
            }

            if (definition)
            {
                if (valueDef)
                {
                    if (variableToVal.count(variableToDefined))
                    {
                        valToVariable.erase(variableToVal[variableToDefined]);
                    }
                    variableToVal[variableToDefined] = stoi(word);
                    valToVariable[stoi(word)] = variableToDefined;
                    continue;
                }
                variableToDefined = word;
                valueDef = true;
            }
            else
            {
                if (word == "+" || word == "-")
                {
                    variablesToCalc.push(word);
                }
                else if (word == "=")
                {
                    bool plus = true;
                    bool unkown = false;
                    int res = 0;
                    string resVar = "";
                    while (variablesToCalc.size())
                    {
                        string topVar = variablesToCalc.front();
                        variablesToCalc.pop();
                        if (topVar == "+")
                        {
                            plus = true;
                            resVar += " + ";
                        }
                        else if (topVar == "-")
                        {
                            plus = false;
                            resVar += " - ";
                        }
                        else if (plus && (variableToVal.find(topVar) != variableToVal.end()))
                        {
                            res += variableToVal[topVar];
                            resVar += topVar;
                        }
                        else if (!plus && (variableToVal.find(topVar) != variableToVal.end()))
                        {
                            res -= variableToVal[topVar];
                            resVar += topVar;
                        }
                        else
                        {
                            resVar += topVar;
                            unkown = true;
                        }
                    }
                    if (unkown || valToVariable.find(res) == valToVariable.end() )
                    {
                        cout << resVar << " = " << "unknown" << endl;
                    }
                    else
                    {
                        cout << resVar << " = " << valToVariable[res] << endl;
                    }
                }
                else
                {

                    variablesToCalc.push(word);
                }
            }
        }
    }
}