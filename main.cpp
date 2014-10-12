#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class PostfixNotation {
	string pn[128];
	int pointer;
	string rpn[128];
	int rpnPointer;
	string stack[100];
	int stackPointer;
	//------------
	long double polishNotation[100];
	int pnPointer;
public:
	PostfixNotation(string ex);
	int getPriority(char p);
	void toArray(string ex);
	void toPostfixNotation();
	void ReversePolishNotation();
	long double action(char p, long double a, long double b);
};

void PostfixNotation::toArray(string ex){
	string bufNum = "", buf = ""; pointer = 0;
	bool isNum = false;

	for(int i = 0; i < ex.length(); i++){
		if((ex[i] == '-' && i == 0) || (ex[i] == '-' && i!= 0 && ex[i-1] == '('))
		{bufNum = bufNum + "-"; isNum = true;}
		else
		{
			
			
			if((ex[i] - '0' >= 0 && ex[i] - '0' <= 9) || ex[i] == '.') isNum = true; else isNum = false;
			
			if(isNum){ 
				bufNum = bufNum + ex[i];

				if(buf != ""){pn[pointer] = buf; buf = ""; ++pointer; }
			}
			else{

				if(i != 0){
				if(ex[i-1] == ')') {pn[pointer] = buf; buf = ""; ++pointer;}else
				if(ex[i] == '(') {pn[pointer] = buf; buf = ""; ++pointer;}
				}

				buf = buf + ex[i];
				
				//if(buf.length() == 1) { pn[pointer] = buf; buf = ""; ++pointer; }
				
				
				if(bufNum != "") { pn[pointer] = bufNum; bufNum = ""; ++pointer; }

				
			}
		}
	}
}

void PostfixNotation::toPostfixNotation(){
	stackPointer = -1;
	rpnPointer = 0;

	for(int i = 0; i < pointer; i++){
		if(pn[i][pn[i].length()-1] - '0' <= 9 && pn[i][pn[i].length()-1] - '0' >= 0)
		{
			rpn[rpnPointer] = pn[i];
			++rpnPointer;
		}else{
			if(pn[i] == ")"){
				int op = -1;
						
						for(int j = 0; j <= stackPointer; j++){
							if(stack[j] == "("){
								op = j;
							}
						}
				
						for(int j = stackPointer; j >= op; j--){
							if(stack[j]!="("){
							rpn[rpnPointer] = stack[j];
							++rpnPointer;
							}
						}

						stackPointer = op-1;
						//stackPointer = op-1;

			}else{
			
			if(stackPointer == -1 || pn[i] == "(") {++stackPointer; stack[stackPointer] = pn[i]; }else{
				if(getPriority(pn[i][0]) > getPriority(stack[stackPointer][0]))
				{
					++stackPointer;
					stack[stackPointer] = pn[i];
				}else{
					if(getPriority(pn[i][0]) <= getPriority(stack[stackPointer][0])){
						int op = -1;
						
						for(int j = 0; j <= stackPointer; j++){
							if(stack[j] == "("){
								op = j + 1;
							}
						}

						if(op == -1){
							for(int j = stackPointer; j >= 0; j--){
							
								if(getPriority(stack[j][0]) >= getPriority(pn[i][0])){
									op = j;
									
								}else break;
							
							}
						}

						for(int j = stackPointer; j >= op; j--){
							if(stack[j] != "("){
							rpn[rpnPointer] = stack[j];
							++rpnPointer;
							}
						}

						stackPointer = op;
						stack[stackPointer] = pn[i];
					}
				}
			}

			}

		}
	}

	
	if(stackPointer >= 0){
		for(int i = stackPointer; i >= 0; i--){
			if(stack[i] != "("){
			rpn[rpnPointer] = stack[i];
			++rpnPointer;
			}
		}
	} 

	//for(int i = 0 ; i < rpnPointer; i++){
	//	cout << rpn[i] << " ";
	//}
}

