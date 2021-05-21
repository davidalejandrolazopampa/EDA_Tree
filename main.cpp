
//#include "avl.h"
#include "range_tree.h"

void profe_test() {
    rangeTree rang;
    rang.insert(10);
    rang.insert(3);
    rang.insert(19);
    cout << endl;
    //rang.print_preOrder();
    rang.insert(23);
    rang.insert(49); // no aparece >:v
    rang.insert(59);
    rang.insert(62);
    rang.insert(70);
    rang.insert(100);
    rang.insert(105);
    //rang.insert(30); // no aparece >:v
    rang.insert(89);
    rang.insert(80);
    rang.insert(37);

    cout << endl;
    rang.print_preOrder();
}
int main() {

    /*root = deleteNode(root, 0);

    cout << "\nPreorder traversal after"
         << " deletion of 0 \n";
    print_tree(root);*/

    /*rangeTree rang;
    rang.insert(9);
    rang.insert(16);
    rang.insert(20);
    rang.insert(15);
    rang.print_preOrder();*/
    //rang.print_tree();

    profe_test();

    return 0;
}
// Cope and Page
