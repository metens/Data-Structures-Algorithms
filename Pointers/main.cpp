#include "helpers.h"
#include "pointer_pair.h"

int main() {

    /* Creating variables: */

    int num {10}; 
    /*  num 
      |------|
      |  10  |
      |------| 
        0xb7  */

    bool con {true}; // true == 1, false == 0

    char let {'a'};

    float val {4.7};

    /* Creating pointers: */

    int* num_ptr {&num};

    char* l_ptr {nullptr};

    // Display section
    /*show_code("int num {10};");
    display("num", num);

    show_code("bool con {true};");
    display("con", con); 

    show_code("char let {'a'};");
    display("let", let);

    show_code("float val {4.7};");
    display("val", val);

    show_code("int* num_ptr {&num};");
    display("n_ptr", num_ptr);

    show_code("char* l_ptr {nullptr};");
    display("l_ptr", l_ptr);*/

    // Pointer connection


    display("num", num);          // your current single-variable display
    display("num_ptr", num_ptr);      // your current pointer variable display

    display_pointer_pair("num_ptr", num_ptr, "num", num);

    display_pointer_deref("num_ptr", num_ptr, "num", num);

    return 0;
}
