#include <bits/stdc++.h>
#include <cmath>
#include <stdio.h>
 
using namespace std;

int visited[10001] = {0} ;

stack < int > topsort;

vector < vector < int > > adjlist(1001);
vector < vector < int > > revadjlist(1001);
vector < set < int >  > finaladj(1002); // adjacency list of strongly connected components 


int CompNum =1; // To compute minimum in the DFS component

void DFS( int  x ) {
	visited[x] =CompNum ;
	
	for ( int i =0; i < revadjlist[x].size(); i++) {
		if (visited[revadjlist[x][i]] == -2) {
			DFS(revadjlist[x][i]);
		} else {
			if (visited[revadjlist[x][i]]!=CompNum)
				finaladj[visited[revadjlist[x][i]]].insert(CompNum);
		}		
	}
	return ;	
}


int TopArray[1002] = {0};
int curval = 0;
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

	for ( int i =0; i < num; i++) {
		cin>>vertex;
		while(vertex !=-1) {
			adjlist[i].push_back(vertex);
			revadjlist[vertex].push_back(i);
			cin>>vertex;
		}
	}

	for ( int i =0; i < num ; i ++) {
		if (!visited[i]) {
			TopSort(i);
		}
	}
	
	vector < int > starray(num) ;
	for ( int i =num-1; i >= 0; i--) {		
		starray[num -1 - i]= TopArray[i];
	}
	for ( int i =0; i < 10001; i++)
		visited[i] = -2 ; // Unvisited value

	for ( int i =starray.size()-1; i>=0; i--) {
		if (visited[starray[i]] == -2) {
			DFS(starray[i]);
			CompNum++;
		}
	}
	
	
	int OrderID=0;
	int orderid[1002], copyVisited[1002];
	for ( int i =0; i <1002; i++) 
		copyVisited[i] = visited[i];

	for ( int i =0; i < num ; i++) {
		if (i != visited[i] && visited[i] != -2) {
			int val = visited[i];
			for (int j =0; j < num ; j++) {
				if (visited[j] == val ) {
					visited[j]= -2;
					orderid[j]= OrderID;
				}
			}
			OrderID++;
		}
	}



	
	

	cout<<OrderID+1<<endl;
	
	set<int>::iterator it;
	for ( int i =0; i < OrderID+1; i++) {
		it = finaladj[revCompMap[i]].begin();
		while(it!= finaladj[revCompMap[i]].end()) {
			cout<<compMap[*it]<<" ";
			it++;
		}
		cout<<-1<<endl;
	} 	
	return 0;
}