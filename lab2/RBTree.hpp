#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>

const char BLACK = 1;
const char RED = 2;

//Class for tree node
class Node
{
public:
    char *key;
    unsigned long long value;
    char Colour = BLACK;

    Node *parent = nullptr;
    Node *Left = nullptr;
    Node *Right = nullptr;

    Node()
    {
        key = (char *)calloc(260, sizeof(char));
        if (key == nullptr)
        {
            throw std::bad_alloc();
        }
        value = 0;
        key = strcpy(key, "");
    }

    Node(char *inpkey, unsigned long long inpval)
    {
        key = (char *)calloc(260, sizeof(char));
        if (key == nullptr)
        {
            throw std::bad_alloc();
        }
        key = strcpy(key, inpkey);
        value = inpval;
    }

    Node(unsigned long long inpval, char *inpkey)
    {
        key = (char *)calloc(260, sizeof(char));
        if (key == nullptr)
        {
            throw std::bad_alloc();
        }
        key = strcpy(key, inpkey);
        value = inpval;
    }

    ~Node()
    {
        free(key);
    }

    Node *Sibling()
    {
        if (parent != nullptr && parent->Left != nullptr && parent->Right != nullptr)
        {
            if (parent->Left->key == key)
            {
                return parent->Right;
            }
            else
            {
                return parent->Left;
            }
        }
        else
        {
            return nullptr;
        }
    }

