#include <algorithm>
#include <iostream>
#include <sstream>
#include "tokenlizor.h"

using namespace std;

Tokenlizor::Tokenlizor(const vector<string>& patterns)
    :patterns(patterns)
{
    re = make_shared<regex>(join(cbegin(patterns), cend(patterns), "|"));
    std::transform(cbegin(patterns), cend(patterns), back_inserter(rePatterns), [](const string& s) {return regex{ s }; });
}
vector<Tokenlizor::Token> Tokenlizor::parse(const string& s) const
{
    vector<string> tokens{ sregex_token_iterator(cbegin(s), cend(s), *re, 0), sregex_token_iterator() };
    vector<Token> results;
    for (const string& token : tokens)
    {
        for (int i = 0; i < rePatterns.size(); i++)
        {
            if (regex_match(token, rePatterns[i]))
            {
                results.emplace_back(token, i);
            }
        }
    }
    return results;
}

template <typename InputIt>
std::string join(InputIt begin, InputIt end, const std::string& separator)
{
    std::ostringstream ss;
    if (begin != end)
    {
        ss << *begin++;
    }
    while (begin != end)
    {
        ss << separator;
        ss << *begin++;
    }
    return ss.str();
}