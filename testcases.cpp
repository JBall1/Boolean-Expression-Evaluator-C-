//TEST FUNCTIONS BELOW

string ASTtoString(AST T) //converts an AST to String
{
	string s;
	// If both children are NULL, just print the symbol
	if (T.children[0] == NULL) {
		s = s + T.info;
		return s;
	}

	// print an opening paren, followed by the symbol of T, followed
	// by a space, and then the first child.
	s = s + "(";
	s = s + T.info;
	s = s + " ";
	s += ASTtoString(*(T.children[0]));
	s = s + " ";

	// print the second child if there is one, and then a right paren.
	if (T.children[1] != NULL) {
		s += ASTtoString(*(T.children[1]));
	}
	s = s + ")";
	return s;
}

void checkTokenize()
{
tokRslt tk1, tk2;
string s1 = "=><=>";
//string s1 = "T F <=";
string s2 = "(T v F)";
vector<string> v1, v2;

tk1 = tokenize(s1);
tk2 = tokenize(s2);
if (tk1.success && tk2.success)
{
v1.push_back("=>"); //if the success value is true only then we initialize vectors v1,v2 with actual input symbols
v1.push_back("<=>");

v2.push_back("(");
v2.push_back("T");
v2.push_back("v");
v2.push_back("F");
v2.push_back(")");

if (tk1.syms == v1 && tk2.syms == v2)
cout << "\nTokenize ALL Test Cases passed";

else if (tk1.syms != v1)
{
cout << "\nTokenize Test case 1: " << s1 << " FAILED";
}

else if (tk2.syms != v2)
{
cout << "\nTokenize Test case 2: " << s2 << " FAILED";
}
else
{
cout << "\nTokenize ALL test cases FAILED";
}
}

else if (!tk1.success)
{
cout << "\nTokenize Test case 1: " << s1 << " FAILED";
}
else if (!tk2.success)
{
cout << "\nTokenize Test case 1: " << s1 << " FAILED";
}
else
{
cout << "\nTokenize ALL test cases FAILED";
}
}

void checkParse()
{
	vector<string> v1, v2;
	parseRslt pr1, pr2;

	string s1 = "T v F ^ F";
//	string s1 = "(~(T^(~(Fv~T))))";
	string s2 = "~F => T";
	v1.push_back("T"); //v1 = T v F ^ F
	v1.push_back("v");
	v1.push_back("F");
	v1.push_back("^");
	v1.push_back("F");
	
	v1.push_back("(");
	v1.push_back("~");
	v1.push_back("(");
	v1.push_back("T");
	v1.push_back("^");
	v1.push_back("(");
	v1.push_back("~");
	v1.push_back("(");
	v1.push_back("F");
	v1.push_back("v");
	v1.push_back("~");
	v1.push_back("T");
	v1.push_back(")");
	v1.push_back(")");
	v1.push_back(")");
	v1.push_back(")");
	
	



	v2.push_back("~"); //v2 = ~F ^ T
	v2.push_back("F"); //v2 = ~F ^ T
	v2.push_back("=>");
	v2.push_back("T");



	pr1 = parse(v1);
	pr2 = parse(v2);

	if (pr1.success && pr2.success)//pr1.success && pr2.success)
	{
		string AST_case1 = "(v T (^ F F))";  //AST for v1 = T v F ^ F
	//	string AST_case1 = "(~(^ T(~(v F(~T)))))";
		string AST_case2 = "(=> (~ F ) T)"; //AST for v2 = ~F ^ T
		string pr1_str, pr2_str;
		
		//Converting user AST tree to string for comparison
		pr1_str = ASTtoString(pr1.ast);
		pr2_str = ASTtoString(pr2.ast);

		if (pr1_str == AST_case1 && pr2_str == AST_case2)//pr1_str == AST_case1 && pr2_str == AST_case2)
		{
			cout << "\nParse ALL Test cases Passed";
		}

		else if (pr1_str != AST_case1)
		{
			cout << "\nParse Test case 1: " << s1 << " FAILED" << endl;
			cout << "should be: " << AST_case1 << endl;
			cout << "but it is : "; 
			prinTree(pr1.ast);
			cout << endl;
		}
		else if (pr2_str != AST_case2)
		{
			cout << "\nParse Test case 2: " << s2 << " FAILED";
		}
		else
		{
			cout << "\nParse ALL Test case FAILED";
		}
	}

	else if (!pr1.success)
	{
		cout << "\nParse Test case 1: " << s1 << " FAILED";
	}
	else if (!pr2.success)
	{
		cout << "\nParse Test case 2: " << s2 << " FAILED";
	}

	else
	{
		cout << "\n Parse ALL test cases FAILED";
	}

}

