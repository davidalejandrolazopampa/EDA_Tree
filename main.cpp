
//#include "avl.h"
//#include "range_tree.h"
#include "Components/two_d_range_tree.h"

void profe_test() {
    rangeTree rang;
    rang.insert(10, {10, 10});
    rang.insert(3, {3, 3});
    rang.insert(19, {19, 19});
    cout << endl;
    //rang.print_preOrder();
    rang.insert(23, {23, 23});
    rang.insert(49,{49, 49});
    rang.insert(59,{59, 59});
    rang.insert(62, {62,62});
    rang.insert(70,{70,70});
    rang.insert(100,{100,100});
    rang.insert(105,{105,105});
    rang.insert(30,{30,30});
    //rang.print_preOrder();
    rang.insert(89,{89,89});
    rang.insert(80,{80,80});
    rang.insert(37,{37,37});
    cout << endl;
    rang.print_preOrder();
    cout << " \nleaves "<<endl;
    rang.print_leaf();
    cout << " \nRange from 17 -> 40"<<endl;
    rang.search1Drange(17, 40);
    cout << " \nRange from 1 -> 50"<<endl;
    rang.search1Drange(1, 50);
    cout << " \nRange from 15 -> 19"<<endl;
    rang.search1Drange(15, 19);
    cout << " \nRange from 59 -> 60"<<endl;
    rang.search1Drange(59, 60);



}

void profe_test2d() {
    vector<coordinate> points;
    points.push_back({1,3});
    points.push_back({8,5});
    points.push_back({3,0});
    points.push_back({4,2});

    two_d_range_tree tree2D;
    tree2D.build_tree(points);
    tree2D.print_leaf();
    cout << "\nresult from (0,1) to (5,5)"<<endl;
    tree2D.range_query({0,1}, {5,5});
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

    //profe_test();

    profe_test2d();

    return 0;
}
// Cope and Page
