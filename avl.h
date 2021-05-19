//
// Created by Raul.Mosquera on 18/05/2021.
//

#ifndef EDA_TREE_AVL_H
#define EDA_TREE_AVL_H

#include<bits/stdc++.h>

using namespace std;

class Node {
public:
    int key;
    Node *left;
    Node *right;
    int height;
};

class avl {

public:

};

int max(int a, int b);

int height(Node *N) {
    if (N == NULL)
        return 0;

    return N->height;
}

int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

Node *newNode(int key) {
    Node *node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1; // new node is initially
    // added at leaf
    return (node);
}

Node *rightRotation(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;

    x->height = max(height(x->left), height(x->right)) + 1;
    // Return new root
    return x;
}

Node *leftRotation(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;

    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(Node *N) {
    if (N == nullptr)
        return 0;

    return height(N->left) - height(N->right);
}

Node *insert(Node *node, int key) {
    // Normal BST rotation
    if (node == nullptr)
        return (newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys not allowed
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left), height(node->right));

    /* 3. Get the balance factor of this ancestor node to check whether this node became unbalanced */
    int balance = getBalance(node);

    // When unbalanced
    // Case 1: Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotation(node);

    // Case 2: Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotation(node);

    // Case 3: Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotation(node->left);
        return rightRotation(node);
    }

    // Case 4: Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotation(node->right);
        return leftRotation(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

/* Given a non-empty binary search tree,
return the node with minimum key value
found in that tree. Note that the entire
tree does not need to be searched. */
Node *minValueNode(Node *node) {
    Node *current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != nullptr)
        current = current->left;

    return current;
}

Node *deleteNode(Node *root, int key) {

    // BST deletion
    if (root == nullptr)
        return root;

    // If the key to be deleted is smaller
    // than the root's key, then it lies
    // in left subtree
    if (key < root->key)
        root->left = deleteNode(root->left, key);

        // If the key to be deleted is greater
        // than the root's key, then it lies
        // in right subtree
    else if (key > root->key)
        root->right = deleteNode(root->right, key);

        // if key is same as root's key, then
        // This is the node to be deleted
    else {
        // node with only one child or no child
        if ((root->left == nullptr) || (root->right == nullptr)) {

            Node *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else // One child case
                *root = *temp; // Copy the contents of
            // the non-empty child
            free(temp);
        } else {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            Node *temp = minValueNode(root->right);

            // Copy the inorder successor's
            // data to this node
            root->key = temp->key;
            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node
    // then return
    if (root == nullptr)
        return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left), height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF
    // THIS NODE (to check whether this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced,
    // then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotation(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotation(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }
    return root;
}

void print_preOrder(Node *root) {
    if (root != nullptr) {
        cout << root->key << " ";
        print_preOrder(root->left);
        print_preOrder(root->right);
    }
}

void print_tree(Node* root, int nro=0)
{
    int i;
    if(root==NULL)return;
    print_tree(root->right,nro+4);
    for(i=0;i<nro;i++)
        cout<<" ";
    cout<<root->key<<endl;
    print_tree(root->left,nro+4);
}

#endif //EDA_TREE_AVL_H
