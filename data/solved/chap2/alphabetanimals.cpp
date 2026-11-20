#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/alphabetanimals?tab=metadata

int main()
{
    string lastAnimalName = "";

    cin >> lastAnimalName;
    int n;
    cin >> n;

    int nodeId = 0;
    unordered_map<char, vector<string>> adjList;
    vector<string> animals;

    nodeId++;
    char lastAnimalLastName = lastAnimalName[lastAnimalName.size() - 1];

    for (int i = 0; i < n; i++)
    { // O(n)
        string namaBinatang;
        cin >> namaBinatang;

        adjList[namaBinatang[0]].push_back(namaBinatang);
        animals.push_back(namaBinatang);

        nodeId++;
    }

    for (auto namaBinatang : adjList[lastAnimalLastName])
    { // O(n)

        char lastName = namaBinatang[namaBinatang.size() - 1];

        if (lastName == namaBinatang[0] && adjList[lastName].size() == 1)
        {
            cout << namaBinatang + "!" << endl;
            return 0;
        }
        else if (!adjList.count(lastName))
        {

            cout << namaBinatang + "!" << endl;
            return 0;
        }
    }

    if (adjList[lastAnimalLastName].empty())
    {
        cout << "?" << endl;
        return 0;
    }
    cout << adjList[lastAnimalLastName][0] << endl;
}

// Memory Limit Excedeed

// #include <bits/stdc++.h>

// using namespace std;
// int main()
// {
//     string lastAnimalName = "";
//     unordered_map<string, int> nameToNodeId;
//     unordered_map<char, vector<int>> firstCharToNodeId;
//     unordered_map<int, string> nodeIdToNamaAnimal;

//     cin >> lastAnimalName;
//     int n;
//     cin >> n;

//     int nodeId = 0;
//     vector<vector<int>> adjList(n + 1, vector<int>(0));

//     nodeId++;
//     char lastAnimalLastName = lastAnimalName[lastAnimalName.size() - 1];

//     for (int i = 0; i < n; i++)
//     {
//         string namaBinatang;
//         cin >> namaBinatang;
//         nameToNodeId[namaBinatang] = nodeId;
//         firstCharToNodeId[namaBinatang[0]].push_back(nodeId);
//         nodeIdToNamaAnimal[nodeId] = namaBinatang;

//         if (lastAnimalLastName == namaBinatang[0])
//         {
//             adjList[0].push_back(nodeId);
//         }

//         nodeId++;
//     }

//     for (auto [animalName, curNodeId] : nameToNodeId)
//     {

//         char lastName = animalName[animalName.size() - 1];

//         if (firstCharToNodeId.find(lastName) != firstCharToNodeId.end())
//         {
//             vector<int> adjNodeIds = firstCharToNodeId[lastName];
//             for (auto adjNodeId : adjNodeIds)
//             {
//                 if (adjNodeId == curNodeId)
//                 {
//                     continue;
//                 }

//                 adjList[curNodeId].push_back(adjNodeId);
//             }
//         }
//     }

//     // hare->eagle : eagle cannot be used again

//     unordered_set<int> usedAnimal(0);
//     usedAnimal.insert(0);
//     if (adjList[0].size() == 0)
//     {
//         cout << "?" << endl;
//     }
//     else
//     {
//         for (auto adjNodeId : adjList[0])
//         {
//             string curNodeAnimalName = nodeIdToNamaAnimal[adjNodeId];
//             char lastCharNodeName = curNodeAnimalName[curNodeAnimalName.size() - 1];
//             if (adjList[adjNodeId].empty())
//             {
//                 cout << curNodeAnimalName + "!" << endl;
//                 return 0;
//             }
//         }
//         cout << nodeIdToNamaAnimal[adjList[0][0]] << endl;
//     }
// }
