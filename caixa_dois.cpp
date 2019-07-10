#include <iostream>
#include <iterator>
#include <sstream>
#include <forward_list>
#include <list>
#include <utility>
#include <queue>

#define MAX_CORNERS 10000
#define MAX_STREETS 100000
#define INF 0x3f3f3f3f

using namespace std;

typedef pair<int, int> iPair;

class Vertice
{
  public:
    int min_key, max_key;
    forward_list<pair<int, int>> adj;

    Vertice()
    {
        min_key = INF;
        max_key = -1;
    }

    void addEdge(int v, int w)
    {
        adj.push_front(make_pair(w, v));
    }
};

void addGraphEdge(Vertice *G, int u, int v, int w)
{
    G[u].addEdge(v, w);
    G[v].addEdge(u, w);
}

void setMinSTvalue(Vertice *G)
{

    bool present[MAX_CORNERS] = {0};
    priority_queue<iPair, vector<iPair>, greater<iPair>> min_pq;

    G[0].min_key = 0;

    min_pq.push(make_pair(G[0].min_key, 0));

    while (!min_pq.empty())
    {
        int u = min_pq.top().second;
        min_pq.pop();
        present[u] = true;

        for (forward_list<iPair>::iterator it = G[u].adj.begin(); it != G[u].adj.end(); ++it)
        {
            int v = it->second;
            int w = it->first;

            if (present[v] == false && G[v].min_key > w)
            {
                G[v].min_key = w;
                min_pq.push(make_pair(G[v].min_key, v));
            }
        }
    }
}

void setMaxSTvalue(Vertice *G)
{
    bool present[MAX_CORNERS] = {0};

    priority_queue<iPair, vector<iPair>> max_pq;

    G[0].max_key = 0;

    max_pq.push(make_pair(G[0].max_key, 0));

    while (!max_pq.empty())
    {
        int u = max_pq.top().second;
        max_pq.pop();
        present[u] = true;

        //for (forward_list<iPair>::iterator it = G[u].adj.begin(); it != G[u].adj.end(); ++it)
        for (iPair pair : G[u].adj)
        {
            int v = pair.second;
            ;
            int w = pair.first;

            if (present[v] == false && G[v].max_key < w)
            {
                G[v].max_key = w;
                max_pq.push(make_pair(G[v].max_key, v));
            }
        }
    }
}

int main()
{
    int corners, streets;

    string lineInput;
    vector<int> results;
    int runs = 0;
    while (true)
    {

       cin >> corners >> streets;

        if (corners == 0 && streets == 0)
        {
            break;
        }

        
        Vertice *graph = new Vertice[corners];

        for (int i = 0; i < streets; i++)
        {
            /* getline(cin, lineInput);
            std::istringstream iss(lineInput);
 */
            int u, v, w;

            cin >> u >> v >> w;

            addGraphEdge(graph, u - 1, v - 1, w);
        }

        setMinSTvalue(graph);

        setMaxSTvalue(graph);

        int minSTSum = 0;
        int maxSTsum = 0;
        for (int i = 0; i < corners; ++i)
        {
            minSTSum += graph[i].min_key;
            maxSTsum += graph[i].max_key;
        }
        
        printf("%d\n",maxSTsum - minSTSum);
    }
 
    return 0;
}
