#include <bits/stdc++.h>
using namespace std;

int main () {
	stack < int > st;
	int ar[5] = {100000, 4,4,4,3};
	vector < int > b;
	for ( int i =1; i <=4; i ++) {
		if (ar[i]< ar[i-1]) 
			st.push(i-1);

		else {
			int x = st.top();
			while(ar[x]<=ar[i]) {
				st.pop();
				x= st.top();
			}
		}
		b.push_back(i- st.top());
	}
	for ( int i =0;i< b.size(); i++)
		cout<<b[i];
	return 0;

}