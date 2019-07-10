#include <iostream>
#include <sstream>
#include <forward_list>

using namespace std;

class Vertice
{
  public:
    int color;
    forward_list<int> lista_adjacencia;

    Vertice()
    {
        color = 1;
        //lista_adjacencia = new forward_list();
    }
};

void DFSVisit(Vertice* graph, int u)
{
    graph[u].color = 2;
    for (int &v : graph[u].lista_adjacencia)
    {
        if (graph[v].color == 1)
        {
            DFSVisit(graph, v);
        }
    }
    graph[u].color = 3;
}

/**
 * Implementação da Busca em profundidade
 */
int DFSComponents(Vertice* graph, int gSize)
{
    int components = 0;
    for (int i = 1; i <= gSize; i++)
    {
        if (graph[i].color == 1){
            DFSVisit(graph, i);
            components++;
        }
    }

    return components;
};

int main()
{

    int nVertices, nLines;

    
    cin >> nVertices >> nLines;

    // Grafo como um array de vertices
    Vertice graph[nVertices + 1];
   

    // Percorrendo a entrada para preencher o grafo
    for (int i = 0; i < nLines; i++)
    {
        // Leitura dos valores de entrada
        int v, relative;
        
        cin >> v >> relative;

        //gerando a familia
        graph[v].lista_adjacencia.push_front(relative);
        graph[relative].lista_adjacencia.push_front(v);
    }

    // Obtendo a quantidade de familias
    int nFamilies = DFSComponents(graph, nVertices);

    cout << nFamilies << "\n";
    return 0;
}
