#include <bits/stdc++.h>

using namespace std;

// https://open.kattis.com/problems/dyslectionary?tab=metadata
int generateRandomInt(int min, int max)
{
    return min + (rand() % (max - min + 1));
}

struct wordObject
{
    string name;
    string lastChar;
};

// expected time complexity O(nlogn), worst case(n^2)
vector<wordObject> stableQuickSort(vector<wordObject> words)
{
    if (words.size() <= 1)
    {
        return words;
    }

    int pivot = generateRandomInt(0, words.size() - 1);

    vector<wordObject> smaller;
    vector<wordObject> bigger;
    for (int i = 0; i < words.size(); i++)
    {
        if (i == pivot)
            continue;
        if (words[i].name < words[pivot].name)
        {

            smaller.push_back(words[i]);
        }
        else if (words[i].name > words[pivot].name)
        {

            bigger.push_back(words[i]);
        }
    }

    vector<wordObject> smallerSorted = stableQuickSort(smaller);
    vector<wordObject> biggerSorted = stableQuickSort(bigger);

    vector<wordObject> ans(0);

    for (int i = 0; i < smallerSorted.size(); i++)
    {
        ans.push_back(smallerSorted[i]);
    }
    ans.push_back(words[pivot]);
    for (int i = 0; i < biggerSorted.size(); i++)
    {
        ans.push_back(biggerSorted[i]);
    }

    return ans;
}

int main()
{
    srand(time(0));
    string word;
    vector<wordObject> words;
    bool firstgroup = true;

    auto sortGroup = [&](vector<wordObject> &words)
    {
        if (!firstgroup)
        {
            cout << endl;
        }

        vector<wordObject> ans = stableQuickSort(words);
        int maxsize = 0;
        for (int i = 0; i < ans.size(); i++)
        {

            for (int j = 0; j < ans[i].name.size(); j++)
            {

                int k = ans[i].name.size() - 1 - j;
                if (k <= j)
                {
                    break;
                }
                swap(ans[i].name[k], ans[i].name[j]);
            }

            if (ans[i].name.size() > maxsize)
            {
                maxsize = ans[i].name.size();
            }
        }

        for (int i = 0; i < ans.size(); i++)
        {
            string output(maxsize, ' ');
            string name = ans[i].name;
            int k = maxsize - name.size();
            for (int j = 0; j < name.size(); j++)
            {
                output[k] = name[j];
                k++;
            }
            cout << output << endl;
        }

        firstgroup = false;
        words.clear();
    };

    while (getline(cin, word))
    {
        if (word.empty())
        {

            sortGroup(words);
            continue;
        }

        for (int i = 0; i < word.size(); i++)
        {

            int j = word.size() - 1 - i;
            if (j <= i)
            {
                break;
            }
            swap(word[j], word[i]);
        }
        wordObject wo;
        wo.name = word;
        wo.lastChar = word[0];
        words.push_back(wo);
    }

    if (!words.empty())
    {
        sortGroup(words);
    }
}