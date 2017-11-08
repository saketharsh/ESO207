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
long long int vertexMap[10002];




void Max_Heapify( int i ) {
	int left = 2*i, right = 2*i +1;
	int largest = i;

	if (left <=size && distances[verticesheap[left]] < distances[verticesheap[i]])
		largest= left ;
	if (right <=size && distances[verticesheap[right]] < distances[verticesheap[i]])
		largest = right;
	if (largest != i) {
		int temp = verticesheap[i];
		verticesheap[i] = verticesheap[largest];
		verticesheap[largest] = temp;
		vertexMap[verticesheap[largest]] = i;
		vertexMap[temp] = largest;  
		Max_Heapify( largest);
	}
}

long long int Extract_Max( ) {
	long long int val = verticesheap[1];

	verticesheap[1] = verticesheap[size];
	vertexMap[verticesheap[size]] = 1;
	size--;
	Max_Heapify( 1);
	return val;
}




void BuildMaxHeap( ) {
	int len = size;

	for (  int i = len/2 ; i>=1; i--) {
		cout<<verticesheap[i];
		Max_Heapify( i);
	}
}

int main()  
{
	int deg;
	node temp_node;
	cin >>num>>source>>D>>C1>>C2>>D1>>D2>>W1>>W2>>W3;

	for ( int i=1; i <= num; i++) {
		deg = (i*C2 + i*i*D2 )%D;
		for ( int j =1; j <=deg; j++) {
			temp_node.vertex = ( i*C1 +j*D1)%num;
			temp_node.vertex+=1;
			temp_node.weight = (i*W1 + j*W2)%W3;
			adjlist[i].push_back(temp_node);
		}
	}
	

	for ( int i =0; i <= 2*num; i++ )
		distances[i] = -1*1000000;


	distances[source] = 0;
	for ( int i =0; i <=num ; i++) {
		verticesheap[i] = i;
		vertexMap[i] = i;
	}


	long long int size= num;
	BuildMaxHeap();
	
	
	


	while (size>0) {
		long long int vert= Extract_Max();
		for ( int  i =0; i < adjlist[vert].size(); i++) {
			if (distances[adjlist[vert][i].vertex] < distances[vert] - adjlist[vert][i].weight) {
				distances[adjlist[vert][i].vertex] = distances[vert] - adjlist[vert][i].weight;
				Max_Heapify( vertexMap[adjlist[vert][i].vertex]);
			}
		}
	}

	return 0;
}

