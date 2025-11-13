#ifndef GRAPH_H
#define GRAPH_H

#include <vector> // para usar listas dinamicas
#include <string> 
#include <utility> // para poder usar pares de datos 

struct DijkstraResult { // para guardar el resultado final con la distancia mas corta y el nodo "padre" del que salio
    std::vector<double> dist;
    std::vector<int> parent;
};

class Graph { //representa el grafo con los nodos y los caminos 
public:
    Graph(int n, const std::vector<std::string>& names = {}); // crea el grafo con n numero de nodos 
    void add_edge(int u, int v, double weight, bool undirected = true); // agregar las conexiones con u,v y su peso de distancia y el undirected sirve para cuando se puede en los dos sentidos
    void print_graph() const; 
    DijkstraResult dijkstra(int start) const; // ejecuta el algoritmo 
    void print_shortest_path(int start, int dest,
                             const std::vector<int>& parent,
                             const std::vector<double>& dist) const; // muestra la distancia mas corta que ecnontro
    const std::vector<std::string>& names() const { return node_names; }

private:
    int n; // num de nodos
    std::vector<std::vector<std::pair<int,double>>> adj; // lista de adyacencia
    std::vector<std::string> node_names; // nombres de los lugares
    std::vector<int> reconstruct_path(int start, int dest,
                                      const std::vector<int>& parent) const;
};

#endif // GRAPH_H

