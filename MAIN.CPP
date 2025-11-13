#include <iostream>
#include <vector>
#include <string>
#include "Graph.h" 

Graph build_sample_graph() { // funcion que llena el grafo con lugares reales
    std::vector<std::string> names = {
        "La Minerva",
        "Catedral de Guadalajara",
        "Expo Guadalajara",
        "Estadio Jalisco",
        "Tlaquepaque Centro",
        "Andares",
        "Tec GDL"
    }; // nombres de los nodos

    Graph g(7, names); // se crea el grafo con los 7 nodos y cada uno de sus nombres

    // Distancias aproximadas (en km)
    g.add_edge(0, 2, 2.4);   // Minerva - Expo
    g.add_edge(0, 5, 4.3);   // Minerva - Andares
    g.add_edge(0, 1, 3.9);   // Minerva - Catedral
    g.add_edge(1, 3, 5.2);   // Catedral - Estadio Jalisco
    g.add_edge(1, 4, 6.8);   // Catedral - Tlaquepaque
    g.add_edge(1, 2, 5.0);   // Catedral - Expo
    g.add_edge(2, 4, 8.4);   // Expo - Tlaquepaque
    g.add_edge(2, 6, 7.1);   // Expo - Tec
    g.add_edge(5, 6,10.8);   // Andares - Tec
    g.add_edge(4, 6,16.5);   // Tlaquepaque - Tec
    g.add_edge(3, 4,7.2);   // Estadio - Tlaquepaque
    
    return g;
}  // las distancias reales entre las combinaciones de los nodos. todas las medidas pueden variar y estan en kilometros

int main() {
    Graph g = build_sample_graph(); // crea ek grafo con el resultado final
    g.print_graph(); // lista de conexiones

    int start = 0; // La Minerva fue el punto de partida que escogimos 
    std::cout << "Nodo origen: [" << g.names()[start] << "]\n\n";

    auto res = g.dijkstra(start);

    std::cout << "=== Distancias mínimas desde [" << g.names()[start] << "] ===\n";
    for (int i = 0; i < (int)res.dist.size(); ++i)
        std::cout << "A " << g.names()[i] << ": "
                  << res.dist[i] << " km\n";
    std::cout << "============================================================\n\n";

    std::cout << "=== Rutas más cortas ===\n";
    g.print_shortest_path(start, 5, res.parent, res.dist); // Andares
    g.print_shortest_path(start, 4, res.parent, res.dist); // Tlaquepaque Centro
    g.print_shortest_path(start, 6, res.parent, res.dist); // Tec de Monterrey GDL
} // imprime las rutas con las distancias mas cortas empezando en la minerva hacie tres lugares diferentes
