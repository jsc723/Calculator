#pragma once
#include <vector>
#include <string>
#include <regex>
#include <memory>
using namespace std;

template <typename InputIt>
std::string join(InputIt begin, InputIt end, const std::string& separator = ", ");

class Tokenlizor {
public:
    typedef pair<string, int> Token;
    Tokenlizor(const vector<string>& patterns);
    vector<Token> parse(const string& s) const;
private:
    vector<string> patterns;
    shared_ptr<regex> re;
    vector<regex> rePatterns;
};