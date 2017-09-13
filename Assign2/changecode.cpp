#include <iostream>
using namespace std;
#include <stack>
#include <iomanip>
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
    int t;
    cin>>t;
    stack <float> operands;
    stack <char> oprator; 
    char p; int lcount=0, rcount =0; int currintindex=-10, j=0, previndex, currcharindex=-20, prevcharindex;
    char prevchar, currchar='$';
    for(int i=0; i<t ; i++)
    {
    	string d;
	    cin>>d;
	    if(d[0]>='0'&&d[0]<='9') //integer, so operands.
	    {
	        previndex = currintindex; currintindex=i; 
	        if(previndex==currintindex-1) {cout<<"Malformed expression"; return 0;}
	        int l=d.length(), j=0, num=0;
	        while(j<l)
	        {
	            num = num*10;
	            num=num + d[j]-48;
	            j++;
	        }
	        operands.push(num); 
	        //operands input taken.
	    }
	    else //character, not integer
	    {
	        p=d[0];//input of operands done, now p contains
	                     //symbol only
	        prevcharindex = currcharindex; currcharindex=i; 
	        prevchar=currchar; currchar=p;
	        if(prevchar=='$'&&p=='-') p='u';
	        //cout<<prevcharindex<<" "<<currcharindex<<endl;
	        if(prevcharindex==currcharindex-1) 
	        {//cout<<"inside this shit";
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
	                    oprator.pop();p='+';
	                }
	                else if(prevchar!=')') p='u';
	                //else if(prevchar=='+') {cout<<"Malformed expression"; return 0;}
	            }
	            else if(prevchar!=')')
	            {
	            	if(currchar=='*'||currchar=='/'||currchar=='%'||currchar=='+')
	            	{cout<<"Malformed expression"; return 0;}
	            }
	        }
	        if(oprator.empty()) 
	        {
	        	if(p=='(') lcount++;
	        	if(p==')') rcount++;
	        	oprator.push(p);
	        }
	        else if( !oprator.empty()&&preference(p)>preference(oprator.top()) )
		    {
		        oprator.push(p);
		    }
	        else if(p=='(') {oprator.push('('); lcount++;} 
		    else if (p==')') 
	        {rcount++; if(rcount>lcount) {cout<<"Malformed expression"; return 0;}
	            while(oprator.top()!='(')
	            {
	                if(oprator.top()!='u')
	                {float a=operands.top();
	                operands.pop();
	                float b=operands.top();
	                operands.pop();
	                switch(oprator.top())
	                {
	                    case '+': operands.push(a+b); break;
	                    case '-': operands.push(b-a); break;
	                    case '*': operands.push(a*b); break;
	                    case '/': operands.push(b/a); break;
	                    case '%': operands.push((int)b%(int)a); break;
	                    default: break;
	                }
	                }
	                else {float a = operands.top(); operands.pop(); operands.push(-1.0*a);}
	                oprator.pop();
	            }
	            if(oprator.top()=='(') oprator.pop();
	        }
	        
	        else if((p=='+'||p=='-'||p=='*'||p=='/'||p=='u'||p=='%') && !oprator.empty())  
	        {
		        while(!oprator.empty() && preference(p)<=preference(oprator.top()) && oprator.top()!='(')
		        {
                    if(oprator.top()!='u')
		            {
		                float a=operands.top();
		                operands.pop();
	                    float b=operands.top();
	                    operands.pop();
	                    switch(oprator.top())
	                    {//the operator on the top of the stack is evaluated using
                        //the operandss on the top of the operands stack and the result is pushed back on to the operands stack.
	                        case '+': operands.push(a+b); break;
	                        case '-': operands.push(b-a); break;
	                        case '*': operands.push(a*b); break;
	                        case '/': operands.push(b/a); break;
	                        case '%': operands.push((int)b%(int)a); break;
	                        default: break;
	                    }//This process is repeated until either (a) the current operator is higher in precedence than the one
                        //on the top of the operator stack, or, (b) the operator stack has '(' on its top, or 
                        //(c) the operator stack is empty.
		            }
		            else 
		            {  
		                float a = operands.top(); 
		                operands.pop(); 
		                operands.push(-1.0*a);
		            }
	                oprator.pop();
		        }
		        //if(oprator.top()=='(') oprator.pop();
		        oprator.push(p);
	        }
	    }
    }
    if(rcount!=lcount) {cout<<"Malformed expression"; return 0;}
    while(!oprator.empty())
    {//cout<<" "<< "step" <<" ";
    //cout<<endl<<oprator.top();
        if(oprator.top()!='u')
        {//cout<<"oout";
        float a=operands.top();
        operands.pop();
         float b=operands.top();
         operands.pop();
         switch(oprator.top())
	      {
	        case '+': operands.push(a+b); break;
            case '-': operands.push(b-a); break;
            case '*': operands.push(a*b); break;
            case '/': operands.push(b/a); break;
            case '%': operands.push((int)b%(int)a); break;
            default: break;
          }  
        }
        else {float a = operands.top(); operands.pop(); operands.push(-a);}
        oprator.pop();
    }
    cout<<fixed<<setprecision(6)<<operands.top();
	return 0;
}