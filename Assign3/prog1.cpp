#include <bits/stdc++.h>
#include <cmath>
#include <stdio.h>
 
using namespace std;

int visited[10001] = {0} ;

stack < int > topsort;

vector < vector < int > > adjlist(1001);
vector < vector < int > > revadjlist(1001);


int compmin = 50000; // To compute minimum in the DFS component

void DFS( int  x ) {
	visited[x] = -1;
	if (x <=compmin) {
		compmin = x;
	}
	for ( int i =0; i < revadjlist[x].size(); i++) {
		if (visited[revadjlist[x][i]] == -2) {
			DFS(revadjlist[x][i]);
		}		
	}
	return ;	
}


int TopArray[1002] = {0};
int curval = 0;
// This will give me topological Ordering in the stack that i will use in for SCC
void TopSort(int x) {
	visited[x] = 1;
	for ( int i =0; i < adjlist[x].size(); i++) {
		if (!visited[adjlist[x][i]]) {
			TopSort(adjlist[x][i]);

		}
	}
		TopArray[curval++]= x;


	return;
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
			cin>>vertex;
		}
	}

	// To do Topological Sort so that we can find connected Components 
	for ( int i =0; i < num ; i ++) {
		if (!visited[i]) {
			TopSort(i);
		}
	}
	// for ( int i =0; i <num ; i++) 
	// 	cout<<TopArray[i];

	// Transfer topsort order to array 
	vector < int > starray(num) ;
	for ( int i =num-1; i >= 0; i--) {		
		starray[num -1 - i]= TopArray[i];
	}

	// for ( int i =0; i< starray.size(); i++) 
	// 	cout<<starray[i]<<endl;


	vector < vector < int > > finaladj(1002); // adjacency list of strongly connected components 


	for ( int i =0; i < 10001; i++)
		visited[i] = -2 ;
	int lastcompmin = 4500;

	for ( int i =starray.size()-1; i>=0; i--) {
		if (visited[starray[i]] == -2) {
			DFS(starray[i]);
			for ( int j =0; j < 1002; j++) {
				if (visited[j] ==-1)
					visited[j] = min(min(compmin,lastcompmin+1), starray[i]);
			}
			lastcompmin = compmin;
			compmin = 50000;

		}
	}

	for ( int i =0; i < num ; i++) 
		cout <<visited[i]<<endl;
	return 0;
}