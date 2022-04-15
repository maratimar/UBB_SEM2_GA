#include    <fstream>
#include    <iostream>
#include    <vector>
using namespace std;

ifstream    fin("color.in");
ofstream    fout("color.out");


vector<int> L[101];
vector <bool> available;
vector<int> color;

int main() {
	int n = 0, m = 0;
	fin >> n >> m;  //citesc numarul de noduri si de muchii din fisier
	for (int a, b, i = 1; i <= m; i++) {
		fin >> a >> b;  //citesc din fisier cele m muchii
		L[a].push_back(b);  //retin muchiile intr-un vector
		L[b].push_back(a);
	}

	for (int i = 0; i <= n; i++) {
		color.push_back(-1);
		available.push_back(false);
	}
	color[0] = 0;

	for (int i = 1; i <= n; i++) {

		for (vector<int> ::iterator st = L[i].begin(), dr = L[i].end(); st != dr; st++)
			if (color[*st] != -1)
				available[color[*st]] = true;

		int first_avail_color = 0;
		for (; first_avail_color <= n and available[first_avail_color]; first_avail_color++);
		color[i] = first_avail_color;

		for (vector<int> ::iterator st = L[i].begin(), dr = L[i].end(); st != dr; st++)
			if (color[*st] != -1)
				available[color[*st]] = false;
	}

	for (int i = 0; i <= n; i++)
		fout << "Nodul " << i << " are culoarea " << color[i] << '\n';
	return 0;
}


