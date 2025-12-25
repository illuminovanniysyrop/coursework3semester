#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <iomanip>
#include "Header.h"

using namespace std;

int main() {
    GraphColoring solver;

    if (!solver.readFromFile("input.txt")) {
        return 1;
    }

    cout << "Graph size: " << solver.getSize() << endl;
    solver.writeResults("output.txt");

    cout << "\nCreated files:\n";
    cout << "- output.txt - results\n";
    cout << "- greedy.dot - greedy coloring\n";
    cout << "- exact.dot - brutforce coloring\n";
    cout << "\nPNG convertion:\n";
    cout << "dot -Tpng greedy.dot -o greedy.png\n";
    cout << "dot -Tpng exact.dot -o exact.png\n";

    return 0;
}
