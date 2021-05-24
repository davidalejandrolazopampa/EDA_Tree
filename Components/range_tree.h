//
// Created by Raul.Mosquera on 18/05/2021.
//

#ifndef EDA_TREE_RANGE_TREE_H
#define EDA_TREE_RANGE_TREE_H
#include<iostream>
#include<fstream>
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
        node->height = 1;
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

    vector<coordinate> search1Drange(int begin, int end) {

        return this->one_d_range_query(begin, end);
    }

    void print_preOrder() {
        this->_print_preOrder(this->root);
    }

    void print_tree() {
        this->_print_tree(this->root);
    }

    vector<coordinate> print_leaf() {
        return this->_print_leaf(this->root);
    }

private:

    vector<coordinate> one_d_range_query(int x_begin, int x_end) {
        vector<coordinate> result;

        auto splitNode = this->find_split_node(x_begin, x_end);

        result.clear();

        if (splitNode->height == 1) {//leaf
            if(x_begin <= splitNode->key && splitNode->key <= x_end) {
                cout << splitNode->data.first << " " << splitNode->data.second << endl;
                result.emplace_back(splitNode->data.first, splitNode->data.second);
            }

        } else {
            auto nodeTmp = splitNode->left;
            while (nodeTmp->height != 1) {
                if(x_begin <= nodeTmp->key) {
                    auto resultLeaf = this->_print_leaf(nodeTmp->right, true);
                    result.insert(end(result), begin(resultLeaf), end(resultLeaf));

                    nodeTmp = nodeTmp->left;
                } else {
                    nodeTmp = nodeTmp->right;
                }
            }
            if(x_begin <= nodeTmp->key && nodeTmp->key <= x_end) {
                cout << nodeTmp->data.first << " " << nodeTmp->data.second << endl;
                result.emplace_back(nodeTmp->data.first, nodeTmp->data.second);
            }

            nodeTmp = splitNode->right;
            while (nodeTmp->height != 1) {
                if(nodeTmp->key <= x_end) {
                    auto resultLeaf = this->_print_leaf(nodeTmp->left, true);
                    result.insert(end(result), begin(resultLeaf), end(resultLeaf));

                    nodeTmp = nodeTmp->right;
                } else {
                    nodeTmp = nodeTmp->left;
                }
            }
            if(x_begin <= nodeTmp->key && nodeTmp->key <= x_end) {
                cout << nodeTmp->data.first << " " << nodeTmp->data.second << endl;
                result.emplace_back(nodeTmp->data.first, nodeTmp->data.second);
            }
        }

        return result;
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

        if (node == nullptr)
            return (Node1D::newNode(key, data));

        if (key < node->key) {
            node->left = this->_insert(node->left, key, data);

            if (node->left->left == nullptr)
                node->left->left = Node1D::newNode(key, data);

            node->left->height = 1 + max(height(node->left->left), height(node->left->right));

            node->height = 1 + max(height(node->left), height(node->right));

        } else if (key >= node->key) {
            node->right = this->_insert(node->right, key, data);

            if (node->left == nullptr) { node->left = Node1D::newNode(node->key, node->data); }

            node->height = 1 + max(height(node->left), height(node->right));
        }

        int balance = getBalance(node);

        if (balance > 1 && key <= node->left->key) { return rightRotation(node); }

        if (balance < -1 && key > node->right->key) { return leftRotation(node); }

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

    vector<coordinate> _print_leaf(Node1D *node, bool new_line=false) {

        vector<coordinate> result;

        if (node != nullptr) {
            if (node->height == 1)
                if(new_line) {
                    cout << node->data.first << " " << node->data.second << endl;
                    result.push_back({node->data.first, node->data.second});
                } else {
                    cout << node->data.first << " "<<node->data.second << " ";
                    result.push_back({node->data.first, node->data.second});
                }

            auto resultL = _print_leaf(node->left, new_line);
            auto resultR = _print_leaf(node->right, new_line);

            result.insert(end(result), begin(resultL), end(resultL));
            result.insert(end(result), begin(resultR), end(resultR));
        }

        return result;
    }
};


#endif //EDA_TREE_RANGE_TREE_H
