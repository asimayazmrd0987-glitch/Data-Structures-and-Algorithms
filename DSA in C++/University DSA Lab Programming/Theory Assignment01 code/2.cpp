#include <iostream>
using namespace std;

struct Node
{
    int ID;
    Node *next;
};
int main()
{
    const int k = 805;
    int A[8];
    Node *head = nullptr;
    //___________________________ part a___________________
    // Step 1: Calculate array elements
    for (int i = 0; i < 8; i++)
    {
        A[i] = ((((13 * k) + (17 * i) + (i * i)) % 90) + 10);
        //  Create a new node
        Node *newNode = new Node();
        newNode->ID = A[i];
        newNode->next = nullptr;
        //  Insert the node into the linked list
        if (head == nullptr)
        { // First node
            head = newNode;
        }
        else
        {
            // Find the last node
            Node *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            // Connect the new node at the end
            temp->next = newNode;
        }
    }

    //  Display the linked list
    cout << "\nAll elements of Linked List:\n";

    Node *temp = head;

    while (temp != nullptr)
    {
        cout << temp->ID << " -> ";
        temp = temp->next;
    }

                   // ___________________part b_________________________

    const int T = A[(k + 2) % 8];
    cout << "\nT: " << T << endl;
    // Search for the first occurrence of T, as defined in Question 1. Report the position and number of nodes
    //     examined.
    int freqNode = 0;
    int position = 0;
    const int X = (((7 * k) + 11) % 90) + 10;

    for (Node *temp = head; temp != nullptr; temp = temp->next)
    {
        freqNode++;
        if (temp->ID == T)
        {
            position = freqNode;
            // _____________part c____________________
            // inserting a new node
            Node *newNode = new Node();
            newNode->ID = X;
            newNode->next = temp->next;
            temp->next = newNode;
            break;
        }
    }
    if (position == 0)
    {
        cout << "T is not found in the linked list" << endl;
    }
    cout << "Number of Nodes: " << freqNode << endl;
    cout << "Position: " << position << endl;

    //  Display the linked list
    cout << "insert Node after \'T\' Linked List:\n";
    Node *tem = head;
    while (tem != nullptr)
    {
        cout << tem->ID << " -> ";
        tem = tem->next;
    }

    cout<<"\n\n";
    //_____________________part d_________________
    //  Delete the first node containing D = A[(K + 5) mod 8]. Handle the case where the node to be deleted is the head
    // of the list. 
    int D = A[(k + 5) % 8];
    cout << "D: " << D << endl;
    Node *prev = nullptr;
    Node *temp2 = head;
    if (head != nullptr && head->ID == D)
    {
        Node *temp3 = head;
        head = head->next;
        delete temp3;
    }
    else
    {
        while (temp2 != nullptr && temp2->ID != D)
        {
            prev = temp2;
            temp2 = temp2->next;
        }
        if (temp2 != nullptr)
        {
            prev->next = temp2->next;
            delete temp2;
        }
        else {            cout << "Value not found in the linked list." << endl; }
    }
    // ________________part e____________
    cout << "Linked List:\n";
    Node *temp1 = head;
    while (temp1 != nullptr)
    {
        cout << temp1->ID << " -> ";
        temp1 = temp1->next;
    }
    return 0;
}