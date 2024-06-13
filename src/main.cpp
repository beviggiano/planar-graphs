#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <utility>

using namespace std;

vector<int> face;
vector<vector<int>> faces;

double relativeInclination(double x1, double x2, double y1, double y2){
    return atan2(y1 - y2, x1 - x2);
}

vector<int> sort_connections(int i, vector<int>& connections, vector<pair<double, double>>& pos){
    double x_ref = pos[i].first;
    double y_ref = pos[i].second;
    sort(connections.begin(), connections.end(), [&](int a, int b) {
        double incl_a = relativeInclination(pos[a].first, x_ref, pos[a].second, y_ref);
        double incl_b = relativeInclination(pos[b].first, x_ref, pos[b].second, y_ref);
        return incl_a < incl_b;
    });

    return connections;
}

void printFaces(){
    cout << faces.size() << endl;
    for(const auto& f : faces){
        cout << f.size() << " ";
        for(int node : f){
            cout << node + 1 << " ";
        }
        cout << endl;
    }
}

void dfs(int start, int current, int direction, vector<vector<int>>& graph, vector<vector<bool>>& visited, vector<pair<double, double>>& positions){
    visited[current][direction] = true;

    int next_node = graph[current][direction];
    face.push_back(next_node);

    // Encontrar a meia aresta direcionada de next_node de volta para current
    int next_direction = -1;
    for (int k = 0; k < graph[next_node].size(); k++) {
        if (graph[next_node][k] == current) {
            next_direction = (k + 1) % graph[next_node].size();
            break;
        }
    }

    if (!visited[next_node][next_direction]) {
        dfs(start, next_node, next_direction, graph, visited, positions);
    } else if (next_node == start) {
        faces.push_back(face);
        face.clear();
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n);
    vector<vector<bool>> visited(n);
    vector<pair<double, double>> positions(n); 

    for(int i = 0; i < n; i++){
        double x, y;
        cin >> x >> y;

        positions[i] = {x, y};

        int k;
        cin >> k;
        while (k--) {
            int a;
            cin >> a;
            a--;
            graph[i].push_back(a);
            visited[i].push_back(false);
        }
    }

    for(int i = 0; i < n; i++){
        graph[i] = sort_connections(i, graph[i], positions);
    }

    for(int i = 0; i < visited.size(); i++){
        for(int j = 0; j < visited[i].size(); j++){
            if (!visited[i][j]) {
                face.push_back(i);
                dfs(i, i, j, graph, visited, positions);
            }
        }
    }

    printFaces();

    return 0;
}
