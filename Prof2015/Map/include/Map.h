#ifndef MAP_H
#define MAP_H

#include <iostream>

using namespace std;

struct TreeNode
{
public:
    string key;
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(string key, int value, TreeNode* left = NULL, TreeNode* right = NULL)
    {
        this->key = key;
        this->value = value;
        this->left = left;
        this->right = right;
    }
};

typedef TreeNode* NodePtr;

class Map
{
    public:
        Map();
        ~Map();
        void add(string key, int value);
        int sum_values();
        void print_by_values(int n);
        void remove_max();
        void print();
    private:
        int sum;
        NodePtr root;

        NodePtr& find(string key, NodePtr& node);
        void remove(NodePtr& node);
        void print(NodePtr node);
        NodePtr& max(NodePtr& node);
        void print_by_values(NodePtr node, int n);
};

#endif // MAP_H
