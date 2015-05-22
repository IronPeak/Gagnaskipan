#include <iostream>

using namespace std;

struct TreeNode
{
    int data;
    TreeNode* leftChild;
    TreeNode* rightChild;

    TreeNode(int Data, TreeNode* LeftChild = NULL, TreeNode* RightChild = NULL)
    {
        data = Data;
        leftChild = LeftChild;
        rightChild = RightChild;
    }
};

typedef TreeNode* NodePtr;

class IntBinaryTree
{
private:
    NodePtr root;

    NodePtr& min(NodePtr& node)
    {
        if(node->leftChild != NULL)
        {
            return min(node->leftChild);
        }
        return node;
    }

public:
    IntBinaryTree()
    {
        root = NULL;
    }
    ~IntBinaryTree()
    {
        remove_all(root);
    }
    void remove_all(NodePtr node) // should be private but placed here for readability
    {
        if(node != NULL)
        {
            remove_all(node->leftChild);
            remove_all(node->rightChild);
            delete node;
        }
    }
    void add(int elem)
    {
        add(elem, root);
    }
    void add(int elem, NodePtr& node) //should be private but placed here for readability
    {
        if(node == NULL)
        {
            node = new TreeNode(elem);
            return;
        }
        if(elem < node->data)
        {
            add(elem, node->leftChild);
        }
        else if(node->data < elem)
        {
            add(elem, node->rightChild);
        }
        else
        {
            cout << "The value " << elem << " is already in the list" << endl;
            return;
        }
    }
    void remove(int elem)
    {
        remove(elem, root);
    }
    void remove(int elem, NodePtr& node) //should be private but placed here for readability
    {
        if(node == NULL)
        {
            cout << "Sorry, couldn't find the target node" << endl;
            return;
        }
        if(elem < node->data)
        {
            remove(elem, node->leftChild);
        }
        else if(node->data < elem)
        {
            remove(elem, node->rightChild);
        }
        else
        {
            //We found the target node

            NodePtr temp = node;
            if(node->leftChild == NULL)
            {
                node = node->rightChild;
            }
            else if(node->rightChild == NULL)
            {
                node = node->leftChild;
            }
            else
            {
                NodePtr& newParent = min(node->rightChild);
                node->data = newParent->data;
                temp = newParent;
                newParent = newParent->rightChild;
            }
            delete temp;

            return;
        }
    }
    bool contains(int elem)
    {
        return contains(elem, root);
    }
    bool contains(int elem, NodePtr& node) //should be private but placed here for readability
    {
        if(node == NULL)
        {
            return false;
        }
        if(elem < node->data)
        {
            return contains(elem, node->leftChild);
        }
        else if(node->data < elem)
        {
            return contains(elem, node->rightChild);
        }
        else
        {
            return true;
        }
    }
    void print()
    {
        print(root);
        cout << endl;
    }
    void print(NodePtr node) //A private function placed here for readability
    {
        if(node == NULL)
        {
            return;
        }
        //Calling them in this order ensures they will be printed in ascending order, reverse these 3 lines to to print in descending order.
        print(node->leftChild);
        cout << node->data << " ";
        print(node->rightChild);
    }
};

int main()
{
    IntBinaryTree tree;

    while(true)
    {
        string cmd;
        cin >> cmd;
        if(cmd == "add")
        {
            int value;
            cin >> value;
            tree.add(value);
        }
        if(cmd == "remove")
        {
            int value;
            cin >> value;
            tree.remove(value);
        }
        if(cmd == "contains")
        {
            int value;
            cin >> value;
            tree.contains(value);
        }
        tree.print();
    }

    return 0;
}
