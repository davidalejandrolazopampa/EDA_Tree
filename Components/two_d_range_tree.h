//
// Created by Raul.Mosquera on 23/05/2021.
//

#ifndef EDA_TREE_TWO_D_RANGE_TREE_H
#define EDA_TREE_TWO_D_RANGE_TREE_H

#include "range_tree.h"

bool cmpCoordinateX (coordinate l, coordinate r) {
    return (l.first < r.first);
}

class Node2D {
public:
    int key;
    Node2D *left;
    Node2D *right;
    int height;
    coordinate data;
    rangeTree t_associated;

    static Node2D *newNode(int key, coordinate data) {
        auto *node = new Node2D();
        node->key = key;
        node->data = data;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1; // new node is initially
        return (node);
    }
};

class two_d_range_tree {
public:
    Node2D *root = nullptr;

    vector<coordinate> range_query(coordinate begin2d, coordinate end2d) {
        vector<coordinate> result;
        vector<coordinate> result1D;
        auto xbegin = begin2d.first;
        auto xend = end2d.first;
        auto ybegin = begin2d.second;
        auto yend = end2d.second;

        auto splitNode = this->find_split_node(xbegin, xend);

        result.clear();
        if (splitNode->height == 1) {//leaf
            if (xbegin <= splitNode->data.first && splitNode->data.first <= xend) {
                cout << splitNode->data.first << " " << splitNode->data.second << endl;
                result.emplace_back(splitNode->data.first, splitNode->data.second);
            }
        } else {
            auto nodeTmp = splitNode->left;
            while (nodeTmp->height != 1) {
                if (xbegin <= nodeTmp->key) {
                    //this->_print_leaf(nodeTmp->right, true);
                    auto t_right = nodeTmp->right->t_associated;
                    auto result1DTmp = t_right.search1Drange(ybegin, yend);

                    result1D.insert(end(result1D), begin(result1DTmp), end(result1DTmp));

                    nodeTmp = nodeTmp->left;
                } else {
                    nodeTmp = nodeTmp->right;
                }
            }
            if (xbegin <= nodeTmp->data.first && nodeTmp->data.first <= xend
                && ybegin <= nodeTmp->data.second && nodeTmp->data.second <= yend) {
                cout << nodeTmp->data.first << " " << nodeTmp->data.second << endl;
                result.emplace_back(nodeTmp->data.first, nodeTmp->data.second);
            }

            nodeTmp = splitNode->right;
            while (nodeTmp->height != 1) {
                if (nodeTmp->key <= xend) {
                    //this->_print_leaf(nodeTmp->left, true);
                    auto t_left = nodeTmp->left->t_associated;
                    auto result1DTmp = t_left.search1Drange(ybegin, yend);

                    result1D.insert(end(result1D), begin(result1DTmp), end(result1DTmp));

                    nodeTmp = nodeTmp->right;
                } else {
                    nodeTmp = nodeTmp->left;
                }
            }
            if (xbegin <= nodeTmp->data.first && nodeTmp->data.first <= xend
                && ybegin <= nodeTmp->data.second && nodeTmp->data.second <= yend) {

                cout << nodeTmp->data.first << " " << nodeTmp->data.second << endl;
                result.emplace_back(nodeTmp->data.first, nodeTmp->data.second);
            }
        }

        result.insert(end(result), begin(result1D), end(result1D));

        return result;
    }

    void build_tree(vector<coordinate> points) {
        this->root = this->build(points);
    }

    void print_leaf() {
        this->_print_leaf(this->root);
    }

private:
    Node2D *find_split_node(int begin, int end) {
        auto nodeTmp = this->root;

        while (nodeTmp->height != 1 && (end <= nodeTmp->key || begin > nodeTmp->key)) {
            if (end <= nodeTmp->key)
                nodeTmp = nodeTmp->left;
            else
                nodeTmp = nodeTmp->right;
        }

        return nodeTmp;
    }

    Node2D *build(vector<coordinate> points) {
        rangeTree tree_a;
        Node2D *node;
        int x_med;
        //Add Y coordinate
        for (auto point: points) {
            auto y = point.second;
            tree_a.insert(y, point);
        }

        if (points.size() == 1) {
            auto point = points.at(0);
            auto x = point.first;
            node = Node2D::newNode(x, point);
            node->t_associated = tree_a;
        } else {
            vector<coordinate> points_left;
            vector<coordinate> points_right;

            if ( points.size() <= 3 ) {
                set<int> tmp;

                for(auto point: points)
                    tmp.insert(point.first);

                if(tmp.size() == 1) { //duplicates
                    auto len = points.size();

                    if (len == 2) {
                        points_left.push_back(points.at(0));
                        points_right.push_back(points.at(1));
                    } else if (len == 3){
                        points_left.push_back(points.at(0));
                        points_left.push_back(points.at(1));
                        points_right.push_back(points.at(2));
                    }

                } else {
                    x_med = this->find_x_median(points);

                    for (auto point: points) {
                        if (point.first <= x_med)
                            points_left.push_back(point);
                        else
                            points_right.push_back(point);
                    }
                }

            } else {
                x_med = this->find_x_median(points);

                for (auto point: points) {
                    if (point.first <= x_med)
                        points_left.push_back(point);
                    else
                        points_right.push_back(point);
                }
            }

            auto node_left = build(points_left);
            auto node_right = build(points_right);

            node = Node2D::newNode(x_med, {x_med, x_med});
            node->left = node_left;
            node->right = node_right;
            node->height = 1 + max(node->left->height, node->right->height);
            node->t_associated = tree_a;
        }

        return node;
    }

    void _print_leaf(Node2D *node, bool new_line = false) {

        if (node != nullptr) {
            if (node->height == 1)
                if (new_line)
                    cout << "(" << node->data.first << "," << node->data.second << ")" << endl;
                else
                    cout << "(" << node->data.first << "," << node->data.second << ")" << " ";

            _print_leaf(node->left, new_line);
            _print_leaf(node->right, new_line);
        }
    }

    int find_x_median(vector<coordinate> points) {
        //auto points_tmp = points;
        //sort(points_tmp.begin(), points_tmp.end(), cmpCoordinateX);

        int n_1;
        int n_plus_1;
        set<int> tmp;

        for(auto elem: points) {
            tmp.insert(elem.first);
        }

        vector<int> points_tmp(tmp.begin(), tmp.end());

        auto n = points_tmp.size();

        if (n % 2 != 0) {
            try {
                return points_tmp.at(ceil(n / 2));
            } catch (const std::out_of_range &oor) {
                std::cerr << "Out of Range error in even" << n << ": " << oor.what() << '\n';
            }
        } else {
            try {
                n_1 = points_tmp.at((n - 1) / 2);
            } catch (const std::out_of_range &oor) {
                std::cerr << "Out of Range error in odd 1" << n << ": " << oor.what() << '\n';
            }
            try {
                n_plus_1 = points_tmp.at(n / 2);
            } catch (const std::out_of_range &oor) {
                std::cerr << "Out of Range error in odd 2" << n << ": " << oor.what() << '\n';
            }

            return ((n_1 + n_plus_1) / 2);
        }
    }
};


#endif //EDA_TREE_TWO_D_RANGE_TREE_H
