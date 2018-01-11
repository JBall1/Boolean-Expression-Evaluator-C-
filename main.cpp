/*
By Joshua Ball

*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
using namespace std;

//given structs
typedef struct AST *pNODE;
struct AST { string info; pNODE children[2]; };
struct tokRslt { bool success; vector<string> syms; };
struct parseRslt { bool success; AST ast; };
struct TPERslt { bool val; string msg; };

//tests, giving random stirngs both correct and not.
//void testFunction();

//Given functions
tokRslt tokenize(string s);
parseRslt parse(vector<string> V);
bool eval(AST T);
string TPEOut(string s);

//helper functions for parse
pNODE Expression(vector<string> V, int i, int j);
pNODE Implcation(vector<string> V, int i, int j);
pNODE Disjunction(vector<string> V, int i, int j);
pNODE Conjunction(vector<string> V, int i, int j);
pNODE Negation(vector<string> V, int i, int j);
pNODE Constant(vector<string> V, int i, int j);
pNODE Unbreakable(vector<string> V, int i, int j);

/*
PrinTree and cons
*/

//Prints Tree
void prinTree(AST T) {
	// If both children are NULL, just print the symbol
	if (T.children[0] == NULL) {
		cout << T.info;
		return;
	}
	cout << "(" << T.info << " ";
	prinTree(*(T.children[0]));
	cout << " ";

	if (T.children[1] != NULL)
		prinTree(*(T.children[1]));
	cout << ")";
}

pNODE cons(string s, pNODE c1, pNODE c2) {
	pNODE ret = new AST;
	ret->info = s;  // same as (*ret).info = s
	ret->children[0] = c1;
	ret->children[1] = c2;
	return ret;
}

//TODO: DONE!
tokRslt tokenize(string s) {
	
	tokRslt lex;
	lex.success = false;
	string n;
	for (int i = 0; s[i] != '\0'; i++) {
		if ((s[i] == 'T' || s[i] == 'F' || s[i] == '=' || s[i] == 'v' || s[i] == '<' || s[i] == '>' || s[i] == '^' || s[i] == '<=>' || s[i] == '=>' || s[i] == '~' || s[i] == '(' || s[i] == ')' || s[i] == ' ')) {

			n = "";
			n = n + s[i];
			if (s[i] == '=') {
				//checking next element
				if (s[i + 1] == '>') {
					i++;
					lex.syms.push_back("=>");
					lex.success = true;
				}
				else {
					lex.syms.push_back(n);
					lex.success = false;
					break;
				}
			}
			else if (s[i] == '<') {
				if (s[i + 1] == '='){
					
					if (s[i + 2] == '>') {
						
						i = i + 2;
						lex.syms.push_back("<=>");
						lex.success = true;
					}
				}
				else if (s[i] == 'T') {
					lex.syms.push_back("T");
					lex.success = true;
					i++;
				}
				else if (s[i] == 'F') {
					lex.syms.push_back("F");
					lex.success = true;
					i++;
				}
			}
			//For everything else
			else {
				if (s[i] != ' ') {
					lex.success = true;
					lex.syms.push_back(n);
				}
			}
		}
		else {
			lex.success = false;
			return lex;
		}
	}
	
	//passing vector to parse function
	/*
	for (size_t i = 0; i < lex.syms.size(); i++) {
		cout << lex.syms[i];
		
	}
	cout << endl;
	*/

	return lex;
}


//TODO: DONE
parseRslt parse(vector<string> V) {

	parseRslt rslt;
	if (V.size() == 1) {
		if (V[0] == " " || V[0] == "")
			rslt.success = false;
	}
	int i = 0;//start of V
	int j = V.size();//size of V
	pNODE A = Expression(V, i, j);
	
	rslt.success = (A != NULL);

	if (rslt.success == true) {
		rslt.ast = *A;
		return rslt;
	}
	else
		rslt.success = false;

	//prinTree(rslt.ast);
	//cout << endl;
	return rslt;
	
}

