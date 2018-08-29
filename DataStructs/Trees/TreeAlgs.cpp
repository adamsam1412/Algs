#include <queue>
#include <iostream>
#define V 100

using std::endl;
using std::cout;

struct node
{
    int value;
    node* left;
    node* right;
    node(int val)
    {
        value = val;
    }
};

void removeTree(node *& root)
{
    if(!root)
        return;
    
    removeTree(root->left);
    removeTree(root->right);
    root = nullptr;
    delete root;
}

void removeNodesOnGivenLevel(node *& root, int level, int rootLevel)
{
    if(!root)
        return;
    //static int lvl = 0;
    if(rootLevel == level)
    {
        cout << root->value << "<- value of removed root" << endl;
        removeTree(root);        
    }

    else
    {
        //lvl++;
        removeNodesOnGivenLevel(root->left, level, rootLevel + 1);
        removeNodesOnGivenLevel(root->right, level, rootLevel + 1);
    }
    
}

int numberOfNodesOnGivenLevel(node *& root, int level, int rootLevel)
{
    if(!root)
        return 0;
    static int numberOfNodes = 0;
    if(rootLevel == level)
    {
        cout << root->value << "<- value of removed root" << endl;
        numberOfNodes++;       
    }

    else
    {
        //lvl++;
        numberOfNodesOnGivenLevel(root->left, level, rootLevel + 1);
        numberOfNodesOnGivenLevel(root->right, level, rootLevel + 1);
    }

    return numberOfNodes;    
}

bool isBST(node * root)
{
    if(!root)
        return true;
    if(root->left && root->value < root->left->value)
        return false;
    if(root->right && root->value > root->right->value)
        return false;

    return isBST(root->left) && isBST(root->right);
}

int getTreeDepth(node * root)
{
    if(!root)
        return 0;
    int left = getTreeDepth(root->left);
    int right = getTreeDepth(root->right);

    if(left > right)
        return left + 1;
    else
        return right + 1;
}

bool isBalanced(node * root)
{
    if(!root)
        return true;
    int left;
    int right;

    left = getTreeDepth(root->left);
    right = getTreeDepth(root->right);

    if(abs(left - right) <= 1 && isBalanced(root->left) && isBalanced(root->right))
        return true;
     
    return false;
}


void printTree(node *& root)
{
    if(!root)
        return;
    printTree(root->left);
    cout << "node: " << root->value << endl;
    printTree(root->right);
}

int main()
{
    node* root = new node(6);
    //root = nullptr;
    root->left = new node(3);
    root->right = new node(7);
    root->left->left = new node(2);
    root->left->right = new node(4);
    root->right->left = new node(6);
    root->right->right = new node(1);
    root->right->right->right = new node(100);
    root->right->right->right->right = new node(100);
    root->left->left->left = new node(1000);

    node* nullRoot = nullptr;

    cout << "Tree: " << endl;
    printTree(root);
    cout << endl;
    cout << "Tree depth: " << getTreeDepth(root) << endl;
    cout << "is Balanced?: " << isBalanced(nullptr) << endl;
    printTree(root);
    

    return 0;
}





























