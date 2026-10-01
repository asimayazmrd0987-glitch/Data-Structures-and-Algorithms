#include <iostream>
using namespace std;

class Node
{
public:                        __________________            
    int data;  //             |  data | pointer |
    Node *next;//             |______|__________|
};

int main()
{

    Node* node1 = new Node();
    node1->data = 10;
    node1->next = nullptr;
    
    cout << node1->data << endl;
    cout << node1->next << endl;

    return 00;
}
