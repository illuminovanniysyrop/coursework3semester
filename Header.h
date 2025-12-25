#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <iomanip>

using namespace std;

class GraphColoring {
private:
    int n;
    vector<vector<int>> adjMatrix;
    vector<int> coloring;

    bool canColor(int v, int c);

    bool solveBacktrack(int v, int k);

public:
    GraphColoring() : n(0) {}

    bool readFromFile(const string& filename);

    int greedyColoring(vector<int>& resultColoring);

    int bruteForceColoring(vector<int>& resultColoring);

    void writeGraphviz(const string& filename, const vector<int>& colors);

    int getSize() const { return n; }

    void writeResults(const string& filename);
};
