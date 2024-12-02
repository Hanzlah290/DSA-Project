#include<iostream>
#include "Core Classes.h"
#include "DijkstraAlgorithm.h"

using namespace std;


void displayMenu() {
    cout << "========== Traffic Network Management System ==========\n";
    cout << "1. Add an Intersection\n";
    cout << "2. Connect Intersections\n";
    cout << "3. Display the Map\n";
    cout << "4. Find Shortest Path\n";
    cout << "5. Exit\n";
    cout << "=======================================================\n";
    cout << "Enter your choice: ";
}

void menu(Graph& network) {
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                // Add an intersection
                {
                    int id;
                    string name;
                    cout << "Enter Intersection ID: ";
                    cin >> id;
                    cout << "Enter Intersection Name: ";
                    cin.ignore();
                    getline(cin, name);
                    network.addIntersection(id, name);
                }
                break;

            case 2:
                // Connect intersections
                {
                    int id1, id2;
                    double distance;
                    cout << "Enter the first Intersection ID: ";
                    cin >> id1;
                    cout << "Enter the second Intersection ID: ";
                    cin >> id2;
                    cout << "Enter the distance between them: ";
                    cin >> distance;
                    network.addRoad(id1, id2, distance);
                }
                break;

            case 3:
                // Display the network
                network.displayMap();
                break;

            case 4:
                // Find the shortest path
                {
                    int startId, endId;
                    cout << "Enter start Intersection ID: ";
                    cin >> startId;
                    cout << "Enter end Intersection ID: ";
                    cin >> endId;
                    network.findShortestPath(startId, endId);
                }
                break;

            case 5:
                cout << "Exiting the program. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

        cout << endl; // For better readability between menu iterations

    } while (choice != 5);
}

int main() {
    Graph graph; // Create an instance of the Graph class

    // Load data from a file (optional)
    graph.loadFromFile("graph.txt");

    // Call the menu function with the graph instance
    menu(graph);

    // Save updated data to a file before exiting (optional)
    graph.saveToFile("updated_graph.txt");

    return 0;
}