//The following are Parse helper functions:
//Checks for the following parameneters: if it is a bool expression
pNODE Expression(vector<string> V, int i, int j) {
	for (int c = i; c<j; c++) {
		if (V[c] == "<=>") {
			pNODE t1 = Implcation(V, i, c);
			pNODE t2 = Expression(V, c + 1, j);
			if (t1 != NULL && t2 != NULL)
				return cons("<=>", t1, t2);
		}
	}
	pNODE W = Implcation(V, i, j);
	if (W != NULL) {
		return W;
	}
	return NULL;
}
//Checks for the following parameneters: T,F
pNODE Constant(vector<string> V, int i, int j) {
	if (i != j-1 || i >= V.size()) {
		return NULL;
	}
	if (V[i] == "T" || V[i] == "F") {
			return cons(V[i], NULL, NULL);
		}
	return NULL;
}
//Checks for the following parameneters: ~
pNODE Negation(vector<string> V, int i, int j) {

	for (int c = i ; c<j; c++) {
		if (V[c] == "~") {
		
		//	pNODE t1 = Expression(V, i ,c);
			pNODE t2 = Negation(V, i+1, j);
			if (t2 != NULL) {
				
				return cons("~", t2,NULL);
			}
		}
	}
	pNODE test = Unbreakable(V, i, j);
	if (test != NULL) {
		return test;
	}
	// All attempts failed
	return NULL;
}
//Checks for the following parameneters: ^(AND)
pNODE Conjunction(vector<string> V, int i, int j) {
	
	for (int c = i; c<j; c++) {
		if (V[c] == "^") {
			pNODE t1 = Conjunction(V, i, c);
			pNODE t2 = Negation(V, c + 1, j);
			if (t1 != NULL && t2 != NULL)
				return cons("^", t1, t2);
		}
	}

	pNODE A = Negation(V, i, j);
	if (A != NULL) {

		return A;
	}
	return NULL;
}
//Checks for the following parameneters: v(OR)
pNODE Disjunction(vector<string> V, int i, int j) {

	for (int c = i ; c<j; c++) {

		if (V[c] == "v") {
			pNODE t1 = Disjunction(V, i, c);
			pNODE t2 = Conjunction(V, c+1 , j);
			if (t1 != NULL && t2 != NULL)
				return cons("v", t1, t2);
		}
	}
	pNODE A = Conjunction(V, i, j);
	if (A != NULL) {
		return A;
	}
	return NULL;
}
//Checks for the following parameneters: =>(false and true is false otherwise is true)
pNODE Implcation(vector<string> V, int i, int j) {
	for (int c = i; c<j; c++) {
		
		if (V[c] == "=>") {
			pNODE t1 = Disjunction(V, i, c);
			pNODE t2 = Implcation(V, c + 1, j);
			if (t1 != NULL && t2 != NULL)
				return cons("=>", t1, t2);
		}
	}
	pNODE A = Disjunction(V, i, j);
	if (A != NULL) {
		return A;
	}
	return NULL;
}
pNODE Unbreakable(vector<string> V, int i, int j) {
	// U::=  "(" Expression ")"
	pNODE test = Constant(V, i, j);
	if (test != NULL) {

		return test;
	}

	else if (V[i] == "(" && V[j-1] == ")") {
		pNODE temp = Expression(V, i + 1, j-1);
		if (temp != NULL) {
			return temp;
		}
	}

	// All attempts failed
	return NULL;
}
//**************** End of Parse helper functions *************************

bool eval(AST T) {
	string op = T.info;
	bool temp;
	if (op == "~") {
		temp = eval(*T.children[0]);
		if (!temp) {
			
			return  1;
		}
		else
			
			return 0;
	}
	//F
	else if (op == "F") {
		return 0;
	}
	//T
	else if (op == "T") {
		return 1;
	}
	//OR
	else if (op == "v") {
		if (eval(*T.children[0]) || eval(*T.children[1])) {
			return 1;
		}
		else
			return 0;
	}
	//AND
	else if (op == "^") {
		if ((eval(*T.children[0]) && eval(*T.children[1]))) {
			return 1;
		}
		else
			return 0;
	}
	//false and true is false otherwise is true
	else if (op == "=>") {
		if (eval(*T.children[0]) && !eval(*T.children[1])) {
			return 0;
		}
		else
			return 1;
	}
	else if (op == "<=>") {
		if ((eval(*T.children[1]) == eval(*T.children[0]))) {
			
			return 1;
		}
		else
		
			return 0;
	}

	return NULL;
}

TPERslt TPE(string s) {
	
	TPERslt tpe;
	tokRslt tempToken;
	parseRslt tempParse;

	tempToken = tokenize(s);

	tempParse = parse(tempToken.syms);
	if (!tempToken.success) {
		tpe.msg = "symbol error";
		return tpe;
	}
	else if (!tempParse.success) {
		tpe.msg = "grammar error";
		return tpe;
	} 
	else if (tempParse.success && tempToken.success) {
		tpe.msg = "success";
		tpe.val = eval(tempParse.ast);
		return tpe;
	}
}

string TPEOut(string s) {
	string outputMsg;
	
	if (TPE(s).msg == "success") {
		if (TPE(s).val == true) {
			outputMsg = "true";
			return outputMsg;
		}
		else if (TPE(s).val == false) {
			outputMsg = "false";
			return outputMsg;
		}
	}
	else if (TPE(s).msg == "grammar error") {
		outputMsg = "grammar error";
		return outputMsg;
	}

	else if (TPE(s).msg == "symbol error") {
		outputMsg = "symbol error";
		return outputMsg;
	}
	
	return "FAILED";
}


