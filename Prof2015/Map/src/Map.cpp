#include "Map.h"

Map::Map()
{
    sum = 0;
    root = NULL;
}

Map::~Map()
{
    remove(root);
}

void Map::remove(NodePtr& node)
{
    if(node == NULL)
    {
        return;
    }
    remove(node->left);
    remove(node->right);
    delete node;
}

void Map::add(string key, int value)
{
    NodePtr& node = find(key, root);
    if(node == NULL)
    {
        node = new TreeNode(key, value);
        sum += value;
    }
    else
    {
        sum += value - node->value;
        node->value = value;
    }
}

NodePtr& Map::find(string key, NodePtr& node)
{
    if(node == NULL)
    {
        return node;
    }
    if(key < node->key)
    {
        return find(key, node->left);
    }
    if(key > node->key)
    {
        return find(key, node->right);
    }
    return node;
}

int Map::sum_values()
{
    return sum;
}

void Map::print_by_values(int n)
{
    print_by_values(root, n);
}

void Map::print_by_values(NodePtr node, int n)
{
    if(node == NULL)
    {
        return;
    }
    print(node->left);
    if(n <= node->value)
    {
        cout << node->key << " " << node->value << endl;
    }
    print(node->right);
}

void Map::remove_max()
{
    if(root == NULL)
    {
        throw;
    }
    NodePtr& m = max(root);
    sum -= m->value;
    if(m->left == NULL)
    {
        delete m;
        m = NULL;
    }
    else
    {
        NodePtr temp = m;
        m = m->left;
        delete temp;
    }
}

NodePtr& Map::max(NodePtr& node)
{
    if(node == NULL)
    {
        return node;
    }
    if(node->right == NULL)
    {
        return node;
    }
    return max(node->right);
}

void Map::print()
{
    print(root);
}

void Map::print(NodePtr node)
{
    if(node == NULL)
    {
        return;
    }
    print(node->left);
    cout << node->key << " " << node->value << endl;
    print(node->right);
}
