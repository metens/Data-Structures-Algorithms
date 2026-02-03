#include <iostream>
using namespace std;

struct node {
    int data;
    node* next;
};

int main() {

    node * head = new node;

    head -> data = 10;
    head -> next = nullptr;

    cout << "head -> data = " << head -> data << endl;

    return 0;
}
