#include<iostream>
#include "tokenlizor.h"
#include "calc.h"
#include<stack>
using namespace std;
using Token = Tokenlizor::Token;

Calculator::Calculator()
    :tkn{ vector<string>{ "(\\d+(\\.\\d+)?)", "\\+", "\\-", "\\*", "/", "\\(", "\\)" } }
{

}

vector<Token> Calculator::parse(const string& exp)
{
    vector<Token> const tokens = tkn.parse(exp);
    vector<Token> out;
    stack<Token> stk;
    for (auto const& t : tokens)
    {
        auto [str, i] = t;
        switch (i)
        {
        case 0: //literal
            out.emplace_back(t);
            break;
        case 1://+
        case 2://-
            while (!stk.empty() && stk.top().second != 5)
            {
                out.emplace_back(stk.top());
                stk.pop();
            }
            stk.push(t);
            break;
        case 3:// *
        case 4:// /
            while (!stk.empty() && stk.top().second != 5 && stk.top().second != 1 && stk.top().second != 2)
            {
                out.emplace_back(stk.top());
                stk.pop();
            }
            stk.push(t);
            break;
        case 5://(
            stk.push(t);
            break;
        case 6:
            while (!stk.empty() && stk.top().second != 5)
            {
                out.emplace_back(stk.top());
                stk.pop();
            }
            if (!stk.empty() && stk.top().second == 5)
            {
                stk.pop();
            }
            if (stk.empty())
                throw runtime_error("Malformed expression");
            break;

        }
    }
    while (!stk.empty()) 
    {
        out.emplace_back(stk.top());
        stk.pop();
    }
    return out;
}

double Calculator::calc(const string& exp)
{
    vector<Token> tokens = parse(exp);
    stack<double> stk;
    double d;
    for (auto &t : tokens) 
    {
        auto [str, i] = t;
        switch (i)
        {
        case 0:
            stk.push(stod(str));
            break;
        case 1:
            d = stk.top();
            stk.pop();
            stk.top() += d;
            break;
        case 2:
            d = stk.top();
            stk.pop();
            stk.top() -= d;
            break;
        case 3:
            d = stk.top();
            stk.pop();
            stk.top() *= d;
            break;
        case 4:
            d = stk.top();
            stk.pop();
            stk.top() /= d;
            break;

        }
    }
    return stk.top();
}

int main(int argc ,char* argv[])
{
    Calculator cal;
    string exp = "1+11.0/(2.22-9) ";
    vector<Token> tokens = cal.parse(exp);
    cout << exp << endl;
    for(auto const &[token, label] : tokens) {
        cout << token << " ";
    }
    cout << endl;
    cout << cal.calc(exp);
	//std::cout << "hello" << std::endl;
	return 0;
}