#include<iostream>
#include "Core Classes.h"
using namespace std;
int main() {
    Graph graph;

    // Load data from file
    graph.loadFromFile("graph.txt");

    // Add a new intersection and road
    graph.addIntersection(4, "D");
    graph.addRoad(3, 4, 8.0, 0.2);

    // Save the updated graph
    graph.saveToFile("updated_graph.txt");

    return 0;
}
