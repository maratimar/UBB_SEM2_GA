#include    <iostream>
#include    <fstream>
#include    <queue>
#include    <vector>
using namespace std;
ifstream fin("dijkstra.in");
ofstream fout("dijkstra.out");
const int NMax = 50005;
const int oo = (1 << 30); //shiftare pe biti, constanta oo va primi valoarea maxima a int-ului;
int N, M;
int D[NMax]; //vectorul de distante
bool InCoada[NMax];
vector < pair <int,int> > G[NMax];
struct compara  //compara distantele pentru doua noduri
{
    bool operator()(int x, int y)
    {
        return D[x] > D[y];
    }
};
priority_queue<int, vector<int>, compara> Coada;
void Citeste()  //citirea datelor de intrare din fisier,nr de noduri,muchii,arcele si costurile aferente
{
    fin >> N >> M;
    for(int i = 1; i <= M; i++)
    {
        int x, y, c;
        fin >> x >> y >> c;
        G[x].push_back(make_pair(y,c));
    }
}
void Dijkstra(int nodStart)
{
    for(int i = 1; i <= N; i++)  //pentru fiecare nod distanta infinit
        D[i] = oo;
    D[nodStart]=0;  //pentru nodul de start distanta 0;
    Coada.push(nodStart);  //punem in coada nodul de start
    InCoada[nodStart] = true;   //marcam ca e in coada
    while(!Coada.empty())
    {
        int nodCurent = Coada.top();  //cat timp coada nu e goala,extragem nodul curent
        Coada.pop();
        InCoada[nodCurent] = false;
        for(size_t i = 0; i < G[nodCurent].size(); i++)
        {
            int Vecin = G[nodCurent][i].first;  //parcurgem toti vecinii nodului curent
            int Cost = G[nodCurent][i].second;  //acesam costul
            if(D[nodCurent] + Cost < D[Vecin])
            {
                D[Vecin] = D[nodCurent] + Cost; //actualizam costul
                if(InCoada[Vecin] == false)  //daca vecinul ne se afla in coada,il adaugam
                {
                    Coada.push(Vecin);
                    InCoada[Vecin] = true;
                }
            }
        }
    }
}
void Afiseaza()  //afisarea distantelor cautate;
{
    for(int i = 2; i <= N; i++)
    {
        if(D[i] != oo)
            fout << D[i] << " ";
        else
            fout << "0 ";
    }
}
int main()
{
    Citeste();
    Dijkstra(1);
    Afiseaza();
}
