#include "SuffTree.h"
#include <utility>

TSuffixTree::TSuffixTree(const std::string& p1, const std::string& p2){
    input = p1 + "^" + p2 + "_";
    pattern1 = p1;
    pattern2 = p2;
    Build();
}
void TSuffixTree::Build(){
    activeNode = root;
    for (size_t i = 0; i < input.length(); ++i)
        StartPhase(i);  
    MarkUp(root);
    ans.length = 0;
    num_max_substring = 0;
    FindNumMax(root, 0);
    std::vector <TSuffixNode *> path_to_sub;
    FindLongestSubstrings(root, 0,  path_to_sub);
    std::list <std::string> answer_string;
    for( long long i = 0; i < (long long) answer.size();++i) {
        std::string a_string;
        for( long long j = 0; j < ( long long) answer[i].path_to_subs.size();++j) {
            std::string next_string(input.substr(answer[i].path_to_subs[j]->l, *(answer[i].path_to_subs[j]->r) - answer[i].path_to_subs[j]->l + 1));
            a_string += next_string;
        }
        answer_string.push_back(a_string);
    }
    answer_string.sort();
    std::cout << num_max_substring << '\n';
    for(auto i = answer_string.begin(); i != answer_string.end();++i){
        std::cout << *i << '\n';
    }
}



void TSuffixTree::StartPhase(long long i){
        //Перед началом каждой фазы создаём указатель на последнюю созданную внутреннюю ноду со значением null.
        TSuffixNode* lastCreatedInternalNode = nullptr;
        //Увеличиваем глобальную переменную end на 1.
        end++;
        //Счётчик для создаваемых листов.
        remainingSuffixCount++;
        while(remainingSuffixCount > 0){
            //Если active length = 0, то смотрим на текущий символ корня.
            if(activeLength == 0){
              activeEdge = i; // индекс текущего символа в тексте определяет дугу, по которой будем двигаться
            }  
            // ищем текущий символ в начале исходящих из activeNode дуг        
            auto find = activeNode->children.find(input[activeEdge]);

            // не нашли подходящую дугу
            if (find == activeNode->children.end())
            {
                // добавим новую листовую дугу, исходящую из activeNode, начинающуся текущим символом
                activeNode->children.insert(std::make_pair(input[activeEdge],
                    new TSuffixNode(root, i, &end, i - remainingSuffixCount + 1)));
                // Так как мы создали новую  вершинку, установим на нее суффикстую ссылку последней созданной внутренней вершины
                if (lastCreatedInternalNode != nullptr)
                {
                    lastCreatedInternalNode->sLink = activeNode;
                    lastCreatedInternalNode = nullptr;
                }
            }
            else
            {
                // а если есть дуга из activeNode, начинающаяся текущим символом, пойдем по ней спускаться
                TSuffixNode *next = find->second;
                long long edge_length = distance(next);

                // спуск по дуге
                if (activeLength >= edge_length)
                {
                    activeEdge += edge_length;
                    activeLength -= edge_length;
                    activeNode = next;
                    continue; // таким образом мы будем спускаться, покуда не станет activeLength < edge_length
                }

                // правило 3: если текущий символ есть на дуге,
                // т.е. суффикс уже есть в дереве, то просто увеличим activeLength
                // шагнем вперед по дуге
                if (input[next->l + activeLength] == input[i])
                {
                    // если lastCreatedInternalNode != null
                    // это означает, что 2-е правило было применено ранее (создание новой вн. вершины)
                    // установим суффиксную ссылку в activeNode
                    if (lastCreatedInternalNode != nullptr && activeNode != root)
                        lastCreatedInternalNode->sLink = activeNode;
                    activeLength++;
                    break; // выйдем из цикла while
                }
            // сюда попали, если текущего символа нет на дуге
            // создадим новую внутреннюю вершинку
            TSuffixNode *split = new TSuffixNode(root, next->l, new long long(next->l + activeLength - 1),-1);
            // подвесим к activeNode новую вершинку
            activeNode->children[input[activeEdge]] = split;
            // у следующей вершинки изменим начало, так как мы ее разделили
            next->l += activeLength;
            // подвесим новую листовую вершинку
            split->children.insert(std::make_pair(input[i], new TSuffixNode(root, i, &end, i - remainingSuffixCount + 1)));
            // подвесим отдельную вершинку
            split->children.insert(std::make_pair(input[next->l], next));
            // Устанавлиает суффиксные ссылки
            if (lastCreatedInternalNode != nullptr)
                lastCreatedInternalNode->sLink = split;
            lastCreatedInternalNode = split;
        }

        remainingSuffixCount--;

        // если activeNode == root, тогда согласно правилу 2, мы декриментируем activeLength и инкрементируем activeEdge
        // это, можно сказать, альтернатива суфф. ссылке в случае, когда activeNode == root
        if (activeNode == root && activeLength > 0)
        {
            activeLength--;
            activeEdge++;
        }
        else if (activeNode != root) // если же activeNode != root, то переходим по суффиксной ссылке
            activeNode = activeNode->sLink;
    }
}


