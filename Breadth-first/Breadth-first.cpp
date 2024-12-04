#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Graph {
public:
    vector<vector<int>> adjList; // Adjacency list representation of the graph

    // Creates a graph with the node-size
    Graph(int nodes) {
        adjList.resize(nodes);
    }

    // Used for an undirected graph
    void addEdge(int firstNode, int secondNode) {
        adjList[firstNode].push_back(secondNode); // Adds the edge from the first node to the second node
        adjList[secondNode].push_back(firstNode); // Adds the edge from the second node to the first node
    }

    vector<int> neighbors(int node) {
        return adjList[node]; // Returns all the nodes that is connected to the current node
    }

    // Amount of nodes in the graph
    int nodeCount() {
        return adjList.size();
    }
};

static vector<vector<int>> BFS(Graph graph, int rootNode) {
  queue<int> foundNodes; // Queue for found nodes
  vector<int> visitedOrder; // Vector for visited node order
  vector<int> adversaryNodes; // Vector for adversary nodes
  vector<int> friendNodes; // Vector for friendNodes

  foundNodes.push(rootNode); // Adds the root node to the queue
  visitedOrder.push_back(rootNode); // Adds the root node to the visited array

  while (!foundNodes.empty()) { // Process each node in queue
    int currentNode = foundNodes.front(); // Saves the first node from the queue
    foundNodes.pop(); // Removes the first element from the queue
    vector<int> neighborList = graph.neighbors(currentNode); // Adds the neighbors from the current node to a neighbor list

    for (int neighbor : neighborList) { // Goes through all the neighbors in the neighbor list
      if (find(visitedOrder.begin(), visitedOrder.end(), neighbor) == visitedOrder.end()) { // Check if the neighbor node already is visited
        visitedOrder.push_back(neighbor); // Adds the neighbor to the visited vector
        foundNodes.push(neighbor); // Adds the neighbor node to the end of the queue
        
        if(find(friendNodes.begin(), friendNodes.end(), currentNode) != friendNodes.end()){ // Checks if the current node is a friend
            adversaryNodes.push_back(neighbor); // Add the node to the adversary vector
        }
        else if (currentNode == rootNode){ // Checks if the current node is the root node
            adversaryNodes.push_back(neighbor); // Add the node to the adversary vector
        }
        else{
            friendNodes.push_back(neighbor); // Add the node to the friend vector
        }
      }
    }
  }

  vector<vector<int>> resultVector;
  resultVector.push_back(friendNodes); 
  resultVector.push_back(adversaryNodes); 
  
  return resultVector; // Returns the visited order
}

// Main
int main() {
    Graph graph(16); // Create a graph with 16 nodes (0 to 15)

    // Adding edges to the graph
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 5);
    graph.addEdge(2, 6);
    graph.addEdge(3, 7);
    graph.addEdge(4, 8);
    graph.addEdge(5, 9);
    graph.addEdge(6, 10);
    graph.addEdge(7, 11);
    graph.addEdge(8, 12);
    graph.addEdge(9, 13);
    graph.addEdge(10, 14);
    graph.addEdge(11, 15);

    int startNode = 0; // Starting node

    vector<vector<int>> BFSResult = BFS(graph, startNode); // Returns the result from the BFS

    // Prints out the order the nodes got visited in
    cout << "BFS visited order starting from node " << startNode << ": ";
    cout << endl;
    
    cout << "Friendnodes: ";
    for (int node : BFSResult[0]) {
        cout << node << " ";
    }
    cout << endl;

    cout << "Adversarynodes: ";
    for (int node : BFSResult[1]) {
        cout << node << " ";
    }

    return 0;
}