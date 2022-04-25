#pragma once
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <exception>
#include <list>
#include <set>

class TSuffixNode {
public:
    int l, index;
    long long* r;
    std::map<char, TSuffixNode*> children;
    TSuffixNode* sLink = nullptr;
    std::set <int> number_string;
    TSuffixNode() = default;
    ~TSuffixNode() {};
    TSuffixNode(TSuffixNode* node, int l, long long* r, int index) : sLink(node),
                                                     l(l),
                                                     r(r),
                                                     index(index){}
};

struct LCS{ // longest common substring
    long long length;
    std::vector <TSuffixNode*> path_to_subs;
    TSuffixNode* ending;
    TSuffixNode* begining;
};

class TSuffixTree {
public:
    void DisplayTree();
    TSuffixTree( const std::string&, const std::string& );
    ~TSuffixTree();
private:
    void Build();
    void StartPhase(long long i);
    int EdgeLength(TSuffixNode *node);
    void CountIndex(TSuffixNode *node, std::vector<int> &vec);
    void Display(TSuffixNode *p);
    void FindNumMax(TSuffixNode * node,  long long walk);
    void FindLongestSubstrings(TSuffixNode * node, long long walk, std::vector <TSuffixNode *>& path_to_sub);
    void RecursiveDestroy(TSuffixNode *node);
    int distance(TSuffixNode* node);
    std::set<int> MarkUp(TSuffixNode* node);
private:
    TSuffixNode *root = new TSuffixNode(nullptr, -1, new long long(-1), -1);
    long long remainingSuffixCount = 0;
    std::string input, pattern1, pattern2;
    TSuffixNode* activeNode =nullptr;
    int activeEdge = -1;
    int activeLength = 0;
    long long end = -1;
    int num_max_substring;
    std::vector <LCS> answer;
    LCS ans;
};