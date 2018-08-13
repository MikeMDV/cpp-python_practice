#include <iostream>
#include <string>

struct Node
{
    int data;
    Node *next;

    Node()
    :next(NULL)
    {

    }
};

class LinkedList
{

public:

    LinkedList(Node *inHead)
        : head(inHead)
    {

    }

    void appendToTail(int inData)
    {
        Node *newTail = new Node;
        Node *n = head;
        while (n->next != NULL)
        {
            n = n->next;
        }
        n->next = newTail;
        n->next->data = inData;
    }

    int getTailData()
    {
        Node *n = head;
        while (n->next != NULL)
        {
            n = n->next;
        }
        return n->data;
    }

    void displayAllData()
    {
        Node *n = head;
        while (n->next != NULL)
        {
            std::cout << "Node data = " << n->data << "\n";
            n = n->next;
        }
        std::cout << "Node data = " << n->data << "\n";
    }

    void removeTail()
    {
        Node *n = head;
        if (n->next == NULL)
        {
            return;
        }
        else if (n->next->next == NULL)
        {
            // Node after head is tail
            delete n->next->next;
            n->next = NULL;
        }
        else
        {
            // n2 will be end and n will be new end
            Node *n2 = head->next;
            while (n2->next != NULL)
            {
                n2 = n2->next;
                n = n->next;
            }
            delete n2;
            n->next = NULL;
        }
    }

    int getKthToEndData(int k)
    {
        Node *n = head;
        // Count current number of nodes
        int numOfNodes = 1;
        while (n->next != NULL)
        {
            numOfNodes++;
            n = n->next;
        }

        if (numOfNodes < k || numOfNodes == k)
        {
            return -1;
        }
        else
        {
            n = head;
            for (int i = 0; i < k; i++)
            {
                n = n->next;
            }

            Node *n2 = head;

            while (n->next != NULL)
            {
                n2 = n2->next;
                n = n->next;
            }

            return n2->data;
        }


    }

    Node *head;
    
};


int main(int argc, char* argv[])
{
    int headData = 4;
    Node *head = new Node;
    head->data = headData;
    LinkedList list(head);

    std::cout << "Tail data = " << list.getTailData() << "\n";

    list.removeTail();

    std::cout << "New tail data = " << list.getTailData() << "\n";

    int newData = 6;
    list.appendToTail(newData);

    std::cout << "New tail data = " << list.getTailData() << "\n";

    list.displayAllData();

    newData = 83;
    list.appendToTail(newData);
    newData = 78;
    list.appendToTail(newData);

    list.displayAllData();

    std::cout << "New tail data = " << list.getTailData() << "\n";

    list.removeTail();

    std::cout << "New tail data = " << list.getTailData() << "\n";
    newData = 63;
    list.appendToTail(newData);
    newData = 2;
    list.appendToTail(newData);

    list.displayAllData();

    int k = std::stoi(argv[1]);

    int kthToEndData = list.getKthToEndData(k);

    std::cout << k << " from end data = " << kthToEndData << "\n";

    return 0;
}
