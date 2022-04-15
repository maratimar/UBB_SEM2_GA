#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
using namespace std;

// Numarul de varfuri din graful dat
#define V 6

  //returneza true daca exista drum de la nodul sursa la destinatie
  //in graful residual
  //adauga in vectirul parinte calea
bool bfs(int rGraph[V][V], int s, int t, int parent[])
{
    //creeaza un vector de vizitati si marcheaza toate varfurile ca
    //fiind nevizitate
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    // creeaza o coada, pun nodul sursa pe coada si il marchez ca vizitat
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    // Standard BFS Loop
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
                //daca am gasit o conexiune catre nodul destinatie
                //iesim din bfs si marcam parintele corespunzator
                //return true
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    //nu am ajuns la varful destinatie din varful sursa
    return false;
}

// returneaza fluxul maxim de la sursa la dest
int fordFulkerson(int graph[V][V], int s, int t)
{
    int u, v;


    //creez un graf rezidual in care pun capacitatile
    //grafului original
    int rGraph[V]
              [V]; // Graful rezidul unde rGraph[i][j]
                   // indica capacitatea reziduala a muchiei
                   // rGraph[i][j] este 0, atunci nu avem muchie)
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];

    int parent[V];

    int max_flow = 0; //fluxul initial primeste val 0


    while (bfs(rGraph, s, t, parent)) {
        //calculam fluxul maxim pentru calea gasita
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        //adaugam la max_flow
        max_flow += path_flow;
    }

    // returneaza fluxul
    return max_flow;
}

int main()
{
    // creez graful
    int graph[V][V]
        = { { 0, 16, 13, 0, 0, 0 }, { 0, 0, 10, 12, 0, 0 },
            { 0, 4, 0, 0, 14, 0 },  { 0, 0, 9, 0, 0, 20 },
            { 0, 0, 0, 7, 0, 4 },   { 0, 0, 0, 0, 0, 0 } };

    cout << "The maximum possible flow is "
         << fordFulkerson(graph, 0, 5);

    return 0;
}
