#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdexcept>

#pragma warning(disable:4996)

using namespace std;

enum Color { RED, BLACK };

template<typename Tk, typename Td>
struct Node {
    Tk key;
    Td data;
    Color color;
    Node* left, * right, * parent;

    Node(Tk key, Td data) : key(key), data(data) {
        parent = left = right = nullptr;
        color = RED;
    }
};

template<typename Tk, typename Td>
class RBTree {
private:
    Node<Tk, Td>* root;
    Node<Tk, Td>* TNULL;

    void initializeNULLNode(Node<Tk, Td>* node, Node<Tk, Td>* parent) {
        node->key = 0;
        node->data = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = BLACK;
    }

    void preOrderHelper(Node<Tk, Td>* node) {
        if (node != TNULL) {
            cout << node->key << " ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    void inOrderHelper(Node<Tk, Td>* node) {
        if (node != TNULL) {
            inOrderHelper(node->left);
            cout << node->key << " ";
            inOrderHelper(node->right);
        }
    }

    void postOrderHelper(Node<Tk, Td>* node) {
        if (node != TNULL) {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            cout << node->key << " ";
        }
    }

    Node<Tk, Td>* searchTreeHelper(Node<Tk, Td>* node, Tk key) {
        while (node != TNULL && key != node->key) {
            if (key < node->key) {
                node = node->left;
            }
            else {
                node = node->right;
            }
        }
        return node;
    }

    void fixDelete(Node<Tk, Td>* x) {
        Node<Tk, Td>* s;
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == BLACK && s->right->color == BLACK) {
                    s->color = RED;
                    x = x->parent;
                }
                else {
                    if (s->right->color == BLACK) {
                        s->left->color = BLACK;
                        s->color = RED;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else {
                s = x->parent->left;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == BLACK && s->right->color == BLACK) {
                    s->color = RED;
                    x = x->parent;
                }
                else {
                    if (s->left->color == BLACK) {
                        s->right->color = BLACK;
                        s->color = RED;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    void rbTransplant(Node<Tk, Td>* u, Node<Tk, Td>* v) {
        if (u->parent == nullptr) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNodeHelper(Node<Tk, Td>* node, Tk key) {
        Node<Tk, Td>* z = TNULL;
        Node<Tk, Td>* x, * y;
        while (node != TNULL) {
            if (node->key == key) {
                z = node;
            }

            if (node->key <= key) {
                node = node->right;
            }
            else {
                node = node->left;
            }
        }

        if (z == TNULL) {
            cout << "Key not found in the tree" << endl;
            return;
        }

        y = z;
        Color y_original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == TNULL) {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            }
            else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == BLACK) {
            fixDelete(x);
        }
    }

    void fixInsert(Node<Tk, Td>* k) {
        Node<Tk, Td>* u;
        while (k->parent->color == RED) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            }
            else {
                u = k->parent->parent->right;

                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = BLACK;
    }

    void printHelper(Node<Tk, Td>* root, string indent, bool last) {
        if (root != TNULL) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            }
            else {
                cout << "L----";
                indent += "|  ";
            }

            string sColor = root->color ? "RED" : "BLACK";
            cout << root->key << "(" << sColor << ")" << endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

public:
    RBTree() {
        TNULL = new Node<Tk, Td>(0, 0);
        TNULL->color = BLACK;
        root = TNULL;
    }

    void preorder() {
        preOrderHelper(this->root);
    }

    void inorder() {
        inOrderHelper(this->root);
    }

    void postorder() {
        postOrderHelper(this->root);
    }

    Node<Tk, Td>* searchTree(Tk k) {
        return searchTreeHelper(this->root, k);
    }

    Node<Tk, Td>* minimum(Node<Tk, Td>* node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    Node<Tk, Td>* maximum(Node<Tk, Td>* node) {
        while (node->right != TNULL) {
            node = node->right;
        }
        return node;
    }

    Node<Tk, Td>* successor(Node<Tk, Td>* x) {
        if (x->right != TNULL) {
            return minimum(x->right);
        }

        Node<Tk, Td>* y = x->parent;
        while (y != TNULL && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    Node<Tk, Td>* predecessor(Node<Tk, Td>* x) {
        if (x->left != TNULL) {
            return maximum(x->left);
        }

        Node<Tk, Td>* y = x->parent;
        while (y != TNULL && x == y->left) {
            x = y;
            y = y->parent;
        }

        return y;
    }

    void leftRotate(Node<Tk, Td>* x) {
        Node<Tk, Td>* y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node<Tk, Td>* x) {
        Node<Tk, Td>* y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void insert(Tk key, Td data) {
        Node<Tk, Td>* node = new Node<Tk, Td>(key, data);
        node->parent = nullptr;
        node->left = TNULL;
        node->right = TNULL;
        node->color = RED;

        Node<Tk, Td>* y = nullptr;
        Node<Tk, Td>* x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->key < x->key) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        }
        else if (node->key < y->key) {
            y->left = node;
        }
        else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = BLACK;
            return;
        }

        if (node->grandparent() == nullptr) {
            return;
        }

        fixInsert(node);
    }

    Node<Tk, Td>* getRoot() {
        return this->root;
    }

    void deleteNode(Tk key) {
        deleteNodeHelper(this->root, key);
    }

    void printTree() {
        if (root) {
            printHelper(this->root, "", true);
        }
    }
};

int main() {
    RBTree<int, int> tree;

    tree.insert(8, 8);
    tree.insert(18, 18);
    tree.insert(5, 5);
    tree.insert(15, 15);
    tree.insert(17, 17);
    tree.insert(25, 25);
    tree.insert(40, 40);
    tree.insert(80, 80);

    tree.printTree();
    cout << endl << "After deleting" << endl;
    tree.deleteNode(25);
    tree.printTree();

    return 0;
}

