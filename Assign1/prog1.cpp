#include <bits/stdc++.h>
#include <complex>
#include <cmath>
using namespace std;
typedef complex < float > complexnum; // Saving time using the typedef 
typedef vector < complexnum >  dcomplex; // To construct a vector of complex numbers
double  pi=  3.141592653589793*2;


dcomplex FFTfunc( dcomplex ax, int num, bool work  ) {
	if ( num ==1) 
		return  ax;

	dcomplex evenarray, oddarray, finalans(num);

	for ( int i =0; i < num; i ++) {
		if ( i%2==0)
			evenarray.push_back(ax[i]);
		else oddarray.push_back(ax[i]);
	}	
  	complexnum iota = {0,1};
  	float alpha = pi/num;
  	alpha = work?-alpha:alpha;
  	complexnum omega = exp(iota*alpha);
  	complexnum theta= {1,0} ;
  	dcomplex  Y_even= FFTfunc(evenarray, num/2, work);
  	dcomplex Y_odd = FFTfunc(oddarray, num/2, work);
  	for ( int i =0;i< (num/2); i++) {
  		finalans[i]= Y_even[i] + theta*Y_odd[i];
  		finalans[i + num/2 ]= Y_even[i] - theta*Y_odd[i];
  		theta = theta*omega;
  	}
	return finalans;
}

int main() {
	bool work;
	int degree_bound;
	cin>>work;
	cin>>degree_bound;
	dcomplex polynomial;
	float r, im;
	for ( int i =0;i< degree_bound; i++) {
		cin>>r>>im;
		complexnum p = {r, im};
		polynomial.push_back(p);
	}
	dcomplex ansarray = FFTfunc(polynomial, degree_bound, work);
	if ( work) {
		for ( int i =0;i<ansarray.size(); i++) {
			ansarray[i]= ansarray[i]/float(degree_bound);	
		}
	}
	cout<<ansarray.size()<<" ";
	for ( int i =0;i< ansarray.size(); i++) {
		cout<<ansarray[i].real()<<" "<<ansarray[i].imag()<<" ";
	}	 
	return 0;
}