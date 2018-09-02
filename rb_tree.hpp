#ifndef RB_TREE_HPP
#define RB_TREE_HPP
#include <stdexcept>

template <class T>
class RBTree {
private:
    enum class Color { red, black };

    class Node {
    private:
        T val;
        bool is_sentinel;

    public:
        Node *left, *right, *parent;
        Color color;

        Node(T val) : val(val), is_sentinel(false), left(new Node()), right(new Node()), color(Color::red) {}
        Node() : is_sentinel(true), left(nullptr), right(nullptr), color(Color::black) {}
        T get_val() {
            if (is_sentinel) {
                throw std::runtime_error("Accessing sentinel value");
            }
            return val;
        }
    };

    Node* root;

    static Node* rb_insert_fixup(Node* grandparent) {
        /* No fixup */
        return grandparent;
    }

    static Node* rb_insert(Node* root, Node* z) {
        if (!root->left) {
            root = z;
        } else if (z->get_val() < root->get_val()) {
            root->left = rb_insert(root->left, z);
        } else {
            root->right = rb_insert(root->right, z);
        }
        return rb_insert_fixup(root);
    }
    static bool rb_find(Node* root, const T& val) {
        if (!root->left) {
            return false;
        } else if (val < root->get_val()) {
            return rb_find(root->left, val);
        } else if (val > root->get_val()) {
            return rb_find(root->right, val);
        } else {
            return true;
        }
    }

public:
    RBTree() : root(new Node()) {}
    void insert(const T& val) {
        Node* z = new Node(val);
        root = rb_insert(root, z);
    }
    bool find(const T& val) { return rb_find(root, val); }
};

#endif
