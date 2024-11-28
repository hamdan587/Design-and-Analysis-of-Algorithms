/*
Sarah, an aspiring computer scientist, is working on a project involving network analysis. She's tasked with
identifying the shortest cycle in a communication network to optimize data transfer. She needs to write a
function that can find the length of the shortest cycle in the network represented by a given set of
connections.
She needs to create an algorithm that takes in the number of vertices and the connections between them.
Each vertex is assigned a unique label ranging from 0 to n - 1. The connections between vertices are
represented by a 2D integer array where each array, edges[i] = [ui, vi], denotes a link between vertex ui and
vertex vi. It's essential to note that there's at most one connection between any pair of vertices, and no vertex
has a direct connection to itself.
Sarah has to return the length of the shortest cycle in the network. A cycle, in this context, is a path that
starts and ends at the same node, utilizing each connection exactly once.
For example:

- If the network has 7 vertices with connections [[0,1],[1,2],[2,0],[3,4],[4,5],[5,6],[6,3]], Sarah's function
should output 3. The shortest cycle in this network is: 0 -> 1 -> 2 -> 0.

- If the network has 4 vertices with connections [[0,1],[0,2]], the function should return -1 since there are
no cycles in this particular network.
Constraints:
- The number of vertices ranges from 2 to 1000.
- The number of connections ranges from 1 to 1000.
- Each edge in the input represents a valid connection between vertices.
- Vertex labels and connections are distinct and non-repeating.
Sarah needs to consider the optimal approach to efficiently solve this problem and ensure the algorithm
works within these constraints. How can she design the function to tackle this challenge?

Test Cases Format
1. First line has the number of vertices
2. Then there are all the connection
3. Then there is an expected output
4. And the resulting cycle (if any)
You are required to provide a C++ implementation of an algorithm that adheres to the aforementioned
conditions. Additionally, analyze the time complexity of your algorithm. The efficiency of the algorithm
will be compared with the best-known solution. Ensure your logic uses no more than a constant amount of
extra space. It is advisable to generate all possible combinations before attempting implementation.

*/


//B

#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <map>
#include<climits>
using namespace std;

struct InputData {
    int n;
    vector<vector<int>> edges;
    int expectedOutput;
    string resultingCycle; //as we dont need to return the cycle, we can just print it
};

InputData readInputData(const string& fileName) {
    ifstream file(fileName);
    InputData inputData;
    string line;

    // Read the number of vertices
    getline(file, line);
    inputData.n = stoi(line);

    // Read the edges separated by spaces
    while (getline(file, line) && !line.empty()) {
        stringstream ss(line);
        string edge, item;
        vector<int> edgePair;
        while (getline(ss, item, ' ')) {
            edgePair.push_back(stoi(item));
        }
        inputData.edges.push_back(edgePair);
    }


    // Read the expected output
    getline(file, line);
    inputData.expectedOutput = stoi(line);

    // Read the resulting cycle
    getline(file, line);
    inputData.resultingCycle = line;

    return inputData;
}

void coutInputData(InputData& inputData) {
    cout << inputData.n << endl;

    for (int i = 0; i < inputData.edges.size(); i++) {
        for (int j = 0; j < inputData.edges[i].size(); j++) {
            cout << inputData.edges[i][j] << " ";
        }

        cout << endl;
    }

    cout << inputData.expectedOutput << endl;
    cout << inputData.resultingCycle << endl;
}

//use dynamic programming to find the shortest cycle and flyod warshall to find the shortest path

int shortestCycle(InputData& inputData) {
    int n = inputData.n;
    vector<vector<int>> edges = inputData.edges;
    int expectedOutput = inputData.expectedOutput;
    string resultingCycle = inputData.resultingCycle;

    //create a matrix to store the shortest path between each pair of vertices
    vector<vector<int>> shortestPath(n, vector<int>(n, INT_MAX));

    //initialize the matrix
    for (int i = 0; i < edges.size(); i++) {
        shortestPath[edges[i][0]][edges[i][1]] = 1;
    }

    //flyod warshall algorithm
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < edges.size(); i++) {
            for (int j = 0; j < edges.size(); j++) {
                if (shortestPath[i][k] != INT_MAX && shortestPath[k][j] != INT_MAX) {
                    shortestPath[i][j] = min(shortestPath[i][j], shortestPath[i][k] + shortestPath[k][j]);
                }
            }
        }
    }

    //find the shortest cycle
    int shortestCycle = INT_MAX;
    for (int i = 0; i < edges.size(); i++) {
        if (shortestPath[i][i] != INT_MAX) {
            shortestCycle = min(shortestCycle, shortestPath[i][i]);
        }
    }

    //print the shortest cycle
    if (shortestCycle == INT_MAX) {
        cout << "No cycle" << endl;
    } else {
        cout << "Shortest cycle: " << shortestCycle << endl;
    }

    //check if the result is correct
    if (shortestCycle == expectedOutput) {
        cout << "Correct" << endl;
    } else {
        cout << "Incorrect" << endl;
    }

    return shortestCycle;
}

//there are three testcases1.txt, 2.txt, 3.txt

void checkAllTestCases() {
    for (int i = 1; i <= 3; i++) {
        string fileName = "testcase" + to_string(i) + ".txt";
        InputData inputData = readInputData(fileName);
        coutInputData(inputData);
        shortestCycle(inputData);
    }
}

//display the result of all testcases
int main() {
    checkAllTestCases();
}