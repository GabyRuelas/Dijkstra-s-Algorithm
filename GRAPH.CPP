#include "Graph.h"
#include <iostream>
#include <queue> //para la cola de prioridad
#include <limits> // infinito
#include <iomanip> // poder mostrardecumales 
#include <algorithm> // invertir listas 

Graph::Graph(int n, const std::vector<std::string>& names) // inicializa el grafo con n num de nodos y sus nombres
    : n(n), adj(n), node_names(names) {
    if ((int)node_names.size() != n) {
        node_names.resize(n);
        for (int i = 0; i < n; ++i)
            if (node_names[i].empty())
                node_names[i] = "Nodo " + std::to_string(i);
    }
}

void Graph::add_edge(int u, int v, double weight, bool undirected) { // comprueba que los indicesexistan
    if (u < 0 || u >= n || v < 0 || v >= n) return; // gaurda la conexion del nodo en u y si hay doble sentido se guarda en v
    adj[u].push_back({v, weight});
    if (undirected) adj[v].push_back({u, weight});
}

void Graph::print_graph() const {
    std::cout << "=== Grafo (lista de adyacencia) ===\n"; // imprime el encabezado
    for (int u = 0; u < n; ++u) { // ciclo para recorrer cada nodo con su no,bre
        std::cout << u << " [" << node_names[u] << "] -> ";
        for (auto &edge : adj[u])
            std::cout << "(" << edge.first << " " << node_names[edge.first]
                      << ", " << edge.second << " km) ";
        std::cout << "\n";
    }
    std::cout << "===================================\n\n"; // muestra todas las conexiones desde el nodo en el que esta
}

DijkstraResult Graph::dijkstra(int start) const { 
    const double INF = std::numeric_limits<double>::infinity(); // define infinito como valor inicial para la distancia
    std::vector<double> dist(n, INF); // distancia minima
    std::vector<int> parent(n, -1); // aqui se reconstruye el camino
    std::vector<bool> visited(n, false); // marca si el nodo ya fue analizado

    using PDI = std::pair<double,int>; 
    std::priority_queue<PDI, std::vector<PDI>, std::greater<PDI>> pq; // gaurda por prioridad la distancia acumulado y en nodo

    dist[start] = 0.0;
    pq.push({0.0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (visited[u]) continue;
        visited[u] = true; // revisa el nodo que tiene menor distancia y que no fue visitado. si fue visitado se lo salta

        for (auto &edge : adj[u]) { // recorre los nidos vecinos v, u y el peso 
            int v = edge.first;
            double w = edge.second;
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v}); // si se encuentra una ruta mas corta hacia v, se actualiza y se guarda en el heap
            }
        }
    }
    return {dist, parent};
}

std::vector<int> Graph::reconstruct_path(int start, int dest,
                                         const std::vector<int>& parent) const {
    std::vector<int> path;
    for (int v = dest; v != -1; v = parent[v])
        path.push_back(v);
    std::reverse(path.begin(), path.end());
    if (path.front() != start) path.clear();
    return path; // empieza desde el destino y se va guiando por los pasdres y despues invierte el camino para poder mostrarlo bien
}

void Graph::print_shortest_path(int start, int dest,
                                const std::vector<int>& parent,
                                const std::vector<double>& dist) const {
    auto path = reconstruct_path(start, dest, parent);
    if (path.empty()) {
        std::cout << "No existe camino de " << node_names[start]
                  << " a " << node_names[dest] << ".\n";
        return;
    }
    std::cout << "Ruta más corta " << node_names[start]
              << " -> " << node_names[dest] << ":\n  ";
    for (size_t i = 0; i < path.size(); ++i) { 
        std::cout << node_names[path[i]];
        if (i + 1 < path.size()) std::cout << " -> ";
    }
    std::cout << "\n  Distancia total: "
              << std::fixed << std::setprecision(2) << dist[dest] << " km\n\n";
}
