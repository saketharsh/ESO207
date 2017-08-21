#include <bits/stdc++.h>
#include <complex>
#include <cmath>
#include <stdio.h>
using namespace std;
typedef complex < double  > complexnum; // Saving time using the typedef 
typedef vector < complexnum >  dcomplex; // To construct a vector of complex numbers
double  twopi=  2.0*acos(-1);

dcomplex FFTfunc( dcomplex ax, int num, bool work  ) {
	if ( num ==1) 
		return  ax;
	dcomplex evenarray, oddarray, finalans(num);  //Array for even degree and odd degree and the final answer
	for ( int i =0; i < num; i ++) {
		if ( i%2==0)
			evenarray.push_back(ax[i]);
		else oddarray.push_back(ax[i]);
	}	
  	complexnum iota = {0,1};
  	double alpha = twopi/(double)num;
  	alpha = work?-alpha:alpha;
  	complexnum omega = exp(iota*alpha); // The primitive complex number that is used to generate all other complex numbers
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
	int tcases;
	cin>>tcases;
	while (tcases--) {
		bool work;
		double degree_bound;
		cin>>work;
		cin>>degree_bound;
		dcomplex polynomial;
		double r, im;
		for ( int i =0;i< degree_bound; i++) {
			cin>>r>>im;
			complexnum p = {r, im};
			polynomial.push_back(p);
		}
		dcomplex ansarray = FFTfunc(polynomial, degree_bound, work);
		if ( work) {
			double inv_de= 1/degree_bound;
			for ( int i =0;i<ansarray.size(); i++) {

				double real = ansarray[i].real(), comp = ansarray[i].imag();
				real= real/(double)degree_bound;
				comp = comp/(double)degree_bound;
				ansarray[i] = {real,comp};	
			}
		}
		for ( int i =0;i< ansarray.size(); i++) 
			printf("%.6f %.6f\n",ansarray[i].real(), ansarray[i].imag());
	}
	return 0;
}