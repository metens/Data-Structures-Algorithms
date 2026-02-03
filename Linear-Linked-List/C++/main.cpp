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
    cout << "head -> data = " << head -> data << endl;

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

    current = head;
    while (current) {
        cout << current-> data << " -> ";
        current = current -> next;
    }

    cout << endl;
    display_list(head);

    return 0;
}
