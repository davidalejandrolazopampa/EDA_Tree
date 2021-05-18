
#include "avl.h"

int main() {
    Node *root = nullptr;

    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);

    cout << "Preorder traversal of the "
            "constructed AVL tree is \n";
    print_preOrder(root);

    root = deleteNode(root, 0);

    cout << "\nPreorder traversal after"
         << " deletion of 10 \n";
    print_preOrder(root);

    return 0;
}
// Cope and Page
