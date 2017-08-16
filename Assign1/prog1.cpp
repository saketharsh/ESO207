#include <bits/stdc++.h>
#include <complex>
using namespace std;
typedef vector < complex < double > > imgarray


imgarray FFTfunc( imgarray ax, int num, bool work  ) {
	if ( num ==0) 
		return vector < int > ax;
	imgarray evenarray;
	imgarray oddarray;

	for ( int i =0; i < num; i ++) {
		if ( i%2==0)
			evenarray.push_back(ax[i]);
		else oddarray.push_back(ax[i]);
	}
	complex omega = work? inverse: normal;
	// The actual logic will appear soon here.


}

int main() {
	bool work;
	int degree_bound;
	imgarray polynomial;
	cin>>work;
	cin>>degree_bound;
	for ( int i =0;i<degree_bound-1; i++) {
		cin>>real>>imaginary;
		complex < double >  coefficient = (real, imaginary);
		polynomial.push_back(coefficient);
	}
	imgarray ans = FFTfunc( polynomial , degree_bound, work);
	int len = ans.size();
	for ( int i =0;i< len, i++) {
		cout<<ans[i];
	} 
	return 0;

}