#include <bits/stdc++.h>
#include <cmath>
 
using namespace std;

int visited[10001] ;
memset (visited, 0, 10001);
stack < int > topsort;
vector < vector < int > > adjlist(1001);
vector < vector < int > > revadjlist(1001);



void DFS( int  x, int compnumber ) {
	visited[x] = compnumber;
	for ( int i =0; i < revadjlist[x].size(); i++) {
		if (!visited[revadjlist[x][i]]) {
			DFS(revadjlist[x][i]);
		}
	}
	
}




// This will give me topological Ordering in the stack that i will use in for SCC
void TopSort(int x) {
	visited[x] = 1;
	for ( int i =0; i < adjlist[x].size(); i++) {
		if (!visited[adjlist[x][i]]) {
			TopSort(adjlist[x][i]);
			topsort.push(adjlist[x][i]);
		}
	}
}

int main () {
	int num ;
	cin>>num;
	int vertex;

	//  Making adjacency List for  graph and its reverse  at once 
	for ( int i =0; i < num; i++) {
		cin>>vertex;
		while(vertex !=-1) {
			adjlist[i].push_back(vertex);
			revadjlist[vertex].push_back(i);
		}
	}

	// To do Topological Sort so that we can find connected Components 
	for ( int i =0; i < num ; i ++) {
		if (!visited[i]) {
			TopSort(i);
		}
	}
	vector < int > starray ;
	for ( int i =0; i < topsort.size(); i++) {
		int x = topsort.top();
		starray.push_back(x);
		topsort.pop();
	}


	memset(visited, 0 , 10001);
	int comp=0;
	for ( int i =starray.size()-1; i>=0; i--) {
		if (!visited[starray[i]]) {
			DFS(starray[i], comp++);
		}
	}
	//comp stores the total number of components that are formed , but it has to made in order .
	


	// Now what is left is to do a DFS and get the connected components from it .






	return 0;
}