void checkEval()
{
bool ev1, ev2, ev3;
AST test1, test2, B, C, D, E, b, c, d, e;
AST test3 ,Q, W, Y, R, T;
string s1 = "T v F ^ F"; 
string s2 = "~ F ^ T";
string s3 = "T <=> F <=> F";
test1 = *cons("v", &B, &C);
B = *cons("^", &D, &E);
C = *cons("T", NULL, NULL);
D = *cons("F", NULL, NULL);
E = *cons("F", NULL, NULL);



//AST for ~ F ^ T
test2 = *cons("^", &b, &c);
b = *cons("~", &d, NULL);
c = *cons("T", NULL, NULL);
d = *cons("F", NULL, NULL);

test3 = *cons("<=>", &R, &Y);
R = *cons("<=>", &Q, &W);
Y = *cons("F", NULL, NULL);
W = *cons("F", NULL, NULL);
Q = *cons("T", NULL, NULL);

ev1 = eval(test1);
ev2 = eval(test2);
ev3 = eval(test3);
//cout << ev3;

	if (ev1 && ev2)
{
		cout << "\nEval ALL Test cases Passed" << endl;
}
	else if (!ev1)
{
		cout << "\nEval Test case 1: " << s1 << " FAILED";
}
	else if (!ev2)
{
		cout << "\nEval Test case 2: " << s2 << " FAILED";
}
	else
{
		cout << "\nEval ALL test cases FAILED" << endl;
}

if (ev3) {
	cout << "Passed test case 3" << endl;

}
else if (!ev3) {
	cout << endl;
	//prinTree(R);
	cout << "\nEval Test case 3: " << s3 << " FAILED";
}
}

void checkTPE()
{
	
TPERslt tpe1, tpe2;
tpe1 = TPE("T => ~F"); //Should evaluate to TRUE
tpe2 = TPE("T v F * F"); //Should print "symbol error"

if (tpe1.msg == "success" &&tpe2.msg == "symbol error")
{
	if (tpe1.val) //if AST evaluates to TRUE for test case 1-     T => ~F
		cout << "\nTPE ALL Test cases PASSED";
}
else if (!tpe1.val)
{
	cout << "\nTPE Test case 1: T => ~F " << " FAILED";
}
else if (tpe2.msg != "symbol error")
{
	cout << "\nTPE Test case 2:  T v F * F " << " FAILED";
	cout << endl << tpe2.msg;

}
else
{
	cout << "\nTPE ALL test cases FAILED";
}
}

void checkTPEOut()
{
string t1, t2;

string case1 = "~ (~ T v F)^ F"; //Should evalute to "false"
string case2 = "(T v F) v ~ F ^ F"; //Should evalute to "true"
//string case2 = " T <=> F %=> F";
t1 = TPEOut(case1);
//cout << "T1: " << t1 << endl;
t2 = TPEOut(case2);
//cout << "T2: " << t2 << endl;
if (t1 == "false" && t2 == "true")
{
cout << "\nTPEOut ALL Test cases PASSED";
}
else if (t1 != "false")
{
cout << "\nTPEOut Test case 1: " << case1 << " FAILED";
}
else if (t2 != "true")
{
cout << "\nTPEOut Test case 2: " << case2 << " FAILED";
}
else
{
cout << "\nTPE ALL test cases FAILED";
}
}

int main()
{
//checkTokenize();
//checkParse();
//checkEval();
checkTPE();
//checkTPEOut();
	


return 0;
}
