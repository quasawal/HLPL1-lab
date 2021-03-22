#include "std_lib_facilities.h"



struct Token {
	char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) { } 
	Token(char ch, double val) :kind(ch), value(val) { } 
	Token(char ch, string n) :kind(ch), name(n) { } // Name of variable
};



class Token_stream {
	bool full;
	Token buffer; 
public:
	Token_stream() :full(0), buffer(0) { }

	Token get();
	void unget(Token t) { buffer=t; full=true; }
	void ignore(char); 
};

const char let = 'L'; 
const char quit = 'E'; // Exit
const char print = ';'; // Print
const char number = '8'; // Indicates that this is a number
const char name = 'a'; // Indicates that this is a variable
const char sqrts = 's'; //  indicates square root
const char pows = 'p';

Token Token_stream::get() 
{
	if (full) { full=false; return buffer; } // if buffer is full return value
	char ch; 
	cin >> ch;
	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case '=':
	case '!':
	case ',':
		return Token(ch);
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{	
		cin.unget(); // If number then return it to the stream
		double val;
		cin >> val; 
		return Token(number,val);
	}
	default:
		if (isalpha(ch)) { // If letter
			string s;
			s += ch; // Put the letter in 's' because it has been already read
			while(cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s+=ch; 
			cin.unget(); // Return the character into the stream
			if (s == "let") return Token(let);	// If user declares the variable then return 'let'
			if (s == "sqrt") return Token(sqrts);
			if (s == "pow") return Token(pows);
			if (s == "exit") return Token(quit); // Close the program
			return Token(name,s); // Return name of variable
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c) // Ignores all characters before c
{
	if (full && c==buffer.kind) { // If 'c' is already in buffer then just discard it
		full = false;
		return;
	}
	full = false; 
	char ch;
	while (cin>>ch) 
		if (ch==c) return; 
}

struct Variable { // Holds variables names and values
	string name; // Variable name
	double value; // Variable value
	Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names;	// Holds all variables

double get_value(string s) // Gets variable's value
{
	for (Variable i: names) {
		if (i.name == s) return i.value;
	}
	error("get: undefined name ",s);
}

void set_value(string s, double d) // Sets variable's value
{
	for (int i = 0; i<=names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ",s);
}

bool is_declared(string s) // Checks whether variable is already declared
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

Token_stream ts; // Holds all Tokens

double expression(); 

double primary()
{
	Token t = ts.get(); // Get a character
	switch (t.kind) {
	case '(': 
	{	double d = expression(); // Perform calculations
		t = ts.get(); // Get a ')' closing character
		if (t.kind != ')') error("')' expected"); // If there wasn't any ')' return an error
		return d;
	}
	case sqrts: // Calculate square root of number
	{
		double d = primary();
		if (d < 0) error("square root of negative number was detected"); // Print error message if negative number was in sqrt
		return sqrt(d);
	}
	case pows:
	{
		t = ts.get();
		if (t.kind == '(') {
			double lval = primary();
			int rval = 0;
			t = ts.get();
			if(t.kind == ',') rval = narrow_cast<int>(primary());
			else error("Second argument is not provided");
			double result = 1;
			for(double i = 0; i < rval; i++) {
				result*=lval;
			}
			t = ts.get();
			if (t.kind != ')') error("')' expected"); // If there wasn't any ')' return an error
			return result;
		}
		else error("'(' expected"); // If there wasn't any ')' return an error
	}
	case '-': // For negative digits
		return - primary(); // Return negative digit
	case number: // If Token is a number
		return t.value; // Return the number
	case name: // If Token is a name of variable
		return get_value(t.name); // Return the value of the variable
	default:
		error("primary expected");
	}
}

double term() 
{
	double left = primary(); // Get the number or the variable
	while(true) {
		Token t = ts.get(); // Get a new character
		switch(t.kind) {
		case '*': // Multiplication
			left *= primary(); 
			break;
		case '/': // Division
		{	double d = primary(); 
			if (d == 0) error("division by zero"); // Division by zero is prohibited
			left /= d;
			break;
		}
        case '!': // Factorial
            {   
                int x = left;
                for (int i = 1; i < left; i++) { // Get a multiplication of all numbers before x (including x)
                    x*=i;
                }
                if (x == 0) left = 1;
                else left = x;
                break;
            }        
        case '%': // Modulo
            {
                double d = primary();
                if(d == 0) error("division by zero");
                left = fmod(left,d); 
                break;
            }
		default:
			ts.unget(t); 
			if (left == -0) return 0; 
			return left; 
		}

	}
}

double expression() // Performs '+' and '-' operations
{
	double left = term(); // Get the number or the result of calculations in term
	while(true) {
		Token t = ts.get();
		switch(t.kind) {
		case '+':
			left += term(); // Addition
			break;
		case '-':
			left -= term(); // Subtraction
			break;
		default:
			ts.unget(t); // If nothing was done return character to the stream
			return left; // Return the new or unchanged value of 'left'
		}
	}
}

double declaration() // Declares a name of the variable
{
	Token t = ts.get(); // Get a character from the stream
	if (t.kind != 'a') error ("name expected in declaration"); // If there is no name return an error
	string name = t.name; 
	if (is_declared(name)) error(name, " declared twice"); // Check if the variable had been already declared
	Token t2 = ts.get(); // Get a character from the stream
	if (t2.kind != '=') error("= missing in declaration of " ,name); 
																		
	double d = expression(); 
	names.push_back(Variable(name,d)); // Add new variable to a vector
	return d; // Return the value of new variable
}

double statement()  
{
	Token t = ts.get();
	switch(t.kind) {
	case let: 
		return declaration();
	default: 
		ts.unget(t);
		return expression();
	}
}

void clean_up_mess() 
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= "; 

void calculate()
{
	while(true) try {
		cout << prompt; 
		Token t = ts.get(); 
		while (t.kind == print) t=ts.get(); // Read all ';'
		if (t.kind == quit) return; // Close the program if exit was entered
		ts.unget(t); // Return a character into the stream
		cout << result << statement() << endl; // Output the result
	}
	catch(runtime_error& e) {
		cerr << e.what() << endl; // Cout the error if the exception was thrown
		clean_up_mess(); // Ignores all characters till the ';'
	}
}

int main()
	try {
		names.push_back(Variable("k",1000)); // Pre-defined variable 'k'

		calculate(); // Performs calculations
		return 0;
	}
	catch (exception& e) { // Throws an exception
		cerr << "exception: " << e.what() << endl; 
		char c;
		while (cin >>c&& c!=';');
		return 1;
	}
	catch (...) { // Throws an exception
		cerr << "exception\n";
		char c;
		while (cin>>c && c!=';');
		return 2;
	}
