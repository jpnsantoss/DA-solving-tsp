#include "utils/Dataset.h"
#include "iostream"

int main() {
    Dataset* dataset = Dataset::getInstance();

    dataset->loadRealWorldGraph("data/Real_World_Graphs/graph3/nodes.csv", "data/Real_World_Graphs/graph3/edges.csv");

    cout << "done";

    return 0;
}