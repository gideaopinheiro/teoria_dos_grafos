# teoria_dos_grafos

Os algorítimos Dijkstra, Kruskal e Prim recebem grafos com peso não-direcionados.

A entrada para os algoritmos Djikstra, Kruskal e Prim devem ser da seguinte forma:
Na primeira linha devem ser passados um par N M, onde N é a quantidade vértices e M é a quantidade de arestas.

Em seguida M linhas, cada uma com uma aresta do formato: V U W onde V e U (numerados a partir de 0) são os extremos da aresta V - U com peso W

Para o algorítmo BellmanFord deve ser passado o número de vértices (n) e em seguida n linhas com V U P, onde V e U são os vértices de origem e destino respectivamente e P o peso da aresta.
Como resultado o algoritmo exibe um vetor de custos e informa se há ou não ciclo negativo no grafo.