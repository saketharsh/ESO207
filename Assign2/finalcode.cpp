#include <iostream>
using namespace std;
#include <stack>
#include <iomanip>
int pri(char a)
{
    switch(a)
    {
        case '+': return 1; break;
        case '-': return 1; break;
        case '*': return 3; break;
        case '/': return 4; break;
        case '%': return 4; break;
        case 'u': return 5;break;
        default : return 0;// '(' or ')'
    }
}

int main() {
    int t;
    cin>>t;
    //string s[t];
    stack <float> operand;
    stack <char> oprator; 
    char p; int lcount=0, rcount =0; int currintindex=-10, j=0, previndex, currcharindex=-20, prevcharindex;
    char prevchar, currchar='$';
    for(int i=0; i<t ; i++)
    {
    	string d;
	    cin>>d;
	    if(d[0]>='0'&&d[0]<='9') //integer, so operand.
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
	        operand.push(num); 
	        //operand input taken.
	    }
	    else //character, not integer
	    {
	        p=d[0];//input of operand done, now p contains
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
	        else if( !oprator.empty()&&pri(p)>pri(oprator.top()) )
		    {
		        oprator.push(p);
		    }
	        else if(p=='(') {oprator.push('('); lcount++;} 
		    else if (p==')') 
	        {rcount++; if(rcount>lcount) {cout<<"Malformed expression"; return 0;}
	            while(oprator.top()!='(')
	            {
	                if(oprator.top()!='u')
	                {float a=operand.top();
	                operand.pop();
	                float b=operand.top();
	                operand.pop();
	                switch(oprator.top())
	                {
	                    case '+': operand.push(a+b); break;
	                    case '-': operand.push(b-a); break;
	                    case '*': operand.push(a*b); break;
	                    case '/': operand.push(b/a); break;
	                    case '%': operand.push((int)b%(int)a); break;
	                    default: break;
	                }
	                }
	                else {float a = operand.top(); operand.pop(); operand.push(-1.0*a);}
	                oprator.pop();
	            }
	            if(oprator.top()=='(') oprator.pop();
	        }
	        
	        else if((p=='+'||p=='-'||p=='*'||p=='/'||p=='u'||p=='%') && !oprator.empty())  
	        {
		        while(!oprator.empty() && pri(p)<=pri(oprator.top()) && oprator.top()!='(')
		        {
                    if(oprator.top()!='u')
		            {
		                float a=operand.top();
		                operand.pop();
	                    float b=operand.top();
	                    operand.pop();
	                    switch(oprator.top())
	                    {//the operator on the top of the stack is evaluated using
                        //the operands on the top of the operand stack and the result is pushed back on to the operand stack.
	                        case '+': operand.push(a+b); break;
	                        case '-': operand.push(b-a); break;
	                        case '*': operand.push(a*b); break;
	                        case '/': operand.push(b/a); break;
	                        case '%': operand.push((int)b%(int)a); break;
	                        default: break;
	                    }//This process is repeated until either (a) the current operator is higher in precedence than the one
                        //on the top of the operator stack, or, (b) the operator stack has '(' on its top, or 
                        //(c) the operator stack is empty.
		            }
		            else 
		            {  
		                float a = operand.top(); 
		                operand.pop(); 
		                operand.push(-1.0*a);
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
        float a=operand.top();
        operand.pop();
         float b=operand.top();
         operand.pop();
         switch(oprator.top())
	      {
	        case '+': operand.push(a+b); break;
            case '-': operand.push(b-a); break;
            case '*': operand.push(a*b); break;
            case '/': operand.push(b/a); break;
            case '%': operand.push((int)b%(int)a); break;
            default: break;
          }  
        }
        else {float a = operand.top(); operand.pop(); operand.push(-a);}
        oprator.pop();
    }
    cout<<fixed<<setprecision(6)<<operand.top();
	return 0;
}