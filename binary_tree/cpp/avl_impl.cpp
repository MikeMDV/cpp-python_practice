#include <iostream>
#include <string>

struct Node
{
    int   data;
    Node *right;
    Node *left;
    int   height;

    Node()
    :right(NULL),
     left(NULL)
    {

    }
};

class AVLTree
{

public:

    AVLTree(Node *inRoot)
        : root(inRoot)
    {

    }

    int getNodeHeight(Node *current)
    {
        if (current == NULL)
        {
            return -1;
        }
        else
        {
            return current->height;
        }
    }

    void setHeight(Node *current)
    {
        int lchild = getNodeHeight(current->left);
        int rchild = getNodeHeight(current->right);
        if (lchild < rchild)
        {
            current->height = 1 + rchild;
        }
        else
        {
            current->height = 1 + lchild;
        }
    }

    Node * nodeAdd(Node *current, int newData)
    {
        Node *newNode = new Node;
        
        if (current == NULL)
        {
            newNode->data = newData;
            return newNode;
        }
        else if(newData < current->data)
        {
            current->left = nodeAdd(current->left, newData);
        }
        else
        {
            current->right = nodeAdd(current->right, newData);
        }

        return balance(current);
    }

    int balanceFactor(Node *current)
    {
        return getNodeHeight(current->right) - getNodeHeight(current->left);
    }

    Node * balance(Node *current)
    {
        int currentBalFac = balanceFactor(current);
        if (currentBalFac < 1)
        {
            if (balanceFactor(current->left) > 0) // double rotation
            {
                current->left = rotateLeft(current->left);
            }
            return rotateRight(current); // single rotation
        }
        else if (currentBalFac > 1)
        {
            if (balanceFactor(current->right) < 0)
            {
                current->right = rotateRight(current->right);
            }
            return rotateLeft(current);
        }
        setHeight(current);
        return current;
    }

    Node * rotateLeft(Node *current)
    {
        Node *newRoot = current->right;

        current->right = newRoot->left;

        newRoot->left = current;

        setHeight(newRoot->left);
        setHeight(newRoot);

        return newRoot;
    }

    Node * rotateRight(Node *current)
    {
        Node *newRoot = current->left;

        current->left = newRoot->right;

        newRoot->right = current;

        setHeight(newRoot->right);
        setHeight(newRoot);

        return newRoot;
    }

    void printData(Node *node)
    {
        std::cout << node->data << "\n";
    }

    void inOrderTraversal(Node *node)
    {
        if (node != NULL)
        {
            inOrderTraversal(node->left);
            printData(node);
            inOrderTraversal(node->right);
        }
    }

    void preOrderTraversal(Node *node)
    {
        if (node != NULL)
        {
            printData(node);
            preOrderTraversal(node->left);
            preOrderTraversal(node->right);
        }
    }

    void postOrderTraversal(Node *node)
    {
        if (node != NULL)
        {
            postOrderTraversal(node->left);
            postOrderTraversal(node->right);
            printData(node);
        }
    }


    Node *root;
    
};


int main(int argc, char* argv[])
{
    int rootData = 4;
    Node *root = new Node;
    root->data = rootData;
    AVLTree tree(root);
    tree.inOrderTraversal(tree.root);
    std::cout << "Adding 34" << "\n";
    int newData = 34;
    tree.root = tree.nodeAdd(tree.root, newData);
    std::cout << "New root = " << "\n";
    tree.printData(tree.root);
    tree.inOrderTraversal(tree.root);
    tree.preOrderTraversal(tree.root);
    std::cout << "Adding 6" << "\n";
    newData = 6;
    tree.root = tree.nodeAdd(tree.root, newData);
    std::cout << "New root = " << "\n";
    tree.printData(tree.root);
    tree.inOrderTraversal(tree.root);
    tree.preOrderTraversal(tree.root);
    std::cout << "Adding 1" << "\n";
    newData = 1;
    tree.root = tree.nodeAdd(tree.root, newData);
    std::cout << "New root = " << "\n";
    tree.printData(tree.root);
    tree.inOrderTraversal(tree.root);
    tree.preOrderTraversal(tree.root);
    std::cout << "Adding 56" << "\n";
    newData = 56;
    tree.root = tree.nodeAdd(tree.root, newData);
    std::cout << "New root = " << "\n";
    tree.printData(tree.root);
    tree.inOrderTraversal(tree.root);
    tree.preOrderTraversal(tree.root);
    std::cout << "Adding 2" << "\n";
    newData = 2;
    tree.root = tree.nodeAdd(tree.root, newData);
    std::cout << "New root = " << "\n";
    tree.printData(tree.root);
    tree.inOrderTraversal(tree.root);
    tree.preOrderTraversal(tree.root);
    //tree.postOrderTraversal(tree.root);
    

    return 0;
}
