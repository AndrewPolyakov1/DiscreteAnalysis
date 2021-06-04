#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <sstream>
#include <cctype>
#include "bm_search.hpp"

bool isSpace(char c)
{
	return ((c == ' ') || (c == '\t') || (c == '\n'));
}

void ToLower(std::string &str)
{
    for (int i = 0; i < (int)str.size(); ++i)
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 'a' - 'A';
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::vector<std::string> text;
	std::vector<std::string> pattern;
	std::string input, word;

	std::vector<std::pair<int, int>> PosArr;
	std::pair<int, int> tmp;


	// reading pattern
    std::string curLine;
    getline(std::cin, curLine, '\n');
    // splitting pattern-line into words
    std::istringstream stringStream(curLine);
    std::string curWord;
    while (stringStream >> curWord) {
        ToLower(curWord);
        pattern.push_back(curWord);
    }
    // reading, parsing text into words
    int nline = 1;
    int nword = 0;
    int lineLen;
    int wordleft;
    std::pair<int, int> lineNumWordNum;
    while (getline(std::cin, curLine, '\n')) {
        nword = 1;
        lineLen = curLine.size();
        for (int curPos = 0; curPos < lineLen;) {
            if (isalpha(curLine[curPos])) {
                wordleft = curPos;
                while (isalpha(curLine[curPos]) && curPos < lineLen)
                    ++curPos;

                lineNumWordNum.first = nline;
                lineNumWordNum.second = nword++;
                PosArr.push_back(lineNumWordNum);

                curWord = curLine.substr(wordleft, curPos - wordleft);
                ToLower(curWord);
                text.push_back(curWord);
            }
            ++curPos;
        }
        ++nline;
    }

	std::vector<int> Pos = Search(pattern, text);

	for (const auto &oc : Pos)
		std::cout << PosArr[oc].first << ", " << PosArr[oc].second << '\n';
	return 0;
}
