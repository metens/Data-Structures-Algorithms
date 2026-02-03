#include <iostream>
#include "address_display.h"
using namespace std;

/*
 ___ ___
| 5 | * |-->  
 --- ---
 ___ ___
| 1 | / |
 --- ---
 */

int main() {

    node* head = new node;
    head -> data = random_number(0, 9);
    head -> next = nullptr;

    node* current = head;

    int i = 0;
    while (i < 6) {
        node* new_node = new node;
        current -> next = new_node;
        current = new_node;
        current -> data = random_number(0, 9);
        current -> next = nullptr;

        ++i;
    }

    /* Snapshot tutorial */

    snapshot("Before push_front(9)", head);

    node* newNode = new node;
    newNode->data = 9; newNode->next = nullptr;
    std::cout << "\n(new node allocated)\n";
    //display_single_node(9, "NULL", "0x??");
    string newNodeAddr = to_string(random_number(0xAB, 0xFF));
    display_single_node(9, "NULL", newNodeAddr);

    newNode->next = head;
    std::cout << "\n(pointer set: new->next = head)\n";
    //display_single_node(9, "0x(head)", to_string(random_number(0xAB, 0xFF)));
    display_single_node(9, "head", newNodeAddr); 

    head = newNode;
    snapshot("After head = new", head);

    return 0;
}
