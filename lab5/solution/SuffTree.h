#pragma once
#include <exception>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

class TNode {
   public:
    int left, index;
    long long* right;
    std::map<char, TNode*> children;
    TNode* suffixLink = nullptr;
    std::set<int> stringNumber;
    TNode() = default;
    ~TNode(){};
    TNode(TNode* node, int l, long long* r, int index) : suffixLink(node),
                                                         left(l),
                                                         right(r),
                                                         index(index) {}
};

struct CommonString {
    long long length;
    std::vector<TNode*> path_to_subs;
    TNode* ending;
    TNode* begining;
};

class TSuffixTree {
   public:
    void DisplayTree();
    TSuffixTree(const std::string&, const std::string&);
    ~TSuffixTree();

    void Init();
    void StartPhase(long long i);
    int EdgeLength(TNode* node);
    void CountIndex(TNode* node, std::vector<int>& vec);
    void Display(TNode* p);
    void MaxSubsringLength(TNode* node, long long walk);
    void FindLongestSubstrings(TNode* node, long long walk, std::vector<TNode*>& path_to_sub);
    void RecursiveDelete(TNode* node);
    int distance(TNode* node);
    std::set<int> MarkUp(TNode* node);

   private:
    TNode* root = new TNode(nullptr, -1, new long long(-1), -1);
    long long remainingSuffixCount = 0;
    std::string input, pattern1, pattern2;
    TNode* activeNode = nullptr;
    int currentEdge = -1;
    int currentEdgeLength = 0;
    long long end = -1;
    int numberMaxSubstring;
    std::vector<CommonString> answer;
    CommonString ans;
};