void TSuffixTree::Display(TSuffixNode *p )
{
    static int level = 0;
    level++;
    if (p->l == -1)
        std::cout << ">> <root>";
    else
        for (int i = p->l; i <= *(p->r); ++i) {
            std::cout << input[i];
        }
        std::cout << p->number_string.size() << "  ";
        for(auto it = p->number_string.begin(); it != p->number_string.end(); ++it){
            std::cout << *it << ' ';
        }
    for (int i = '^'; i < (int) 'z' + 1; ++i)
    {
        auto next_child = p->children.find(i);
        if(next_child != p->children.end()){
            std::cout << "\n";
            for (int j = 0; j < level; j++)
                std::cout << "   ";
            std::cout << ">>";
            Display(next_child->second);
        }
    }
    level--;
}

void TSuffixTree::DisplayTree()
{
    Display(root);
}

// Ищет максимальную длину построки
void TSuffixTree::FindNumMax(TSuffixNode* node,  long long walk) {
    if (node->number_string.size() == 2) {
        if(node != root) {
            walk += *(node->r) - node->l + 1;
            if (walk > num_max_substring) {
                num_max_substring = walk;
            }
        }
        for (auto i =node->children.begin(); i != node->children.end(); ++i) {
                FindNumMax(i->second, walk);
        }
    }
}

// Ищет самые длинный подстроки
void TSuffixTree::FindLongestSubstrings(TSuffixNode *node,  long long walk, std::vector<TSuffixNode *>& path_to_sub) {
    if (node->number_string.size() == 2) {
        if(node != root) {
            if(walk == 0) {
                path_to_sub.clear();
            }
            path_to_sub.emplace_back(node);

            walk += *(node->r) - node->l + 1;
            if (walk == num_max_substring) {
                ans.path_to_subs = path_to_sub;
                ans.length = walk;
                answer.emplace_back(ans);
                path_to_sub.pop_back();
                return;
            }
        }
        for (auto i = node->children.begin(); i != node->children.end(); ++i){
                FindLongestSubstrings(i->second, walk, path_to_sub);
 
        }
        if(path_to_sub.size()){
            path_to_sub.pop_back();
        }
    }
}

TSuffixTree::~TSuffixTree() {
    RecursiveDestroy(root);
}



void TSuffixTree::RecursiveDestroy(TSuffixNode *node) {
   for (auto i = node->children.begin(); i != node->children.end(); ++i){
            RecursiveDestroy(i->second);
    }
    if(node->r != &end){
        delete node->r;
    }
    delete node;
}

int TSuffixTree::distance(TSuffixNode* node){
    return *node->r - node->l + 1;
}

std::set<int> TSuffixTree::MarkUp(TSuffixNode * node) {
    if(node != root){
        if(input[node->l] == '^')
            node->number_string.insert(1);
        else if(input[node->l] == '_')
            node->number_string.insert(2);
        else if(distance(node) > 0) {
            int size = pattern2.size();
            if (distance(node) - 2 > size) {
                node->number_string.insert(1);
            } else if (input[*node->r] == *(input.end() - 1)) {
                node->number_string.insert(2);
            }
        }
    }
    for (auto it = node->children.begin(); it != node->children.end(); ++it) {
        TSuffixNode* next = it->second;
        std::set<int> ans = MarkUp(next);
        for(auto itt = ans.begin(); itt != ans.end(); ++itt)
            node->number_string.insert(*itt);
    }
    return node->number_string;
}