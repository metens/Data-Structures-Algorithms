#include "helpers.h"

int main() {

    int num = 10;

    cout << "num: " << num << endl;
    cout << "&num: " << abbrev_addr(&num) << endl;
    display_var("num", num, &num);

    bool con = true;    // true == 1, false == 0

      /*  con
        |------|
        |  1   |
        |------| 
          0xb7  */

    cout << "con: " << con << endl;
    cout << "&con: " << abbrev_addr(&con) << endl;
    display_var("con", con, &con);

    char let = 'a';

      /*  let 
        |------|
        | 'a'  |
        |------| 
          0xc9  */

    cout << "let: " << let << endl;
    cout << "&let: " << abbrev_addr((void*)&let) << endl;
    display_var("let", let, &let);

    float val = 4.7;

    cout << "val: " << val << endl;
    cout << "&val: " << abbrev_addr(&val) << endl;
    display_var("val", val, &val);

    return 0;
}
