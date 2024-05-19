#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "Sourse.h"

template <typename Td, typename Tk>
class RBTree : public BST<Td, Tk>
{
public:
    bool InsertByKey(Td data, Tk key);
    bool DeleteByKey(Tk key);

    using BST<Td, Tk>::root;
    using BST<Td, Tk>::sizeT;
    using BST<Td, Tk>::Counter;
    RBTree() : BST<Td, Tk>() {} // default constructor
    RBTree(const RBTree<Td, Tk> &other) : BST<Td, Tk>(other)
    {
        this->copyTree(other.root, this->root, nullptr);
    } // added this constructor

    RBTree(const BST<int, int> &other) : BST<int, int>()
    {
        this->copyTree(other.root, this->root, nullptr);
    }

private:
    void LeftRotate(typename BST<Td, Tk>::Node *&root, typename BST<Td, Tk>::Node *x);
    void RightRotate(typename BST<Td, Tk>::Node *&root, typename BST<Td, Tk>::Node *y);
    void InsertFixup(typename BST<Td, Tk>::Node *&root, typename BST<Td, Tk>::Node *z);
    void DeleteFixup(typename BST<Td, Tk>::Node *&root, typename BST<Td, Tk>::Node *x);
    void Transplant(typename BST<Td, Tk>::Node *&root, typename BST<Td, Tk>::Node *u, typename BST<Td, Tk>::Node *v);
    typename BST<Td, Tk>::Node *Minimum(typename BST<Td, Tk>::Node *node);
    // void copyTree(typename BST<Td, Tk>::Node *sourceNode, typename BST<Td, Tk>::Node *&destNode);
    void copyTree(const typename BST<Td, Tk>::Node *sourceNode, typename BST<Td, Tk>::Node *&destNode, typename BST<Td, Tk>::Node *destParent)
    {
        if (sourceNode == nullptr)
        {
            destNode = nullptr;
        }
        else
        {
            destNode = new typename BST<Td, Tk>::Node(*sourceNode);
            destNode->parent = destParent;
            copyTree(sourceNode->left, destNode->left, destNode);
            copyTree(sourceNode->right, destNode->right, destNode);
        }
    }
};

template <typename Td, typename Tk>
bool RBTree<Td, Tk>::InsertByKey(Td data, Tk key)
{
    auto z = new typename BST<Td, Tk>::Node(data, key);
    z->left = this->tnil;
    z->right = this->tnil;

    auto y = this->tnil;
    auto x = this->root;

    if (this->tnil != nullptr)
    {
        while (x != this->tnil)
        {
            y = x;
            if (z->key < x->key)
            {
                Counter++;
                x = x->left;
            }
            else
            {
                Counter++;
                x = x->right;
            }
        }
    }

    z->parent = y;
    if (this->tnil != nullptr)
    {
        if (y == this->tnil)
        {
            this->root = z;
        }
        else if (z->key < y->key)
        {
            Counter++;
            y->left = z;
        }
        else
        {
            Counter++;
            y->right = z;
        }
    }

    z->color = true; // RED
    InsertFixup(this->root, z);
    this->sizeT++;
    return true;
}

template <typename Td, typename Tk>
void RBTree<Td, Tk>::InsertFixup(typename BST<Td, Tk>::Node *&root, typename BST<Td, Tk>::Node *z)
{
    if (z->parent != nullptr)
    {
        while (z->parent->color == true)
        {
            if (z->parent == z->parent->parent->left)
            {
                auto y = z->parent->parent->right;
                if (y->color == true)
                {
                    z->parent->color = false;
                    y->color = false;
                    z->parent->parent->color = true;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        LeftRotate(root, z);
                    }
                    z->parent->color = false;
                    z->parent->parent->color = true;
                    RightRotate(root, z->parent->parent);
                }
            }
            else
            {
                auto y = z->parent->parent->left;
                if (y->color == true)
                {
                    z->parent->color = false;
                    y->color = false;
                    z->parent->parent->color = true;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        RightRotate(root, z);
                    }
                    z->parent->color = false;
                    z->parent->parent->color = true;
                    LeftRotate(root, z->parent->parent);
                }
            }
        }

        root->color = false;
    }
}

template <typename Td, typename Tk>
typename BST<Td, Tk>::Node *RBTree<Td, Tk>::Minimum(typename BST<Td, Tk>::Node *node)
{
    if (this->tnil != nullptr)
    {
        while (node->left != this->tnil)
        {
            node = node->left;
        }
        return node;
    }
}

