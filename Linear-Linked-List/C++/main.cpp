#include <iostream>
#include "random.h"
using namespace std;

// Create the node structure:
struct node {
    int data;       // The data that the node holds. This could be any data, not just int.
    node* next;     // Each node must always have a pointer to the next node in the list.
};

/*
 ___ ___
| 5 | * |-->  
 --- ---
 ___ ___
| 1 | / |
 --- ---
 */

int main() {

    node * head = new node;

    head -> data = random_number(0, 10);
    head -> next = nullptr;

    cout << "head -> data = " << head -> data << endl;

    return 0;
}
