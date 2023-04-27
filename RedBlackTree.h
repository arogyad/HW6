#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <string>
#include <iostream>

using namespace std;

enum Color {
    Red = 0,
    Black = 1,
};

struct RBTNode {
    Color color = Color::Red;
    int value = 0;
    RBTNode* left = nullptr;
    RBTNode* right = nullptr;

    bool operator==(const RBTNode& other) const {
        return this->value == other.value;
    };

    bool operator<(const RBTNode& other) const {
        return this->value < other.value;
    }

    bool operator>(const RBTNode& other) const {
        return this->value > other.value;
    }
};

class RedBlackTree {
public:
    RedBlackTree(const RedBlackTree &other);
    RedBlackTree()= default;
    ~RedBlackTree();
    string ToInfixString() const { return ToInfixString(this->root); }
    string ToPrefixString() const { return ToPrefixString(this->root); }
    string ToPostfixString() const { return ToPostfixString(this->root); }
    void Insert(int value);
    void Remove(int value);
    bool Contains(int value) const;
    int GetMax() const;
    int GetMin() const;
    unsigned int Size() const;
    RBTNode* root = nullptr;

private:
    unsigned long long int numItems = 0;
    static string ToInfixString(const RBTNode* pos);
    static string ToPrefixString(const RBTNode* pos);
    static string ToPostfixString(const RBTNode* pos);
    void get_all(RBTNode* node, RBTNode*** parent, RBTNode*** grandparent, RBTNode*** uncle);
    void get_node_replacement(int value, RBTNode** node, RBTNode** replacement);
    void BinaryInsert(int value, RBTNode **inserted, RBTNode*** parent, RBTNode*** grandparent, RBTNode*** uncle);
    void BinaryRemove(int value);
    void DoBalance(RBTNode* node, RBTNode** parent, RBTNode** grandparent, RBTNode** uncle);
    void get_parent(RBTNode* node, RBTNode** parent);
    void find(RBTNode* node, RBTNode*** location);
    void fix_double_black(RBTNode* node);
    static void right_rotate(RBTNode** node);
    static void left_rotate(RBTNode** node);
    static void copy(RBTNode *node, RBTNode** other);
};

#endif
