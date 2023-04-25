#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <string>
#include <iostream>

using namespace std;

enum Color {
    Red = 0,
    Black = 1,
    DBlack
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
    RedBlackTree(){};
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

private:
    RBTNode* root = nullptr;
    unsigned long long int numItems = 0;
    static string ToInfixString(const RBTNode* pos);
    static string ToPrefixString(const RBTNode* pos);
    static string ToPostfixString(const RBTNode* pos);
    void BinaryInsert(int val, RBTNode** inserted);
    void BinaryRemove(int value, RBTNode* from);
    void DoBalance(RBTNode* node);
    void get_parent(RBTNode* node, RBTNode** parent);
    void find(RBTNode* node, RBTNode*** location);
    void get_uncle(RBTNode* node, RBTNode** uncle);
    void fix_double_black(RBTNode* node);
    static void right_rotate(RBTNode** node);
    static void left_rotate(RBTNode** node);
    static void copy(RBTNode *node, RBTNode** other);
};

#endif
