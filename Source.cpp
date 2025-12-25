#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <iomanip>
#include "Header.h"

using namespace std;

bool GraphColoring::canColor(int v, int c) {
    for (int u = 0; u < n; ++u) {
        if (adjMatrix[v][u] && coloring[u] == c) {
            return false;
        }
    }
    return true;
}

bool GraphColoring::solveBacktrack(int v, int k) {
    if (v == n) return true;
    for (int c = 0; c < k; ++c) {
        if (canColor(v, c)) {
            coloring[v] = c;
            if (solveBacktrack(v + 1, k)) return true;
            coloring[v] = -1;
        }
    }
    return false;
}

bool GraphColoring::readFromFile(const string& filename) {
    ifstream in(filename);
    if (!in.is_open()) {
        cout << "Error: can not open" << filename << endl;
        return false;
    }

    in >> n;
    adjMatrix.assign(n, vector<int>(n, 0));
    coloring.assign(n, -1);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            in >> adjMatrix[i][j];
        }
    }
    in.close();
    return true;
}

int GraphColoring::greedyColoring(vector<int>& resultColoring) {
    vector<int> degrees(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            degrees[i] += adjMatrix[i][j];
        }
    }

    vector<int> vertices(n);
    for (int i = 0; i < n; ++i) vertices[i] = i;
    sort(vertices.begin(), vertices.end(), [&](int a, int b) {
        return degrees[a] > degrees[b];
        });

    vector<int> color(n, -1);
    int maxColor = 0;

    for (int v : vertices) {
        vector<bool> used(n, false);
        for (int u = 0; u < n; ++u) {
            if (adjMatrix[v][u] && color[u] != -1) {
                used[color[u]] = true;
            }
        }
        int c;
        for (c = 0; c < n; ++c) {
            if (!used[c]) break;
        }
        color[v] = c;
        maxColor = max(maxColor, c + 1);
    }

    resultColoring = color;
    return maxColor;
}

int GraphColoring::bruteForceColoring(vector<int>& resultColoring) {
    for (int k = 1; k <= n; ++k) {
        fill(coloring.begin(), coloring.end(), -1);
        if (solveBacktrack(0, k)) {
            resultColoring = coloring;
            return k;
        }
    }
    return -1;
}

void GraphColoring::writeGraphviz(const string& filename, const vector<int>& colors) {
    ofstream out(filename);
    out << "graph G {\n";
    out << "  layout=dot;\n";
    out << "  node [shape=circle, style=filled];\n";

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (adjMatrix[i][j]) {
                out << "  " << i << " -- " << j << ";\n";
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        string colorStr;
        switch (colors[i]) {
        case 0: colorStr = "red"; break;
        case 1: colorStr = "blue"; break;
        case 2: colorStr = "green"; break;
        case 3: colorStr = "yellow"; break;
        case 4: colorStr = "orange"; break;
        case 5: colorStr = "purple"; break;
        default: colorStr = "gray";
        }
        out << "  " << i << " [fillcolor=\"" << colorStr
            << "\", label=\"" << i << "\\n(color " << colors[i] << ")\"];\n";
    }
    out << "}\n";
    out.close();
}

void GraphColoring::writeResults(const string& filename) {
    ofstream out(filename);
    if (!out.is_open()) {
        cout << "Import error in " << filename << endl;
        return;
    }

    out << "GRAPH COLORING RESULTS\n";
    out << "======================\n\n";

    vector<int> greedyColors;
    int greedyNum = greedyColoring(greedyColors);
    out << "GREEDY ALGORYTHM:\n";
    out << "Chromatic number: " << greedyNum << "\n";
    out << "Coloring: ";
    for (int c : greedyColors) out << c << " ";
    out << "\nGraph: greedy.dot\n\n";
    writeGraphviz("greedy.dot", greedyColors);

    vector<int> exactColors;
    int exactNum = bruteForceColoring(exactColors);
    out << "BRUTFORCE ALGORYTHM:\n";
    out << "Chromatic number: " << exactNum << "\n";
    out << "Coloring: ";
    for (int c : exactColors) out << c << " ";
    out << "\nGraph: exact.dot\n\n";
    writeGraphviz("exact.dot", exactColors);

    out << "Adjacency matrix (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            out << setw(2) << adjMatrix[i][j] << " ";
        }
        out << "\n";
    }
    out.close();
}
