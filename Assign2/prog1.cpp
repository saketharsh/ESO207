#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <cctype>
using namespace std;
 
bool error;  // To enocounter if there is an error or not 
 
// returns true if op2 has lower or equal priority than op1, false otherwise
bool hasLowerPriority(char op1, char op2)   {
    switch (op1) {
        case '(': return false;
        case '-': return op2 == '-';
        case '+': return op2 == '-' || op2 == '+';
        case '*': return op2 != '/';
        case '/': return true;
        default : error = true; return false;
    }
}
 
stack < char > operators;
stack < float > operands;
 
// perform the operation 'op' on the two operands on top of the stack
void operation(char op) {
    if(operands.size() < 2) {
        error = true; return;
    }
    int op2 = operands.top(); operands.pop();
    int op1 = operands.top(); operands.pop();
    switch(op)  {
        case '+': operands.push(op1 + op2); break;
        case '-': operands.push(op1 - op2); break;
        case '*': operands.push(op1 * op2); break;
        case '/': operands.push(op1 / op2); break;
        default : error = true; return;
    }
}
 
int main()  {
    char exp[1000], *p;
    int len;
    cin>>len;
    char  str[50]= {' '} ;
    str[0]= '(';
    for ( int i =1;i<=len ; i++)
        cin>>str[i];
    str[len+1]= ')';  

    // Code will begin from here    
    error = false;
    int i =0;
    while(i<len+2 && !error)    {
        if(isdigit(str[i]))
            operands.push(atoi((str+i)));
        else switch(str[i])    {
            case '(' :  operators.push('(');
                         break;
                        while (!operators.empty() && !error && operators.top() != '(') {
			             operation(operators.top()); operators.pop();
		                  }
		                if (!operators.empty())
            			operators.pop();
            		    else
            			error = true;
		                break;
            default  :  while(!operators.empty() && !error && hasLowerPriority(operators.top(), str[i])) {
                            operation(operators.top()); operators.pop();
                        }
                        operators.push(str[i]);
        }
        i++;
    }
    if(error || !operators.empty() || operands.size() != 1) {
        printf("Malformed expression\n");
        
    } else    {
        printf("%f\n", operands.top()); operands.pop();
    }    
    return 0;
}