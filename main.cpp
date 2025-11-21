#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

// --- Prepare Abstract Data Types ---
constexpr int INF = numeric_limits<int>::max();

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
        priority_queue<
            pair<int, int>,  // [distance, nodeId]
            vector<pair<int, int>>,
            std::greater<>
        > unsurePQ ;

        vector<int> estD(numV + 1, INF);

        // MAIN
        estD[startV] = 0;
        unsurePQ.emplace(0, startV);

        while (!unsurePQ.empty()) {
            const auto [distance, vertice] = unsurePQ.top();
            const int dCurrentV = distance;
            const int currentV = vertice;
            cerr << "Processing vertex " << currentV << " with distance " << dCurrentV << endl;

            unsurePQ.pop();

            // Skip the Stale Entries
            if (dCurrentV > estD[currentV]) {
                continue;
            }

            for (auto& edge : adjList[currentV]) {
                auto v = edge.neighbor;
                auto vWeight = edge.weight;

                if (estD[currentV] != INF &&
                    estD[currentV] + vWeight < estD[v] ) {
                    estD[v] = estD[currentV] + vWeight;
                    unsurePQ.emplace(estD[v], v);
                    cerr << "  Updated vertex " << v << " to distance " << estD[v] << endl;
                }
            }
        }
        return estD;
    }

};

int main(){
    if (!freopen("input.txt", "r", stdin)) {
        cerr << "Error: Cannot open input.txt" << endl;
    };

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