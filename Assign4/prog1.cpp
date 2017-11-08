#include <bits/stdc++.h>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

struct node {
	long long int vertex;
	long long int weight;
};

vector < vector < node > >  adjlist(10002);
long long int num, source,D, C1, C2, D1, D2, W1, W2, W3;
long long int distances[10002];
long long int  verticesheap[10002];
long long int size;
long long int position[10002];


void Update_Heap( long long int i) {
	long long int parent = i/2; 
	while ((distances[verticesheap[parent]] < distances[verticesheap[i]]) && parent > 0) {
		long long int temp = verticesheap[i];
		verticesheap[i] = verticesheap[parent];
		position[verticesheap[parent]] = i;		
		verticesheap[parent] = temp;
		position[temp] = parent;
		parent = parent/2;
		i=i/2;
	}
}



void Max_Heapify( long long int i ) {
	long long int left = 2*i, right = 2*i +1;
	long long int largest = i;

	if (left <=size && distances[verticesheap[left]] > distances[verticesheap[i]])
		largest= left ;
	if (right <=size && distances[verticesheap[right]] > distances[verticesheap[largest]])
		largest = right;
	if (largest != i) {
		long long int temp = verticesheap[i];
		verticesheap[i] = verticesheap[largest];
		position[verticesheap[largest]] = i;
		verticesheap[largest] = temp;
		position[temp] = largest;  
		Max_Heapify(largest);
	}
}

long long int Extract_Max( ) {
	long long int val = verticesheap[1];

	verticesheap[1] = verticesheap[size];
	position[verticesheap[size]] = 1;
	size--;
	Max_Heapify(1);
	return val;
}




void BuildMaxHeap( ) {
	long long int len = size;
	for (  long long int i = len/2 ; i>=1; i--) {
		Max_Heapify( i);
	}
}

int main()  
{
	long long int deg;
	node temp_node;
	cin >>num>>source>>D>>C1>>C2>>D1>>D2>>W1>>W2>>W3;

	for ( long long int i=1; i <= num; i++) {
		deg = (i*C2 + i*i*D2 )%D;
		for ( long long int j =1; j <=deg; j++) {
			temp_node.vertex = ( i*C1 +j*D1)%num;
			temp_node.vertex+=1;
			temp_node.weight = (i*W1 + j*W2)%W3;
			adjlist[i].push_back(temp_node);
		}
	}	

	for ( int i =0; i <= num; i++ )
		distances[i] = -1*1000000000;


	distances[source] = 0;
	for ( long long int i =1; i <=num ; i++) {
		verticesheap[i] = i;
		position[i] = i;
	}


	size= num;
	BuildMaxHeap();

	
	while (size>0) {
		long long int vert= Extract_Max();
		for ( long long int  i =0; i < adjlist[vert].size(); i++) {
			if (distances[adjlist[vert][i].vertex] < distances[vert] - adjlist[vert][i].weight) {
				distances[adjlist[vert][i].vertex] = distances[vert] - adjlist[vert][i].weight;
				Update_Heap( position[adjlist[vert][i].vertex]);
			}
		}
	}
	for ( long long int i =1 ; i <=num ; i++)  {
		if (distances[i] == -1000000000)
			cout<<i<<" "<<-1<<endl;
		else 
			cout<<i<<" "<<-1*distances[i]<<endl;
	}


	return 0;
}

