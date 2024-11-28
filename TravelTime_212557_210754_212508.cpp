#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>

using namespace std;

struct InputData {
    map<pair<string, string>, int> edges;
    vector<vector<string>> paths;
    double number;
};

InputData readInputData(const string& fileName) {
    ifstream file(fileName);
    InputData inputData;
    string line;

    // Read the edges
    while (getline(file, line) && !line.empty()) {
        stringstream ss(line);
        string edge, item;
        getline(ss, edge, ' ');
        pair<string, string> edgePair = make_pair(edge.substr(0, 1), edge.substr(2, 1));
        getline(ss, item);
        inputData.edges[edgePair] = stoi(item);
    }

    // Read the paths
    while (getline(file, line) && !line.empty()) {
        vector<string> path;
        stringstream ss(line);
        string item;
        while (getline(ss, item, '-')) {
            path.push_back(item);
        }
        inputData.paths.push_back(path);
    }

    // Read the number
    file >> inputData.number;

    return inputData;
}

//cout data from the file
void coutData(InputData inputData) {
//dont put - at the end of the line
    for (const auto& edge : inputData.edges) {
        cout << edge.first.first << "-" << edge.first.second << " " << edge.second << endl;
    }

    for (const auto& path : inputData.paths) {
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size() - 1) {
                cout << "-";
            }
        }
        cout << endl;
    }

    cout << inputData.number << endl;
}

//function to print all possible paths and their costs
void printAllPaths(vector<vector<string>>& paths, map<pair<string, string>, int>& edges) {
    for (const auto& path : paths) {
        int cost = 0;
        for (int i = 0; i < path.size() - 1; i++) {
            pair<string, string> edge = make_pair(path[i], path[i + 1]);
            cost += edges[edge];
        }
        cout << "Path: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size() - 1) {
                cout << "-";
            }
        }
        cout << " Cost: " << cost << endl;
    }

    cout<<"number of paths: "<<paths.size()<<endl;
}

//the edges also have reverse direction so we need to add them to the map as well to be able to calculate the cost of the path
void addReverseEdges(map<pair<string, string>, int>& edges) {
    map<pair<string, string>, int> tempEdges = edges;
    for (const auto& edge : tempEdges) {
        pair<string, string> reverseEdge = make_pair(edge.first.second, edge.first.first);
        edges[reverseEdge] = edge.second;
    }
}

//function to calculate the average time to move between locations
double averageTimeToMoveBetweenLocations(vector<vector<string>>& paths, map<pair<string, string>, int>& edges) {
    double sum = 0;
    for (const auto& path : paths) {
        int cost = 0;
        for (int i = 0; i < path.size() - 1; i++) {
            pair<string, string> edge = make_pair(path[i], path[i + 1]);
            cost += edges[edge];
        }
        sum += cost;
    }

    return sum / paths.size();
}

//there are 3 file with different tescases testcase1, testcase2, testcase3
//function to check if the output is correct in all 3 testcases

bool checkOutput(InputData& inputData, double output) {
    if (inputData.number == output) {
        return true;
    }
    return false;
}

//check all testcases

void checkAllTestCases() {
    for (int i = 1; i <= 3; i++) {
        string fileName = "testcase" + to_string(i) + ".txt";
        InputData inputData = readInputData(fileName);
        addReverseEdges(inputData.edges);
        double output = averageTimeToMoveBetweenLocations(inputData.paths, inputData.edges);
        if (checkOutput(inputData, output)) {
            cout << "Testcase " << i << " passed" << endl;
        }
        else {
            cout << "Testcase " << i << " failed" << endl;
        }
    }
}

int main(){
//output data from the file
    InputData inputData = readInputData("testcase1.txt");
    coutData(inputData);

    addReverseEdges(inputData.edges);
    printAllPaths(inputData.paths, inputData.edges);
    cout << "Average time to move between locations: " << averageTimeToMoveBetweenLocations(inputData.paths, inputData.edges) << endl;

    checkAllTestCases();


}