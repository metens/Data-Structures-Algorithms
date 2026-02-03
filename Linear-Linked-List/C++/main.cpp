#include <iostream>
#include "address_display.h"
using namespace std;

#include <iostream>
#include <thread>
#include <chrono>

inline void clear_screen() {
    // ANSI clear + move cursor home
    std::cout << "\033[2J\033[H";
}

inline void pause_ms(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void display_single_node_colored(int data,
                                 const std::string& next_text,
                                 const std::string& addr_text,
                                 bool highlight_next = false,
                                 bool highlight_node = false) {
    std::string d = std::to_string(data);
    std::string nxt = next_text;

    if (highlight_node) {
        d = ansi::color(d, ansi::GREEN);
    }
    if (highlight_next) {
        nxt = ansi::color(nxt, ansi::YELLOW);
    }

    std::cout << " --- ------\n";
    std::cout << "| " << d << " | " << nxt << " |\n";
    std::cout << " --- ------\n";
    std::cout << "  " << (highlight_node ? ansi::color(addr_text, ansi::CYAN) : addr_text) << "\n";
}

void animate_push_front(node*& head) {

    int pause = 5000;

    // Frame 1: before
    clear_screen();
    std::cout << ansi::BOLD << "=== Before push_front(9) ===" << ansi::RESET << "\n";
    display_list(head);
    pause_ms(pause);

    // Allocate new node
    node* newNode = new node;
    newNode->data = 9;
    newNode->next = nullptr;

    // Frame 2: new node allocated (highlight node itself)
    clear_screen();
    std::cout << ansi::BOLD << "=== (new node allocated) ===" << ansi::RESET << "\n";
    display_list(head);
    std::cout << "\n";
    display_single_node_colored(9, "NULL", short_addr(newNode),
                                /*highlight_next=*/false,
                                /*highlight_node=*/true);
    pause_ms(pause);

    // Frame 3: pointer set new->next = head (highlight the next pointer field)
    newNode->next = head;
    clear_screen();
    std::cout << ansi::BOLD << "=== (pointer set: new->next = head) ===" << ansi::RESET << "\n";
    display_list(head);
    std::cout << "\n";
    display_single_node_colored(9, short_addr(head), short_addr(newNode),
                                /*highlight_next=*/true,
                                /*highlight_node=*/true);
    pause_ms(pause);

    // Frame 4: head = new (final list, highlight head label)
    head = newNode;
    clear_screen();
    std::cout << ansi::BOLD << "=== After head = new ===" << ansi::RESET << "\n";

    // Optional: make your head label cyan/bold inside display_head_label
    display_list(head);
}


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

    animate_push_front(head);

/*
    snapshot("Before push_front(9)", head);

    node* newNode = new node;
    newNode->data = 9; newNode->next = nullptr;
    std::cout << "\n(new node allocated)\n";
    string newNodeAddr = short_addr(newNode);
    display_single_node(9, "NULL", newNodeAddr);

    newNode->next = head;
    std::cout << "\n(pointer set: new->next = head)\n";
    display_single_node(9, short_addr(head), newNodeAddr); 

    head = newNode;
    snapshot("After head = new", head);
*/
    return 0;
}
