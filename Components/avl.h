//
// Created by Raul.Mosquera on 18/05/2021.
//

#ifndef EDA_TREE_AVL_H
#define EDA_TREE_AVL_H

#include<bits/stdc++.h>

using namespace std;

class Node1D {
public:
    int key;
    Node1D *left;
    Node1D *right;
    int height;
};

class avl {

public:

};

int max(int a, int b);

int height(Node1D *N) {
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

Node1D *newNode(int key) {
    Node1D *node = new Node1D();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return (node);
}

Node1D *rightRotation(Node1D *y) {
    Node1D *x = y->left;
    Node1D *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node1D *leftRotation(Node1D *x) {
    Node1D *y = x->right;
    Node1D *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(Node1D *N) {
    if (N == nullptr) {return 0;}
    return height(N->left) - height(N->right);
}

Node1D *insert(Node1D *node, int key) {
    if (node == nullptr)
        return (newNode(key));

    if (key < node->key) node->left = insert(node->left, key);
    else if (key >= node->key)  node->right = insert(node->right, key);
    else return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotation(node);

    if (balance < -1 && key > node->right->key)
        return leftRotation(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotation(node->left);
        return rightRotation(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotation(node->right);
        return leftRotation(node);
    }

    return node;
}

Node1D *minValueNode(Node1D *node) {
    Node1D *current = node;

    while (current->left != nullptr)
        current = current->left;

    return current;
}

Node1D *deleteNode(Node1D *root, int key) {

    if (root == nullptr) { return root; }

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node1D *temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;
            free(temp);
        } else {
            Node1D *temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    if (root == nullptr) { return root; }
     root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotation(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotation(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }
    return root;
}

void print_preOrder(Node1D *root) {
    if (root != nullptr) {
        cout << root->key << " ";
        print_preOrder(root->left);
        print_preOrder(root->right);
    }
}

void print_tree(Node1D* root, int nro=0)
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
