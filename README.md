# Dijkstra-s-Algorithm
Este proyecto utiliza el algoritmo de Dijkstra en C++ con el propósito de determinar cuáles son las rutas más breves entre los lugares reales de Guadalajara, en Jalisco (México).
Los pesos de las aristas indican distancias estimadas, calculadas en Google Maps, entre los puntos escogidos.

El algoritmo de Dijkstra tiene como objetivo encontrar la vía más corta desde un nodo inicial hacia todos los demás nodos en un grafo ponderado que no tenga pesos negativos.

Proceso en términos generales:
Todos los nodos, a excepción del nodo inicial (0), se les asigna una distancia infinita.
Se emplea una cola de prioridad (min-heap) para escoger siempre el nodo más próximo que aún no ha sido visitado.
Cuando se examina un nodo, si se descubre un camino más corto, las distancias a sus nodos vecinos se actualizan.
Cuando termina, cada nodo tiene la distancia mínima y un "padre" que posibilita la reconstrucción de la ruta.
