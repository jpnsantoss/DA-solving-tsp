#include "Dataset.h"
#include "iostream"

int main() {
    Dataset* dataset = Dataset::getInstance();

    int count = 0;

    for(auto v : dataset->getGraph2().getVertexSet()) {
        for(auto edge : v->getAdj()) {
            count++;
            cout << "Vertex Id:" << v->getInfo().first;
            auto destination = edge->getDest();
            cout << " | Destination:" << destination->getInfo().first << " | " << edge->getWeight() << endl;
        }
    }

    cout << count;

    return 0;
}