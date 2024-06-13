#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <utility>

// Variáveis globais para armazenar a face atual e todas as faces encontradas
std::vector<int> face;
std::vector<std::vector<int>> faces;

// Função para calcular a inclinação relativa entre dois pontos (x1, y1) e (x2, y2)
double relativeInclination(double x1, double x2, double y1, double y2){
    return std::atan2(y1 - y2, x1 - x2);
}

// Função para ordenar as conexões de um nó com base na inclinação relativa em relação ao nó de referência
std::vector<int> sort_connections(int i, std::vector<int>& connections, std::vector<std::pair<double, double>>& pos){
    double x_ref = pos[i].first;
    double y_ref = pos[i].second;
    std::sort(connections.begin(), connections.end(), [&](int a, int b) {
        double incl_a = relativeInclination(pos[a].first, x_ref, pos[a].second, y_ref);
        double incl_b = relativeInclination(pos[b].first, x_ref, pos[b].second, y_ref);
        return incl_a < incl_b;
    });

    return connections;
}

// Função para imprimir todas as faces encontradas
void printFaces(){
    std::cout << faces.size() << std::endl;
    for(const auto& f : faces){
        std::cout << f.size() << " ";
        for(int node : f){
            std::cout << node + 1 << " "; // Converte de 0-based para 1-based index
        }
        std::cout << std::endl;
    }
}

// Função de DFS para encontrar e armazenar faces no grafo
void dfs(int start, int current, int direction, std::vector<std::vector<int>>& graph, std::vector<std::vector<bool>>& visited, std::vector<std::pair<double, double>>& positions){
    visited[current][direction] = true; // Marca a meia aresta como visitada

    int next_node = graph[current][direction]; // Próximo nó a ser visitado
    face.push_back(next_node); // Adiciona o nó atual à face

    int next_direction = -1;
    // Encontrar a meia aresta direcionada de next_node de volta para current
    for (int k = 0; k < graph[next_node].size(); k++) {
        if (graph[next_node][k] == current) {
            next_direction = (k + 1) % graph[next_node].size(); // Próxima meia aresta no sentido horário
            break;
        }
    }

    // Continua a DFS se a meia aresta ainda não foi visitada
    if (!visited[next_node][next_direction]) {
        dfs(start, next_node, next_direction, graph, visited, positions);
    } else if (next_node == start) {
        // Se voltar ao nó inicial, a face está completa
        faces.push_back(face);
        face.clear(); // Limpa a face para a próxima iteração
    }
}

int main() {
    int n, m;
    std::cin >> n >> m; // Lê o número de nós e arestas

    std::vector<std::vector<int>> graph(n);
    std::vector<std::vector<bool>> visited(n);
    std::vector<std::pair<double, double>> positions(n); 

    // Lê as posições dos nós e suas conexões
    for(int i = 0; i < n; i++){
        double x, y;
        std::cin >> x >> y;

        positions[i] = {x, y};

        int k;
        std::cin >> k;
        while (k--) {
            int a;
            std::cin >> a;
            a--;
            graph[i].push_back(a);
            visited[i].push_back(false);
        }
    }

    // Ordena as conexões de cada nó com base na inclinação relativa
    for(int i = 0; i < n; i++){
        graph[i] = sort_connections(i, graph[i], positions);
    }

    // Executa a DFS para encontrar todas as faces
    for(int i = 0; i < visited.size(); i++){
        for(int j = 0; j < visited[i].size(); j++){
            if (!visited[i][j]) {
                face.push_back(i); // Inicia uma nova face
                dfs(i, i, j, graph, visited, positions); // Inicia a DFS
            }
        }
    }

    printFaces(); // Imprime todas as faces encontradas

    return 0;
}
