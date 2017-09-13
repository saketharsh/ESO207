#include <bits/stdc++.h>
#include <iostream>
using namespace std;
#include <stack>
#include <iomanip>


float solve(float op1, float op2, char ch)  // Solve Function 
{
	switch(ch)
	{
		case '+': return (op1+op2);
		case '-': return (op1-op2);
		case '*': return (op1*op2);
		case '/': return (op1/op2);
		case '%': return fmod(op1,op2);
	}
}

int  isChar(string s)   // TO check if it is a string or not 
{
	if(s.size() >1 ) return false;

	switch (s[0]) {
		case '+': return 1;
		case '-': return 1;
		case '*': return 2;
		case '/': return 3;
		case '(': return 4;
		case ')': return 4;
		case '%': return 3;
		default: return false;
	}
}

void fraud( int a) {
	int i =0;
	while (i<a) {
		i++;
	}
}

int preference(char a)
{
    switch(a)
    {
        case '+': return 1; break;
        case '-': return 1; break;
        case '*': return 3; break;
        case '/': return 4; break;
        case '%': return 4; break;
        case 'u': return 5;break;
        default : return 0;
    }
}
 
int main() {
    int len;
    cin>>len;


    stack <float> operands;
    stack <char> operators; 


    char p; 
    int leftBCount=0, rightBCount =0; int currintindex=-10, j=0, previndex, currcharindex=-20, prevcharindex;
    
    char prevchar, currchar='$';
    string d;

    for( int i=0; i<len ; i++)
    {
	    cin>>d;
	    if(!isChar(d) ) 
	    {
	        previndex = currintindex; currintindex=i; 

	        if(previndex==currintindex-1) {
	        	cout<<"Malformed expression"; return 0;
	        }
	        float num = stoi(d);
	        operands.push(num); 
	    }


	    else 
	    {
	        p=d[0];

	        prevcharindex = currcharindex; currcharindex=i; 

	        prevchar=currchar; currchar=p;

	        if(prevchar=='$'&& p=='-') p='u';

	        if(prevcharindex==currcharindex-1) 

	        {
	            if(prevchar=='(')
	            {
	                if (currchar=='-') p='u';
	                else {
	                	if(currchar!='(') 
	                	{
	                		cout<<"Malformed expression"; return 0;
	                	}
	                }	
	            }
	            else if(p=='-') 
	            {
	                if(prevchar=='-') 
	                {
	                    operators.pop();
	                    p='+';
	                }
	                else if(prevchar!=')') p='u';
	            }
	            else if(prevchar!=')')
	            {
	            	if(currchar=='*'||currchar=='/'||currchar=='%'|| currchar=='+' )
	            	{
	            		cout<<"Malformed expression"; 
	            		return 0;
	            	}
	            }
	        }
	        if(operators.empty()) 
	        {
	        	if(p=='(') leftBCount++;
	        	if(p==')') rightBCount++;
	        	operators.push(p);
	        }
	        else if( !operators.empty() && preference(p)>preference(operators.top()) )
		    {
		        operators.push(p);
		    }
	        else if(p=='(') {operators.push('('); leftBCount++;} 
		    else if (p==')') 
	        {
	        	rightBCount++; 
	        	if(rightBCount>leftBCount) 
	        		{
	        			cout<<"Malformed expression"; 
	        			return 0;
	        		}
	            while(operators.top()!='(')
	            {
	                if(operators.top()!='u')
	                {float a=operands.top();
	                operands.pop();
	                float b=operands.top();
	                operands.pop();
	                
	                float ans = solve(a, b, operators.top());
	                operands.push(ans);

	                }
	                else {float a = operands.top(); operands.pop(); operands.push(-1.0*a);}
	                operators.pop();
	            }
	            if(operators.top()=='(') operators.pop();
	        }
 
	        else if((p=='+'||p=='-'||p=='*'||p=='/'||p=='u'||p=='%') && !operators.empty())  
	        {
		        while(!operators.empty() &&  preference(p)<=preference(operators.top()) && operators.top()!='(')
		        {
                    if(operators.top()!='u')
		            {
		                float a=operands.top();           operands.pop();
	                    float b=operands.top();           operands.pop();

	                    float ans =solve(a, b , operators.top());         operands.push(ans);
	                    
		            }
		            else 
		            {  
		                float a = operands.top(); 
		                operands.pop(); 
		                operands.push(-1.0*a);
		            }
	                operators.pop();
		        }
		        operators.push(p);
	        }
	    }
    }
    if(rightBCount!=leftBCount) {cout<<"Malformed expression"; return 0;}
    while(!operators.empty())
    {

        if(operators.top()!='u')
        {
        	float a=operands.top();     operands.pop();
         	float b=operands.top();      operands.pop();
         	float ans = solve (a, b , operators.top());      operands.push(ans);
        }
        else {
        	float a = operands.top(); 
        	operands.pop(); 
        	operands.push(-1.00*a);
        }
        operators.pop();
    }
    cout<<fixed<<setprecision(6)<<operands.top();
	return 0;
}