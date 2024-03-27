#include<bits/stdc++.h>
using namespace std;

void inputAllocMatrix(vector<vector<int>> &allocation, int n, int m) {
    cout << "Enter the allocation matrix:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> allocation[i][j];
        }
    }
}

void inputMaxMatrix(vector<vector<int>> &maximum, int n, int m) {
    cout << "Enter the maximum matrix:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> maximum[i][j];
        }
    }
}

bool isSafe(vector<int> &avail, vector<vector<int>> &need, vector<int> &f, int n, int m, int process) {
    for (int j = 0; j < m; ++j) {
        if (need[process][j] > avail[j])
            return false;
    }
    return true;
}

void findSafeSeq(vector<vector<int>> &alloc, vector<vector<int>> &maxMatrix, vector<int> &avail, int n, int m, vector<int> &f, vector<int> &ans, vector<vector<int>> &need, vector<vector<int>> &safeSeqs) {
    if (accumulate(f.begin(), f.end(), 0) == n) {
        safeSeqs.push_back(ans);
        return;
    }

    for (int i = 0; i < n; ++i) {
        if (!f[i] && isSafe(avail, need, f, n, m, i)) {
            for (int j = 0; j < m; ++j) {
                avail[j] += alloc[i][j];
            }
            ans.push_back(i);
            f[i] = 1;
            findSafeSeq(alloc, maxMatrix, avail, n, m, f, ans, need, safeSeqs);
            ans.pop_back();
            f[i] = 0;
            for (int j = 0; j < m; ++j) {
                avail[j] -= alloc[i][j];
            }
        }
    }
}

int main() {
    int n, m;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resources: ";
    cin >> m;

    // Allocation Matrix
    vector<vector<int>> alloc(n, vector<int>(m));
    inputAllocMatrix(alloc, n, m);

    // Max Matrix
    vector<vector<int>> maxMatrix(n, vector<int>(m));
    inputMaxMatrix(maxMatrix, n, m);

    // Available Resources
    vector<int> avail(m);
    cout << "Enter the available resources:\n";
    for (int i = 0; i < m; ++i) {
        cin >> avail[i];
    }

    vector<int> f(n), ans;
    vector<vector<int>> need(n, vector<int>(m)), safeSeqs;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            need[i][j] = maxMatrix[i][j] - alloc[i][j];
    }

    findSafeSeq(alloc, maxMatrix, avail, n, m, f, ans, need, safeSeqs);

    if (safeSeqs.empty()) {
        cout << "No safe sequences found." << endl;
    } else {
        cout << "Safe sequences:\n";
        for (auto &seq : safeSeqs) {
            for (int i = 0; i < n - 1; i++)
                cout << " P" << seq[i] << " ->";
            cout << " P" << seq[n - 1] << endl;
        }
    }
    return 0;
}
