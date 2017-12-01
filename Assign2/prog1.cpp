#include <bits/stdc++.h>
#include <cmath>
#include <iomanip>
 
 
using namespace std;
 
 
int preference(char a)
{
    switch(a)
    {
        case '+': return 1; break;
        case '-': return 1; break;
        case '*': return 3; break;
        case '/': return 4; break;
        case '%': return 4; break;
        case 'h': return 5;break;
        default : return 0;
    }
}
 
int  isChar(string s)
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
 
 
float solve(float op1, float op2, char ch)  
{
	switch(ch)
	{
		case '+': return (op1+op2); break;
		case '-': return (op2-op1); break;
		case '*': return (op1*op2); break;
		case '/': return (op2/op1); break;
		case '%': return fmod(op2,op1); break;
		default: return 0;
	}
}
 
int evaluate();
 
int main() {
	evaluate();
    
	return 0;
}
 
 
int evaluate () {
 
	int len;
    cin>>len;
    stack <float> operands;
 
    stack <char> operators; 
 
    char p; int LeftCount=-1, rightCount =-1;
 
     int currintindex=-7, j=0;
 
     int previndex, currcharindex=-8, prevcharindex;
 
    char prevchar, currchar='$';
 
 
    for(int i=0; i<len ; i++)
    {
    	string d;
	    cin>>d; 
	    if(!isChar(d)) 
	    {
	        previndex = currintindex; currintindex=i; 
 
	        if(previndex == currintindex-1) {
	        	cout<<"Malformed expression"; return -1;
	        }
	        
	        float num = stoi(d);
	        
	        operands.push(num); 
	    }
 
	    else 
	    
	    {
	        p=d[0];
	    
	        prevcharindex = currcharindex; currcharindex=i; 
	    
	        prevchar=currchar; currchar=p;
	        if(prevchar=='$'&&p=='-') p='h';
	        if(prevcharindex==currcharindex-1) 
	        {
	            if(prevchar=='(')
	            {
	                if (currchar=='-') p='h';
	                else {
	                	if(currchar!='(') 
	                	{
	                		cout<<"Malformed expression"; return -1;
	                	}
	                }	
	            }
	            else if(p=='-') 
	            {
	                if(prevchar=='-') 
	                {
	                    operators.pop();p='+';
	                }
	                else if(prevchar!=')') p='h';
	            }
	            else if(prevchar!=')')
	            {
	            	if(currchar=='*'||currchar=='/'||currchar=='%'||currchar=='+')
	            	{cout<<"Malformed expression"; return 0;}
	            }
	        }
	        if(operators.empty()) 
	        {
	        	if(p=='(') LeftCount++;
	        	if(p==')') rightCount++;
	        	operators.push(p);
	        }
	        else if( !operators.empty()&&preference(p)>preference(operators.top()) )
		    {
		        operators.push(p);
		    }
	        else if(p=='(') {operators.push('('); LeftCount++;} 
		    else if (p==')') 
	        {rightCount++; if(rightCount>LeftCount) {cout<<"Malformed expression"; return -1;}
	            while(operators.top()!='(')
	            {
	                if(operators.top()!='h')
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
	            	operators.pop();
	        }
	        
	        else if( (p=='+'||p=='-'||p=='*'||p=='/'||p=='h'||p=='%')  &&  !operators.empty())  
	        {
		        while(!operators.empty() && preference(p)<=preference(operators.top()) && operators.top()!='(')
		        {
                    if(operators.top()!='h')
		            {
		                float a=operands.top();
		                operands.pop();
	                    float b=operands.top();
	                    operands.pop();
	                    float ans = solve(a, b, operators.top());
	                	operands.push(ans);
	                   
	                   
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
    if(rightCount!=LeftCount) 
    	{cout<<"Malformed expression"; return -1;
	}
	
    while(!operators.empty())
    {
        if(operators.top()!='h')
        {
        float a=operands.top();
        operands.pop();
         float b=operands.top();
         operands.pop();
         float ans = solve(a, b, operators.top());
	                operands.push(ans);
        }
        else {float a = operands.top(); operands.pop(); operands.push(-1.00*a);}
        operators.pop();
    }
    cout<<fixed<<setprecision(6)<<operands.top();
    return 0;
 
}