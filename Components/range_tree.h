//
// Created by Raul.Mosquera on 18/05/2021.
//

#ifndef EDA_TREE_RANGE_TREE_H
#define EDA_TREE_RANGE_TREE_H

#include<bits/stdc++.h>

using namespace std;

typedef pair<int, int> coordinate;

class Node1D {
public:
    int key;
    Node1D *left;
    Node1D *right;
    int height;
    coordinate data;

    static Node1D *newNode(int key, coordinate data) {
        Node1D *node = new Node1D();
        node->key = key;
        node->data = data;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1; // new node is initially
        return (node);
    }
};

class rangeTree {

public:
    Node1D *root = nullptr;

    rangeTree() {
        root = nullptr;
    }

    void insert(int key, coordinate data) {
        this->root = _insert(this->root, key, data);
    }

    void search1Drange(int begin, int end) {

        this->one_d_range_query(begin, end);
    }

    void print_preOrder() {
        this->_print_preOrder(this->root);
    }

    void print_tree() {
        this->_print_tree(this->root);
    }

    void print_leaf() {
        this->_print_leaf(this->root);
    }

private:

    void one_d_range_query(int begin, int end) {
        auto splitNode = this->find_split_node(begin, end);

        if (splitNode->height == 1) {//leaf
            if(begin <= splitNode->key && splitNode->key <= end)
                cout << splitNode->key << endl;

        } else {
            auto nodeTmp = splitNode->left;
            while (nodeTmp->height != 1) {
                if( begin <= nodeTmp->key) {
                    this->_print_leaf(nodeTmp->right, true);
                    nodeTmp = nodeTmp->left;
                } else {
                    nodeTmp = nodeTmp->right;
                }
            }
            if(begin <= nodeTmp->key && nodeTmp->key <= end)
                cout << nodeTmp->key << endl;

            nodeTmp = splitNode->right;
            while (nodeTmp->height != 1) {
                if( nodeTmp->key <= end) {
                    this->_print_leaf(nodeTmp->left, true);
                    nodeTmp = nodeTmp->right;
                } else {
                    nodeTmp = nodeTmp->left;
                }
            }
            if(begin <= nodeTmp->key && nodeTmp->key <= end)
                cout << nodeTmp->key << endl;
        }
    }

    Node1D *find_split_node(int begin, int end) {
        auto nodeTmp = this->root;

        while (nodeTmp->height != 1 && (end <= nodeTmp->key || begin > nodeTmp->key)) {
            if (end <= nodeTmp->key)
                nodeTmp = nodeTmp->left;
            else
                nodeTmp = nodeTmp->right;
        }

        return nodeTmp;
    }

    Node1D *rightRotation(Node1D *y) {
        Node1D *x = y->left;
        Node1D *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;

        x->height = max(height(x->left), height(x->right)) + 1;
        // Return new root

        return x;
    }

    Node1D *leftRotation(Node1D *x) {
        Node1D *y = x->right;
        Node1D *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = max(height(x->left), height(x->right)) + 1;

        y->height = max(height(y->left), height(y->right)) + 1;

        // Return new root
        return y;
    }

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

    int getBalance(Node1D *N) {
        if (N == nullptr)
            return 0;

        return height(N->left) - height(N->right);
    }

    Node1D *_insert(Node1D *node, int key, coordinate data) {
        // Normal BST rotation
        if (node == nullptr)
            return (Node1D::newNode(key, data));

        if (key < node->key) {
            node->left = this->_insert(node->left, key, data);

            //node->left->left = newNode(key);
            if (node->left->left == nullptr)
                node->left->left = Node1D::newNode(key, data);

            //node->left->height = 2;
            node->left->height = 1 + max(height(node->left->left), height(node->left->right));
            //node->height = 3;
            node->height = 1 + max(height(node->left), height(node->right));

        } else if (key >= node->key) {
            node->right = this->_insert(node->right, key, data);

            if (node->left == nullptr)                   //for range tree
                node->left = Node1D::newNode(node->key, data);

            node->height = 1 + max(height(node->left), height(node->right));
        }

        // Get the balance factor of this ancestor node to check whether this node became unbalanced
        int balance = getBalance(node);

        // When unbalanced
        // Case 1: Left Left Case
        //if (balance > 1 && key < node->left->key)
        if (balance > 1 && key <= node->left->key)
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

        return node;
    }

    // Note that the entire tree does not need to be searched.
    Node1D *minValueNode(Node1D *node) {
        Node1D *current = node;

        /* loop down to find the leftmost leaf */
        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    Node1D *_deleteNode(Node1D *root, int key) {

        // BST deletion
        if (root == nullptr)
            return root;

        // If the key to be deleted is smaller
        // than the root's key, then it lies
        // in left subtree
        if (key < root->key)
            root->left = _deleteNode(root->left, key);

            // If the key to be deleted is greater
            // than the root's key, then it lies
            // in right subtree
        else if (key > root->key)
            root->right = _deleteNode(root->right, key);

            // if key is same as root's key, then
            // This is the node to be deleted
        else {
            // node with only one child or no child
            if ((root->left == nullptr) || (root->right == nullptr)) {

                Node1D *temp = root->left ? root->left : root->right;

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
                Node1D *temp = minValueNode(root->right);

                // Copy the inorder successor's
                // data to this node
                root->key = temp->key;
                // Delete the inorder successor
                root->right = _deleteNode(root->right, temp->key);
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

    void _print_preOrder(Node1D *root) {
        if (root != nullptr) {
            cout << root->key << " ";
            _print_preOrder(root->left);
            _print_preOrder(root->right);
        }
    }

    void _print_tree(Node1D *root, int nro = 0) {
        int i;
        if (root == NULL)return;
        _print_tree(root->right, nro + 4);
        for (i = 0; i < nro; i++)
            cout << " ";
        cout << root->key << endl;
        _print_tree(root->left, nro + 4);
    }

    void _print_leaf(Node1D *node, bool new_line=false) {

        if (node != nullptr) {
            if (node->height == 1)
                if(new_line)
                    cout << "("<< node->data.first << "," << node->data.second << ")"<< endl;
                else
                    cout << "("<< node->data.first << ","<<node->data.second << ")" << " ";

            _print_leaf(node->left, new_line);
            _print_leaf(node->right, new_line);
        }
    }
};


#endif //EDA_TREE_RANGE_TREE_H