#include <bits/stdc++.h>
#include <cmath>

using namespace std;

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

float solve(float op1, float op2, char ch)  // Solve Function 
{
	switch(ch)
	{
		case '+': return (op1+op2);
		case '-': return (op1-op2);
		case '*': return (op1*op2);
		case '/': return (op1/op2);
		case '%': return (fmod(op1,op2));
	}
}

int preference( char ch)   {        // Preference Order of different operators 
	switch(ch) {
		case '+': return 1;
		case '-': return 1;
		case '*': return 2;
		case '/': return 3;
		case '%': return 3;
		case '(': return -1;
	}
}

float flag =1.0;
bool error = false ; // Assumed expression is true initially


void checkMalformed ( vector < string> s) {
	int opbrace=0;
	int closebrac=0;
	for ( int i=0; i <s.size()-1; i ++) {
		if (isChar(s[i]) && isChar([i-1])) {
			
		}
	}
	
}



// Main evaluator function 
void evaluate(vector <string >  s)
{
	int len = s.size();

	stack< char > operators;
	stack< float > operandssss;

	int i =0;
	while(i < len && !error )
	{
		if(isChar(s[i]))
		{
			if (isChar(s[i+1])) {
				checkMalformed(s[i][0], s[i+1][0]);
				if (error) {
					cout<<"E5";
					break;
				}
			}
			
			// I need to write here classic case to handle negative elements  and mal-formed expressions 

			if(s[i][0]=='(') operators.push('(');
			else if(s[i][0]==')')
			{
				while(operators.top()!='(' && !error)
				{
					if (operandssss.size()<2 ) {
						cout<<"E4";
						error =1 ;
						break;
					}
					char ch=operators.top(); operators.pop();
					float op2=operandssss.top(); operandssss.pop();
					float op1=operandssss.top(); operandssss.pop();
					operandssss.push(solve(op1,op2,ch));
				}
				operators.pop(); // To pop out opening braces 
			}
			else
			{
				if ( s[i][0]== '-' && isChar(s[i-1] ) )	 {  // Not to insert minus sign when it is with the number 
					i=i+1;
					continue;
				}			
				while(!operators.empty() &&   preference(s[i][0]) <= preference(operators.top())  && !error)
				{
					if (operandssss.size()<2 ) {
						cout<<"E3";
						error =1 ;
						break;
					}
					char ch=operators.top(); operators.pop();
					float op2=operandssss.top(); operandssss.pop();
					float op1=operandssss.top(); operandssss.pop();

					operandssss.push(solve(op1,op2,ch));
				}

				operators.push(s[i][0]);
			}
		}
		else
		{
			if (i >=1 && !isChar(s[i-1])) {
				
				cout<<"E2";
				error =1;
				break;
			}
			float op=stoi(s[i]);
			operandssss.push(flag*op*1.00);
			flag =1.0;
		}
			i++;
	}


	while(!operators.empty() && !error )
	{
		if (operandssss.size()<2) 
		{
			cout<<"E1";
			error =1 ;
			continue;
		}
		char ch=operators.top(); operators.pop();
		float op2=operandssss.top(); operandssss.pop();
		float op1=operandssss.top(); operandssss.pop();
		operandssss.push((float)solve(op1,op2,ch));
	}
	if (error) {
		cout<<"Malformed expression";
	}
	else {
		cout<<operandssss.top();
	}
}

int main() {
	int len ;
	cin>>len;
	vector <string> s(len);	
	for ( int i =0;i<len ; i ++) {
		cin>>s[i];	
	}
	checkMalformed(s);
	evaluate(s);
	return 0;
}