    bool Isleft()
    {
        if (parent != nullptr && parent->Left != nullptr && parent->Left->key != nullptr && parent->Left->key == key)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Islist()
    {
        if (Right == nullptr || Left == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

int StrCmp(const char *lhs, const char *rhs)
{
    if (lhs == nullptr || rhs == nullptr)
    {
        if (lhs == nullptr)
        {
            return -1;
        }
        if (rhs == nullptr)
        {
            return 1;
        }
    }

    size_t i = 0;
    while (lhs[i] != 0 || rhs[i] != 0)
    {
        if (lhs[i] == rhs[i])
        {
            ++i;
            continue;
        }
        else
        {
            char cmp_l = lhs[i];
            char cmp_r = rhs[i];
            if (lhs[i] >= 'A' && lhs[i] <= 'Z')
            {
                cmp_l = lhs[i] + ('a' - 'A');
            }
            if (rhs[i] >= 'A' && rhs[i] <= 'Z')
            {
                cmp_r = rhs[i] + ('a' - 'A');
            }

            if (cmp_l < cmp_r)
            {
                return -1;
            }
            else if (cmp_l > cmp_r)
            {
                return 1;
            }
            else
            {
                ++i;
                continue;
            }
        }
    }
    if (lhs[i] != 0 || rhs[i] != 0)
    {
        if (lhs[i] == 0)
        {
            return -1;
        }
        if (rhs[i] == 0)
        {
            return 1;
        }
    }

    return 0;
}

void Swap(Node *lhs, Node *rhs)
{
    char *tmpkey = (char *)calloc(300, sizeof(char));

    if (tmpkey == nullptr)
    {
        throw -1;
    }

    tmpkey = strcpy(tmpkey, rhs->key);
    unsigned long long tmpval = rhs->value;

    rhs->key = strcpy(rhs->key, lhs->key);
    rhs->value = lhs->value;

    lhs->key = strcpy(lhs->key, tmpkey);
    lhs->value = tmpval;
    free(tmpkey);
}

Node *LeftRotate(Node *centre)
{
    if (centre->parent != nullptr)
    {
        if (centre->parent->Left == centre)
        {
            centre->parent->Left = centre->Left;
        }
        else if (centre->parent->Right == centre)
        {
            centre->parent->Right = centre->Left;
        }
    }

    Node *new_centre = centre->Left;
    centre->Left = centre->Left->Right;
    centre->Left->parent = centre;

    new_centre->parent = centre->parent;
    new_centre->Right = centre;
    centre->parent = new_centre;

    return new_centre;
}

Node *RightRotate(Node *centre)
{
    if (centre->parent != nullptr)
    {
        if (centre->parent->Left == centre)
        {
            centre->parent->Left = centre->Right;
        }
        else if (centre->parent->Right == centre)
        {
            centre->parent->Right = centre->Right;
        }
    }

    Node *new_centre = centre->Right;
    centre->Right = centre->Right->Left;
    centre->Right->parent = centre;

    new_centre->parent = centre->parent;
    new_centre->Left = centre;
    centre->parent = new_centre;

    return new_centre;
}

Node *ARMreballance(Node *start_element, Node *root)
{
    if (root == start_element)
    {
        return root;
    }
    else
    {
        Node *sibl = start_element->Sibling();

        if (sibl->Colour == RED)
        {
            if (sibl->Isleft())
            {

                if (start_element->parent == root)
                {
                    root = LeftRotate(start_element->parent);
                }
                else
                {
                    LeftRotate(start_element->parent);
                }

                sibl->Colour = BLACK;
                sibl->Right->Colour = RED; //

                root = ARMreballance(start_element, root);
            }
            else
            {
                if (start_element->parent == root)
                {
                    root = RightRotate(start_element->parent);
                }
                else
                {
                    RightRotate(start_element->parent);
                }

                sibl->Colour = BLACK;
                sibl->Left->Colour = RED;

                root = ARMreballance(start_element, root);
            }
        }
        else
        {
            if (sibl->Isleft())
            {
                if (sibl->Left->Colour == BLACK && sibl->Right->Colour == BLACK && sibl->parent->Colour == BLACK)
                {
                    sibl->Colour = RED;
                    sibl->parent->Colour = BLACK;

                    root = ARMreballance(start_element->parent, root);
                }
                else if (sibl->Left->Colour == BLACK && sibl->Right->Colour == BLACK && sibl->parent->Colour == RED)
                {
                    sibl->Colour = RED;
                    sibl->parent->Colour = BLACK;
                }
                else if (sibl->Right->Colour == RED && sibl->Left->Colour == BLACK)
                {
                    sibl->Right->Colour = BLACK;
                    sibl->Colour = RED;
                    RightRotate(sibl);

                    root = ARMreballance(start_element, root);
                }
                else if (sibl->Left->Colour == RED)
                {
                    sibl->Colour = sibl->parent->Colour;
                    sibl->parent->Colour = BLACK;
                    //sibl->Right->Colour = BLACK;
                    sibl->Left->Colour = BLACK;

                    if (sibl->parent == root)
                    {
                        root = LeftRotate(sibl->parent);
                    }
                    else
                    {
                        LeftRotate(sibl->parent);
                    }
                }
            }
            else
            {
                if (sibl->Left->Colour == BLACK && sibl->Right->Colour == BLACK && sibl->parent->Colour == BLACK)
                {
                    sibl->Colour = RED;
                    sibl->parent->Colour = BLACK;

                    root = ARMreballance(start_element->parent, root);
                }
                else if (sibl->Left->Colour == BLACK && sibl->Right->Colour == BLACK && sibl->parent->Colour == RED)
                {
                    sibl->Colour = RED;
                    sibl->parent->Colour = BLACK;
                }
                else if (sibl->Left->Colour == RED && sibl->Right->Colour == BLACK)
                {
                    sibl->Left->Colour = BLACK;
                    sibl->Colour = RED;
                    LeftRotate(sibl);

                    root = ARMreballance(start_element, root);
                }
                else if (sibl->Right->Colour == RED)
                {
                    sibl->Colour = sibl->parent->Colour;
                    sibl->parent->Colour = BLACK;
                    sibl->Right->Colour = BLACK;

                    if (sibl->parent == root)
                    {
                        root = RightRotate(sibl->parent);
                    }
                    else
                    {
                        RightRotate(sibl->parent);
                    }
                }
            }
        }

        return root;
    }
}

Node *AISreballance(Node *start_element, Node *root)
{

    if (start_element->parent == nullptr)
    {
        start_element->Colour = BLACK;
    }

    if (start_element->Colour == RED)
    {
        if (start_element->parent != nullptr && start_element->parent->Colour == RED)
        {
            if (start_element->parent->Sibling() != nullptr)
            {
                if (start_element->parent->Sibling()->Colour == BLACK)
                {
                    int rcm = 0;
                    Node *new_centre;
                    if (!start_element->parent->Isleft())
                    {
                        if (start_element->Isleft())
                        {
                            if (start_element->parent->parent == root)
                            {
                                rcm = 1;
                            }

                            new_centre = LeftRotate(start_element->parent);
                            new_centre = RightRotate(start_element->parent);

                            if (rcm == 1)
                            {
                                root = new_centre;
                                rcm = 0;
                            }
                        }
                        else
                        {
                            if (start_element->parent->parent == root)
                            {
                                rcm = 1;
                            }
                            new_centre = RightRotate(start_element->parent->parent);

                            if (rcm == 1)
                            {
                                root = new_centre;
                                rcm = 0;
                            }
                        }

                        new_centre->Colour = BLACK;
                        new_centre->Left->Colour = RED;
                        new_centre->Right->Colour = RED;
                    }
                    else
                    {
                        if (!start_element->Isleft())
                        {
                            if (start_element->parent->parent == root)
                            {
                                rcm = 1;
                            }

                            new_centre = RightRotate(start_element->parent);
                            new_centre = LeftRotate(start_element->parent);

                            if (rcm == 1)
                            {
                                root = new_centre;
                                rcm = 0;
                            }
                        }
                        else
                        {
                            if (start_element->parent->parent == root)
                            {
                                rcm = 1;
                            }
                            new_centre = LeftRotate(start_element->parent->parent);

                            if (rcm == 1)
                            {
                                root = new_centre;
                                rcm = 0;
                            }
                        }

                        new_centre->Colour = BLACK;
                        new_centre->Left->Colour = RED;
                        new_centre->Right->Colour = RED;
                    }
                }
                else
                {
                    start_element->parent->parent->Colour = RED;
                    start_element->parent->parent->Left->Colour = BLACK;
                    start_element->parent->parent->Right->Colour = BLACK;
                    root = AISreballance(start_element->parent->parent, root);
                }
            }
            else
            {
                if (start_element->parent->parent == nullptr)
                {
                    start_element->parent->Colour = BLACK;
                }
                else
                {
                    start_element->parent->parent->Colour = RED;
                    start_element->parent->Colour = BLACK;
                }
            }
        }
        else
        {
            return root;
        }
    }
    else
    {
        return root;
    }
    return root;
}

int HeigthCounter(Node *start)
{
    int counter = 0;
    while (!start->Islist())
    {
        if (start->Colour == BLACK)
        {
            ++counter;
        }
        start = start->Right;
    }

    return counter;
}

int HeigthChecker(Node *start, int maxheigth, int heigth)
{
    if (start->Islist() && heigth != maxheigth)
    {
        return -1;
    }
    else if (!start->Islist() && ((start->parent != nullptr && !(start->parent->Right == start || start->parent->Left == start)) || (start->Left->parent != start) || (start->Right->parent != start)))
    {
        return -1;
    }
    else
    {
        int nextheigth = heigth;
        if (start->Colour == BLACK)
        {
            nextheigth++;
        }

        if (!start->Islist())
        {
            if (HeigthChecker(start->Right, maxheigth, nextheigth) != -1 && HeigthChecker(start->Left, maxheigth, nextheigth) != -1)
            {
                return 0;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            return 0;
        }
    }
}

Node *LoadNode(std::ifstream &fin, Node *pst)
{
    int siz[1];
    siz[0] = 0;
    unsigned long long val[1];
    val[0] = 0;
    char ch[1];
    ch[0] = 0;
    try
    {
        fin.read((char *)&siz[0], sizeof(int) / sizeof(char));
        if (siz[0] < 0 || siz[0] > 257)
        {
            throw -1;
        }

        char *stri = (char *)calloc(siz[0] + 1, sizeof(char));
        if (stri == nullptr)
        {
            throw -1;
        }

        fin.read(&stri[0], siz[0]);

        stri[siz[0]] = 0;
        fin.read((char *)&val[0], sizeof(unsigned long long) / sizeof(char));
        fin.read(&ch[0], 1);
        Node *ND = new (Node);

        if (ND->key == nullptr)
        {
            free(stri);
            delete ND;
            throw -1;
        }

        ND->key = strcpy(ND->key, stri);
        free(stri);
        ND->value = val[0];
        ND->Colour = ch[0];
        ND->parent = pst;

        if (siz[0] == 0)
        {
            delete ND;
            return nullptr;
        }
        return ND;
    }
    catch (std::ios_base::failure &fail)
    {
        throw -1;
    }
    catch (std::bad_alloc())
    {
        throw -1;
    }
}

void DestroyNode(Node *dyb)
{
    delete dyb;
}

void DestroyTree(Node *root)
{
    if (root != nullptr)
    {
        if (root->Left != nullptr)
        {
            DestroyTree(root->Left);
            root->Left = nullptr;
        }
        if (root->Right != nullptr)
        {
            DestroyTree(root->Right);
            root->Right = nullptr;
        }

        DestroyNode(root);
    }
}

Node *LoadTree(std::ifstream &fin, Node *root)
{
    Node *croot;
    try
    {
        croot = LoadNode(fin, root);
    }
    catch (int err)
    {
        return nullptr;
    }
    if (croot == nullptr)
    {
        try
        {
            croot = new (Node);
        }
        catch (std::bad_alloc())
        {
            return nullptr;
        }

        if (croot->key == nullptr)
        {
            delete croot;
            return nullptr;
        }

        croot->key = strcpy(croot->key, "");
        croot->value = 0;
        croot->Colour = BLACK;
        croot->parent = root;
        croot->Left = nullptr;
        croot->Right = nullptr;
        return croot;
    }

    croot->Left = LoadTree(fin, croot);
    croot->Right = LoadTree(fin, croot);

    if (croot->Left == nullptr || croot->Right == nullptr)
    {

        if (croot->Left != nullptr)
        {
            DestroyTree(croot->Left);
            croot->Left = nullptr;
        }

        if (croot->Right != nullptr)
        {
            DestroyTree(croot->Right);
            croot->Right = nullptr;
        }

        delete croot;
        return nullptr;
    }

    return croot;
}

int SaveNode(std::ofstream &fout, Node *ldb)
{
    try
    {
        int size = strlen(ldb->key);
        fout.write((char *)&size, sizeof(size));
        fout.write(ldb->key, size);
        fout.write((char *)&ldb->value, sizeof(unsigned long long));
        fout.write(&ldb->Colour, 1);
    }
    catch (std::ios_base::failure &fail)
    {
        return -1;
    }

    return 0;
}

int SaveTree(std::ofstream &fout, Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    if (SaveNode(fout, root) != 0)
    {
        return -1;
    }
    if (root->Left != nullptr)
    {
        if (SaveTree(fout, root->Left) != 0)
        {
            return -1;
        }
    }
    if (root->Right != nullptr)
    {
        if (SaveTree(fout, root->Right) != 0)
        {
            return -1;
        }
    }

    return 0;
}
//Class for tree

class TRBTree
{

private:
    Node *Root = nullptr;

public:
    int Add(char *key, unsigned long long &value)
    {
        if (key == nullptr)
        {
            return -3;
        }

        if (Root == nullptr)
        {
            try
            {
                Root = new (Node);
            }
            catch (std::bad_alloc())
            {
                Root = nullptr;
                return -1;
            }

            if (Root->key == nullptr)
            {
                Root = nullptr;
                return -1;
            }

            Root->Colour = BLACK;
            Root->parent = nullptr;
            Root->Left = nullptr;
            Root->Right = nullptr;

            Root->key = strcpy(Root->key, key);
            Root->value = value;

            try
            {
                Root->Right = new (Node);
            }
            catch (std::bad_alloc())
            {
                delete Root;
                Root = nullptr;
                return -1;
            }

            if (Root->Right->key == nullptr)
            {
                delete Root->Right;
                delete Root;
                Root = nullptr;
                return -1;
            }

            Root->Right->parent = Root;

            try
            {
                Root->Left = new (Node);
            }
            catch (std::bad_alloc())
            {
                delete Root->Right;
                delete Root;
                Root = nullptr;
                return -1;
            }

            if (Root->Left->key == nullptr)
            {
                delete Root->Right;
                delete Root->Left;
                delete Root;
                Root = nullptr;
                return -1;
            }

            Root->Left->parent = Root;
        }
        else
        {
            Node *last = nullptr;
            Node *cur = Root;
            //поиск места для вставки
            while (!cur->Islist())
            {
                if (cur->key == nullptr)
                {
                    return -4;
                }

                if (StrCmp(key, cur->key) == 0)
                {
                    return -7;
                }
                if (StrCmp(key, cur->key) > 0)
                {
                    last = cur;
                    cur = cur->Right;
                }
                else if (StrCmp(key, cur->key) < 0)
                {
                    last = cur;
                    cur = cur->Left;
                }
            }
            cur->parent = last;
            cur->key = strcpy(cur->key, key);
            cur->value = value;
            cur->Colour = RED;

            try
            {
                cur->Right = new Node;
            }
            catch (std::bad_alloc())
            {
                cur->key = strcpy(cur->key, "");
                cur->value = 0;
                cur->Colour = BLACK;
                cur->Right = nullptr;
                cur->Left = nullptr;
                return -1;
            }

            try
            {
                cur->Left = new Node;
            }
            catch (std::bad_alloc())
            {
                delete cur->Right;
                cur->key = strcpy(cur->key, "");
                cur->value = 0;
                cur->Colour = BLACK;
                cur->Right = nullptr;
                cur->Left = nullptr;
                return -1;
            }

            if (cur->Right->key == nullptr || cur->Left->key == nullptr)
            {

                if (cur->Left != nullptr)
                {
                    delete cur->Left;
                }

                if (cur->Right != nullptr)
                {
                    delete cur->Right;
                }

                cur->key = strcpy(cur->key, "");
                cur->value = 0;
                cur->Colour = BLACK;
                cur->Right = nullptr;
                cur->Left = nullptr;
                return -1;
            }

            cur->Right->parent = cur;
            cur->Left->parent = cur;

            Root = AISreballance(cur, Root);
        }

        return 0;
    }

    int Remove(char *inpkey)
    {
        if (inpkey == nullptr)
        {
            return -8;
        }
        Node *cur = Root;
        if (cur == nullptr)
        {
            return -8;
        }

        while (true)
        {
            if (cur->key == nullptr)
            {
                return -1;
            }
            if (cur->Islist())
            {
                return -8;
            }

            if (StrCmp(inpkey, cur->key) == 0)
            {
                break;
            }
            else if (StrCmp(inpkey, cur->key) > 0)
            {
                cur = cur->Right;
            }
            else if (StrCmp(inpkey, cur->key) < 0)
            {
                cur = cur->Left;
            }
        }

        if (cur->Left->Islist() && cur->Right->Islist())
        {
            if (cur == Root)
            {
                Root = nullptr;
                delete cur->Left;
                delete cur->Right;
                delete cur;

                return 0;
            }
            else if (cur->Colour == RED)
            {
                if (cur->Isleft())
                {
                    cur->Left->parent = cur->parent;
                    cur->parent->Left = cur->Left;
                }
                else
                {
                    cur->Left->parent = cur->parent;
                    cur->parent->Right = cur->Left;
                }
                delete cur->Right;
                delete cur;
            }
            else
            {
                if (cur->Isleft())
                {
                    if (cur->parent != nullptr)
                        cur->parent->Left = cur->Left;

                    cur->Left->parent = cur->parent;
                    Node *start = cur->Left;
                    delete cur->Right;
                    delete cur;
                    Root = ARMreballance(start, Root);
                }
                else
                {
                    if (cur->parent != nullptr)
                        cur->parent->Right = cur->Left;

                    cur->Left->parent = cur->parent;
                    Node *start = cur->Left;
                    delete cur->Right;
                    delete cur;
                    Root = ARMreballance(start, Root);
                }
            }
        }
        else if (cur->Left->Islist())
        {

            if (cur == Root)
            {
                Root = cur->Right;
                Root->Colour = BLACK;
                Root->parent = nullptr;
                delete cur->Left;
                delete cur;

                return 0;
            }

            if (cur->Colour == RED)
            {
                if (cur->Isleft())
                {
                    cur->Right->parent = cur->parent;
                    cur->parent->Left = cur->Right;
                }
                else
                {
                    cur->Right->parent = cur->parent;
                    cur->parent->Right = cur->Right;
                }
                delete cur->Left;
                delete cur;
            }
            else
            {
                if (cur->Right->Colour == RED)
                {
                    if (cur->Isleft())
                    {
                        cur->Right->parent = cur->parent;
                        cur->Right->Colour = BLACK;
                        cur->parent->Left = cur->Right;
                    }
                    else
                    {
                        cur->Right->parent = cur->parent;
                        cur->Right->Colour = BLACK;
                        cur->parent->Right = cur->Right;
                    }
                    delete cur->Left;
                    delete cur;
                }
                else
                {
                    return -2;
                }
            }
        }
        else if (cur->Right->Islist())
        {

            if (cur == Root)
            {
                Root = cur->Left;
                Root->Colour = BLACK;
                Root->parent = nullptr;
                delete cur->Right;
                delete cur;

                return 0;
            }

            if (cur->Colour == RED)
            {
                if (cur->Isleft())
                {
                    cur->Left->parent = cur->parent;
                    cur->parent->Left = cur->Left;
                }
                else
                {
                    cur->Left->parent = cur->parent;
                    cur->parent->Right = cur->Left;
                }
                delete cur->Right;
                delete cur;
            }
            else
            {
                if (cur->Left->Colour == RED)
                {
                    if (cur->Isleft())
                    {
                        cur->Left->parent = cur->parent;
                        cur->Left->Colour = BLACK;
                        cur->parent->Left = cur->Left;
                    }
                    else
                    {
                        cur->Left->parent = cur->parent;
                        cur->Left->Colour = BLACK;
                        cur->parent->Right = cur->Left;
                    }
                    delete cur->Right;
                    delete cur;
                }
                else
                {
                    return -2;
                }
            }
        }
        else
        {
            Node *cnb = cur->Right;
            while (!cnb->Left->Islist())
            {
                cnb = cnb->Left;
            }

            try
            {
                Swap(cur, cnb);
            }
            catch (int err)
            {
                return -1;
            }
            cur = cnb;
            if (cur->Left->Islist() && cur->Right->Islist())
            {
                if (cur == Root)
                {
                    Root = nullptr;
                    delete cur->Left;
                    delete cur->Right;
                    delete cur;

                    return 0;
                }
                else if (cur->Colour == RED)
                {
                    if (cur->Isleft())
                    {
                        cur->Left->parent = cur->parent;
                        cur->parent->Left = cur->Left;
                    }
                    else
                    {
                        cur->Left->parent = cur->parent;
                        cur->parent->Right = cur->Left;
                    }
                    delete cur->Right;
                    delete cur;
                }
                else
                {
                    if (cur->Isleft())
                    {
                        if (cur->parent != nullptr)
                            cur->parent->Left = cur->Left;

                        cur->Left->parent = cur->parent;
                        Node *start = cur->Left;
                        delete cur->Right;
                        delete cur;
                        Root = ARMreballance(start, Root);
                    }
                    else
                    {
                        if (cur->parent != nullptr)
                            cur->parent->Right = cur->Left;

                        cur->Left->parent = cur->parent;
                        Node *start = cur->Left;
                        delete cur->Right;
                        delete cur;
                        Root = ARMreballance(start, Root);
                    }
                }
            }
            else if (cur->Left->Islist())
            {

                if (cur == Root)
                {
                    Root = cur->Right;
                    Root->Colour = BLACK;
                    Root->parent = nullptr;
                    delete cur->Left;
                    delete cur;

                    return 0;
                }

                if (cur->Colour == RED)
                {
                    if (cur->Isleft())
                    {
                        cur->Right->parent = cur->parent;
                        cur->parent->Left = cur->Right;
                    }
                    else
                    {
                        cur->Right->parent = cur->parent;
                        cur->parent->Right = cur->Right;
                    }
                    delete cur->Left;
                    delete cur;
                }
                else
                {
                    if (cur->Right->Colour == RED)
                    {
                        if (cur->Isleft())
                        {
                            cur->Right->parent = cur->parent;
                            cur->Right->Colour = BLACK;
                            cur->parent->Left = cur->Right;
                        }
                        else
                        {
                            cur->Right->parent = cur->parent;
                            cur->Right->Colour = BLACK;
                            cur->parent->Right = cur->Right;
                        }
                        delete cur->Left;
                        delete cur;
                    }
                    else
                    {
                        return -2;
                    }
                }
            }
            else if (cur->Right->Islist())
            {

                if (cur == Root)
                {
                    Root = cur->Left;
                    Root->Colour = BLACK;
                    Root->parent = nullptr;
                    delete cur->Right;
                    delete cur;

                    return 0;
                }

                if (cur->Colour == RED)
                {
                    if (cur->Isleft())
                    {
                        cur->Left->parent = cur->parent;
                        cur->parent->Left = cur->Left;
                    }
                    else
                    {
                        cur->Left->parent = cur->parent;
                        cur->parent->Right = cur->Left;
                    }
                    delete cur->Right;
                    delete cur;
                }
                else
                {
                    if (cur->Left->Colour == RED)
                    {
                        if (cur->Isleft())
                        {
                            cur->Left->parent = cur->parent;
                            cur->Left->Colour = BLACK;
                            cur->parent->Left = cur->Left;
                        }
                        else
                        {
                            cur->Left->parent = cur->parent;
                            cur->Left->Colour = BLACK;
                            cur->parent->Right = cur->Left;
                        }
                        delete cur->Right;
                        delete cur;
                    }
                    else
                    {
                        return -2;
                    }
                }
            }
        }

        return 0;
    }

    Node *Max()
    {
        Node *scb = Root;
        if (scb == nullptr)
        {
            return nullptr;
        }

        while (!scb->Right->Islist())
        {
            scb = scb->Right;
        }

        return scb;
    }

    Node *Min()
    {
        Node *scb = Root;
        if (scb == nullptr)
        {
            return nullptr;
        }

        while (!scb->Left->Islist())
        {
            scb = scb->Left;
        }

        return scb;
    }

    Node *GetRoot()
    {
        return Root;
    }

    int ChekBlackHeighth()
    {
        if (Root == nullptr)
        {
            return 0;
        }
        if (HeigthChecker(Root, HeigthCounter(Root), 0) == -1)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }

    Node *Search(char *inpkey)
    {
        if (inpkey == nullptr)
        {
            return nullptr;
        }
        Node *cur = Root;
        if (cur == nullptr)
        {
            return nullptr;
        }

        while (true)
        {
            if (cur->Right == nullptr || cur->Left == nullptr)
            {
                return nullptr;
            }
            if (cur->key == nullptr)
            {
                return nullptr;
            }

            if (StrCmp(inpkey, cur->key) == 0)
            {
                break;
            }
            else if (StrCmp(inpkey, cur->key) > 0)
            {
                //last = cur;
                cur = cur->Right;
            }
            else if (StrCmp(inpkey, cur->key) < 0)
            {
                //last = cur;
                cur = cur->Left;
            }
        }

        return cur;
    }

    int Save(const std::string &path)
    {
        try
        {
            std::ofstream fout;
            fout.open(path, std::ios::binary | std::ios::out);
            if (!fout.is_open())
            {

                return -1;
            }
            char mark[3] = {'r', 'b', 't'};
            fout.write((char *)&mark[0], sizeof(char) * 3);
            if (SaveTree(fout, Root) != 0)
            {
                fout.close();
                return -2;
            }
            fout.close();
        }
        catch (std::ios_base::failure &fail)
        {
            return -3;
        }

        return 0;
    }

    int Load(const std::string &path)
    {

        char mark[4];
        std::ifstream fin;
        try
        {
            fin = std::ifstream(path, std::ios::binary | std::ios::in);
            if (!fin.is_open())
            {
                return -3;
            }
            fin.read((char *)mark, sizeof(char) * 3);
        }
        catch (std::ios_base::failure &fail)
        {
            fin.close();
            return -3;
        }

        if (!(mark[0] == 'r' && mark[1] == 'b' && mark[2] == 't'))
        {
            fin.close();
            return -2;
        }

        Node *NewRoot = nullptr;
        NewRoot = LoadTree(fin, NewRoot);
        if (NewRoot != nullptr)
        {

            fin.close();
            DestroyTree(Root);
            Root = NewRoot;
            return 0;
        }

        DestroyTree(NewRoot);
        fin.close();
        return -1;
    }

    void Destroy()
    {
        DestroyTree(Root);
        Root = nullptr;
    }

    ~TRBTree()
    {
        DestroyTree(Root);
    }
};