template <typename Td, typename Tk>
void RBTree<Td, Tk>::Transplant(typename BST<Td, Tk>::Node *&root, typename BST<Td, Tk>::Node *u, typename BST<Td, Tk>::Node *v)
{
    if (this->tnil != nullptr)
    {
        if (u->parent == this->tnil)
        {
            root = v;
        }
        else if (u == u->parent->left)
        {
            Counter++;
            u->parent->left = v;
        }
        else
        {
            Counter++;
            u->parent->right = v;
        }
        v->parent = u->parent;
    }
}

template <typename Td, typename Tk>
bool RBTree<Td, Tk>::DeleteByKey(Tk key)
{
    auto z = this->root;
    if (this->tnil != nullptr)
    {
        while (z != this->tnil && z->key != key)
        {
            if (key < z->key)
            {
                Counter++;
                z = z->left;
            }
            else
            {
                Counter++;
                z = z->right;
            }
        }
    }
    if (this->tnil != nullptr)
    {
        if (z == this->tnil)
            return false;
    }

    auto y = z;
    auto x = this->tnil;
    if (y != nullptr)
    {
        bool yOriginalColor = y->color;
        if (this->tnil != nullptr)
        {
            if (z->left == this->tnil)
            {
                Counter++;
                x = z->right;
                Transplant(this->root, z, z->right);
            }
            else if (z->right == this->tnil)
            {
                Counter++;
                x = z->left;
                Transplant(this->root, z, z->left);
            }
            else
            {
                y = Minimum(z->right);
                yOriginalColor = y->color;
                x = y->right;
                Counter++;
                if (y->parent == z)
                {
                    x->parent = y;
                }
                else
                {
                    Transplant(this->root, y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }
                Transplant(this->root, z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }
        }
        if (yOriginalColor == false)
        {
            DeleteFixup(this->root, x);
        }
    }
    delete z;
    this->sizeT--;
    return true;
}

template <typename Td, typename Tk>
void RBTree<Td, Tk>::DeleteFixup(typename BST<Td, Tk>::Node *&root, typename BST<Td, Tk>::Node *x)
{
    while (x != root && x->color == false)
    {
        if (x == x->parent->left)
        {
            auto w = x->parent->right;
            if (w->color == true)
            {
                w->color = false;
                x->parent->color = true;
                LeftRotate(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == false && w->right->color == false)
            {
                w->color = true;
                x = x->parent;
            }
            else
            {
                if (w->right->color == false)
                {
                    w->left->color = false;
                    w->color = true;
                    RightRotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = false;
                w->right->color = false;
                LeftRotate(root, x->parent);
                x = root;
            }
        }
        else
        {
            auto w = x->parent->left;
            if (w->color == true)
            {
                w->color = false;
                x->parent->color = true;
                RightRotate(root, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == false && w->left->color == false)
            {
                w->color = true;
                x = x->parent;
            }
            else
            {
                if (w->left->color == false)
                {
                    w->right->color = false;
                    w->color = true;
                    LeftRotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = false;
                w->left->color = false;
                RightRotate(root, x->parent);
                x = root;
            }
        }
    }
    x->color = false;
}

template <typename Td, typename Tk>
void RBTree<Td, Tk>::RightRotate(typename BST<Td, Tk>::Node *&root, typename BST<Td, Tk>::Node *y)
{
    auto x = y->left;
    y->left = x->right;
    if (this->tnil != nullptr)
    {
        if (x->right != this->tnil)
        {
            x->right->parent = y;
        }
    }
    x->parent = y->parent;
    if (this->tnil != nullptr)
    {
        if (y->parent == this->tnil)
        {
            root = x;
        }
    }
    else if (y == y->parent->right)
    {
        y->parent->right = x;
    }
    else
    {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

template <typename Td, typename Tk>
void RBTree<Td, Tk>::LeftRotate(typename BST<Td, Tk>::Node *&root, typename BST<Td, Tk>::Node *x)
{
    auto y = x->right;
    x->right = y->left;
    if (this->tnil != nullptr)
    {
        if (y->left != this->tnil)
        {
            y->left->parent = x;
        }
    }
    y->parent = x->parent;
    if (this->tnil != nullptr)
    {
        if (x->parent == this->tnil)
        {
            root = y;
        }

        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
    }
    y->left = x;
    x->parent = y;
}