#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

// --- Prepare Abstract Data Types ---
constexpr int INF = numeric_limits<int>::max();

// struct Vertex {
//     int value;
//     int estD;
//
//     explicit Vertex(const int value) : value(value), estD(INF) { };
// };

struct WeightedEdge {
    int neighbor;
    int weight;

    WeightedEdge(const int neighbor, const int weight) : neighbor(neighbor), weight(weight){}
};

class WeightedGraph {
private:
    int numV;  // Why do I need this?
    vector<vector<WeightedEdge>> adjList;

public:
    explicit
    WeightedGraph(const int numV) {
       this->numV  = numV;
       this->adjList.resize(numV + 1);
    }

    void addEdge(int u, int v, int weight) {
        adjList[u].emplace_back(v, weight);
        adjList[v].emplace_back(u, weight);
    }

    std::vector<int> shortestPathDijsktra(int startV) {
        // The priority queue with MIN heap
        priority_queue<
            pair<int, int>,  // [distance, nodeId]
            vector<pair<int, int>>,
            std::greater<>
        > pqUnsureList ;

        // Init
        // estD
        vector<int> estDistanceList(numV + 1, INF);

        // MAIN
        estDistanceList[startV] = 0;
        pqUnsureList.emplace(0, startV);

        while (!pqUnsureList.empty()) {
            const auto [distance, vertice] = pqUnsureList.top();
            int dU = distance;
            int u = vertice;
            pqUnsureList.pop();

            if (dU > estDistanceList[u]) {
                continue;
            }

            for (auto& edge : adjList[u]) {
                auto v = edge.neighbor;
                auto vWeight = edge.weight;

                if (estDistanceList[u] + vWeight < estDistanceList[v] ) {
                    estDistanceList[v] = estDistanceList[u] + vWeight;
                    pqUnsureList.emplace(estDistanceList[v], v);
                }
            }
        }
        return estDistanceList;
    }

};

int main(){
    freopen("../input.txt", "r", stdin);

    cout << INF << endl;

    int nTestCases;
    cin >> nTestCases;

    while (nTestCases--) {
        int V, E, start;
        cin >> V >> E >> start;

        WeightedGraph graph(V);
        for (int i = 0; i < E; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            graph.addEdge(u, v, w);
        }

        std::vector<int> shortest_distances = graph.shortestPathDijsktra(start);

        for (int i = 1; i <= V; i++) {
            cout << shortest_distances[i] << " ";
        }
        cout << endl;

    }
}