PostfixNotation::PostfixNotation(string ex){
	toArray(ex);
	toPostfixNotation();
	ReversePolishNotation();
	if(pnPointer == 0){
		cout << fixed << polishNotation[0] << endl;
	}else cout << "Unspecified error!" << endl;

	//for(int i = 0; i < pointer; i++){
	//	cout << pn[i] << endl;
	//}
}

void PostfixNotation::ReversePolishNotation(){
	pnPointer = -1;
	
	for(int i = 0; i < rpnPointer; i++){
		if(rpn[i][rpn[i].length()-1] - '0' >= 0 && rpn[i][rpn[i].length()-1] - '0' <= 9){
			++pnPointer;
			polishNotation[pnPointer] = stod(rpn[i]); //atof(rpn[i].c_str());
		}else{
			if(pnPointer != 0){
				polishNotation[pnPointer-1] = action(rpn[i][0], polishNotation[pnPointer-1], polishNotation[pnPointer]);
				pnPointer = pnPointer-1;
			}
		}
	}
}

long double PostfixNotation::action(char p, long double a, long double b){
	switch(p){
	case '+': return a+b; break;
	case '-': return a-b; break;
	case '*': return a*b; break;
	case '/': return a/b; break;
	case '^': return pow(a, b); break;
	default: return -1; break;
	}
}

int PostfixNotation::getPriority(char p){
	switch(p){
	case '^': return 2; break;
	case '*': case '/': return 1; break;
	case '+': case '-':	return 0; break;
	default: return -1;
	}
}

bool checkError(string);

int main(){
	//system("COLOR 70");
	string expression;
	cin >> expression;

	//a = atof(p.c_str());
	//cout << a << endl;
	
	if(!checkError(expression)){
		
		PostfixNotation Postfixnotation(expression);

	}else cout << "ERROR!" << endl;

	
	
	system("PAUSE");
	return 0;
}

bool checkError(string ex){
	if(ex[ex.length()-1] != '=') return true;
	int brackets = 0, ch = 0, dotcount = 0;

	for(int i = 0; i < ex.length(); i++){
		
		if(ex[i] == '(') ++brackets;
		else if(ex[i] == ')') --brackets;
		
		if(i != 0 && ex[i] == '(' && ex[i-1] == ')') return true;
		else if(i != 0 && ex[i] == ')' && ex[i-1] == '(') return true;

		if(brackets < 0) return true;
		if(ch > 1) return true;
		if(ch == 1) dotcount = 0;

		if(!(ex[i] - '0' >= 0 && ex[i] - '0' <= 9)){
			switch(ex[i]){
				case '-': 
					if(i == 0 && !(ex[i+1] - '0' >= 0 && ex[i+1] - '0' <= 9))
						return true;
					
					if(i!= 0 && ex[i-1] == '(');
					else
					if(i != 0 && ex[i-1] != ')')
					++ch;

					break;

			case '+':  case '/': case '*':
			case '^':
				if((i != 0 && ex[i-1] == '(') || i == 0)
					return true;
				
				if(i != 0 && ex[i-1] != ')')
				++ch;  break; 
			
			case ')': 

				if(i != ex.length()-1 && ex[i+1] - '0' >= 0 && ex[i+1] - '0' <= 9) 
					return true;
				else if(i != 0 && ex[i-1] != ')')
					++ch;
			

				break;  
			case '=':
				if(i != ex.length()-1) return true; 
				else if(ex[i-1] == '+' || ex[i-1] == '-' || ex[i-1] == '*' || 
					ex[i-1] == '/' || ex[i-1] == '^') return true;
				break; 
			
			
			case '(': 
				if(i != 0 && (ex[i-1] - '0' >= 0 && ex[i-1] - '0' <= 9))
					return true;
				break;

				case '.': 

					if(ch == 0) ++dotcount;
					
					if(dotcount > 1) return true;

					if(!(i != 0 &&
							  i != ex.length()-1 && (ex[i+1] - '0' >= 0 && ex[i+1] - '0' <= 9) 
							  && (ex[i-1] - '0' >= 0 && ex[i-1] - '0' <= 9))) 
							  return true;

							  break;
			default:
				return true;
				break;
			}
		}else ch = 0;


	}

	if(brackets != 0) return true;
	return false;
}
