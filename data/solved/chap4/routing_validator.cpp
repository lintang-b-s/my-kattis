#include <bits/stdc++.h>
using namespace std;

string exec(const string &cmd) {
    array<char, 128> buf;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) return "";
    while (fgets(buf.data(), buf.size(), pipe.get()))
        result += buf.data();
    while (!result.empty() && result.back() == '\n')
        result.pop_back();
    return result;
}

vector<pair<string, string>> listTestCases(const string &dir) {
    vector<pair<string, string>> cases;
    for (const auto &entry : filesystem::directory_iterator(dir)) {
        string path = entry.path().string();
        if (path.size() >= 3 && path.substr(path.size() - 3) == ".in") {
            string base = path.substr(0, path.size() - 3);
            string ansFile = base + ".ans";
            if (filesystem::exists(ansFile))
                cases.push_back({path, ansFile});
        }
    }
    sort(cases.begin(), cases.end());
    return cases;
}

int main() {
    int compileStatus = system("g++ -O2 -o routing_bin routing.cpp");
    if (compileStatus != 0) {
        cerr << "Compilation failed." << endl;
        return 1;
    }

    int total = 0, passed = 0;
    vector<string> dirs = {"data/routing/sample", "data/routing/secret"};

    for (const string &dir : dirs) {
        if (!filesystem::exists(dir)) continue;
        auto cases = listTestCases(dir);
        for (auto &[inFile, ansFile] : cases) {
            total++;
            string output = exec("./routing_bin < " + inFile);
            ifstream ifs(ansFile);
            string expected((istreambuf_iterator<char>(ifs)), {});
            while (!expected.empty() && expected.back() == '\n')
                expected.pop_back();
            if (output == expected) {
                passed++;
                cout << "PASS " << inFile << endl;
            } else {
                cout << "FAIL " << inFile << endl;
                cout << "  Expected: " << expected << endl;
                cout << "  Got:      " << output << endl;
            }
        }
    }

    cout << "\n" << passed << "/" << total << " passed" << endl;
    filesystem::remove("routing_bin");
    return (passed == total) ? 0 : 1;
}
