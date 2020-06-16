#include <string>
#include <stack>
#include "tokenlizor.h"
class Calculator
{
public:
	Calculator();
	double calc(const string& exp);
	vector<Tokenlizor::Token> parse(const string& exp);
private:
	Tokenlizor tkn;
};