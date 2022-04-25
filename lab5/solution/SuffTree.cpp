#include "SuffTree.h"

#include <utility>

TSuffixTree::TSuffixTree(const std::string& p1, const std::string& p2) {
    input = p1 + "^" + p2 + "_";
    pattern1 = p1;
    pattern2 = p2;
    Init();
}

void TSuffixTree::Init() {
    activeNode = root;
    for (size_t i = 0; i < input.length(); ++i)
	   StartPhase(i);
    MarkUp(root);
    ans.length = 0;
    numberMaxSubstring = 0;
    MaxSubsringLength(root, 0);
    std::vector<TNode*> path_to_sub;
    FindLongestSubstrings(root, 0, path_to_sub);
    std::list<std::string> answer_string;
    for (long long i = 0; i < (long long)answer.size(); ++i) {
	   std::string a_string;
	   for (long long j = 0; j < (long long)answer[i].path_to_subs.size(); ++j) {
		  std::string next_string(input.substr(answer[i].path_to_subs[j]->left, *(answer[i].path_to_subs[j]->right) - answer[i].path_to_subs[j]->left + 1));
		  a_string += next_string;
	   }
	   answer_string.push_back(a_string);
    }
    answer_string.sort();
    std::cout << numberMaxSubstring << '\n';
    for (auto i = answer_string.begin(); i != answer_string.end(); ++i) {
	   std::cout << *i << '\n';
    }
}

void TSuffixTree::StartPhase(long long i) { // Вставка в дерево
	//Перед началом каждой фазы создаём указатель на последнюю созданную внутреннюю ноду со значением null.
    TNode* lastCreatedInternalNode = nullptr;
	 //Увеличиваем глобальную переменную end на 1.
    end++;
	//Счётчик для создаваемых листов.
    remainingSuffixCount++;
	 //Если active length = 0, то смотрим на текущий символ корня.
    while (remainingSuffixCount > 0) {
		// ищем текущий символ в начале исходящих из activeNode дуг
	   if (currentEdgeLength == 0) {
		  currentEdge = i;
	   }

	   auto find = activeNode->children.find(input[currentEdge]);
		// не нашли подходящую дугу
	   if (find == activeNode->children.end()) {
		  activeNode->children.insert(std::make_pair(input[currentEdge],
		                                             new TNode(root, i, &end, i - remainingSuffixCount + 1)));

		  if (lastCreatedInternalNode != nullptr) {
			 lastCreatedInternalNode->suffixLink = activeNode;
			 lastCreatedInternalNode = nullptr;
		  }
	   } else {
		  TNode* next = find->second;
		  long long edge_length = distance(next);

		  if (currentEdgeLength >= edge_length) {
			 currentEdge += edge_length;
			 currentEdgeLength -= edge_length;
			 activeNode = next;
			 continue;
		  }

		  if (input[next->left + currentEdgeLength] == input[i]) {
			 if (lastCreatedInternalNode != nullptr && activeNode != root)
				lastCreatedInternalNode->suffixLink = activeNode;
			 currentEdgeLength++;
			 break;
		  }
		  TNode* split = new TNode(root, next->left, new long long(next->left + currentEdgeLength - 1), -1);
		  activeNode->children[input[currentEdge]] = split;
		  next->left += currentEdgeLength;
		  split->children.insert(std::make_pair(input[i], new TNode(root, i, &end, i - remainingSuffixCount + 1)));
		  split->children.insert(std::make_pair(input[next->left], next));
		  if (lastCreatedInternalNode != nullptr)
			 lastCreatedInternalNode->suffixLink = split;
		  lastCreatedInternalNode = split;
	   }

	   remainingSuffixCount--;

	   if (activeNode == root && currentEdgeLength > 0) {
		  currentEdgeLength--;
		  currentEdge++;
	   } else if (activeNode != root)
		  activeNode = activeNode->suffixLink;
    }
}

// Prints tree to the ostream (debug)
void TSuffixTree::Display(TNode* p) {
    static int level = 0;
    level++;
    if (p->left == -1)
	   std::cout << ">> <root>";
    else
	   for (int i = p->left; i <= *(p->right); ++i) {
		  std::cout << input[i];
	   }
    std::cout << p->stringNumber.size() << "  ";
    for (auto it = p->stringNumber.begin(); it != p->stringNumber.end(); ++it) {
	   std::cout << *it << ' ';
    }
    for (int i = '^'; i < (int)'z' + 1; ++i) {
	   auto next_child = p->children.find(i);
	   if (next_child != p->children.end()) {
		  std::cout << "\n";
		  for (int j = 0; j < level; j++)
			 std::cout << "   ";
		  std::cout << ">>";
		  Display(next_child->second);
	   }
    }
    level--;
}

void TSuffixTree::DisplayTree() {
    Display(root);
}

void TSuffixTree::MaxSubsringLength(TNode* node, long long walk) {
    if (node->stringNumber.size() == 2) {
	   if (node != root) {
		  walk += *(node->right) - node->left + 1;
		  if (walk > numberMaxSubstring) {
			 numberMaxSubstring = walk;
		  }
	   }
	   for (auto i = node->children.begin(); i != node->children.end(); ++i) {
		  MaxSubsringLength(i->second, walk);
	   }
    }
}

void TSuffixTree::FindLongestSubstrings(TNode* node, long long walk, std::vector<TNode*>& path_to_sub) {
    if (node->stringNumber.size() == 2) {
	   if (node != root) {
		  if (walk == 0) {
			 path_to_sub.clear();
		  }
		  path_to_sub.emplace_back(node);

		  walk += *(node->right) - node->left + 1;
		  if (walk == numberMaxSubstring) {
			 ans.path_to_subs = path_to_sub;
			 ans.length = walk;
			 answer.emplace_back(ans);
			 path_to_sub.pop_back();
			 return;
		  }
	   }
	   for (auto i = node->children.begin(); i != node->children.end(); ++i) {
		  FindLongestSubstrings(i->second, walk, path_to_sub);
	   }
	   if (path_to_sub.size()) {
		  path_to_sub.pop_back();
	   }
    }
}

TSuffixTree::~TSuffixTree() {
    RecursiveDelete(root);
}

void TSuffixTree::RecursiveDelete(TNode* node) {
    for (auto i = node->children.begin(); i != node->children.end(); ++i) {
	   RecursiveDelete(i->second);
    }
    if (node->right != &end) {
	   delete node->right;
    }
    delete node;
}

int TSuffixTree::distance(TNode* node) {
    return *node->right - node->left + 1;
}

std::set<int> TSuffixTree::MarkUp(TNode* node) {
    if (node != root) {
	   if (input[node->left] == '^')
		  node->stringNumber.insert(1);
	   else if (input[node->left] == '_')
		  node->stringNumber.insert(2);
	   else if (distance(node) > 0) {
		  int size = pattern2.size();
		  if (distance(node) - 2 > size) {
			 node->stringNumber.insert(1);
		  } else if (input[*node->right] == *(input.end() - 1)) {
			 node->stringNumber.insert(2);
		  }
	   }
    }
    for (auto it = node->children.begin(); it != node->children.end(); ++it) {
	   TNode* next = it->second;
	   std::set<int> ans = MarkUp(next);
	   for (auto itt = ans.begin(); itt != ans.end(); ++itt)
		  node->stringNumber.insert(*itt);
    }
    return node->stringNumber;
}