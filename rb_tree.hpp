#ifndef RB_TREE_HPP
#define RB_TREE_HPP
#include <stdexcept>

template <class T>
class RBTree {
private:
    enum class Color { red, black };
    /* ===== Node ===== */
    class Node {
    public:
        Node *left, *right, *parent;
        Color color;
        Node(Node *left, Node *right, Color color): left(left), right(right), parent(nullptr), color(color){};
        static Node* sentinel(){
            static SentinelNode sentinel;
            static Node* sentinel_ptr(static_cast<Node*>(static_cast<void*>(&sentinel)));
            return sentinel_ptr;
        }
        // TODO: Remove get_val when debugging is complete
        virtual T get_val(){
            throw std::runtime_error("Not an implmentation of Node");
        }
    };
    class SentinelNode: public Node {
    public:
        SentinelNode(): Node(nullptr, nullptr, Color::black) {}
        T get_val() {
            throw std::runtime_error("Accessing sentinel value");
        }
    };
    class ValueNode: public Node {
    private:
        T val;
    public:
        ValueNode(T val): Node(Node::sentinel(), Node::sentinel(), Color::red), val(val){}
        T get_val() {
            return val;
        }
    };
    /* ===== RBT ===== */
    Node* root;

    static Node* rb_insert_fixup(Node* z) { return z; }

    static Node* rb_insert(Node* root, Node* z) {
        if (!root->left) {
            root = z;
        } else if (z->get_val() < root->get_val()) {
            root->left = rb_insert(root->left, z);
            root->left->parent = root;
        } else {
            root->right = rb_insert(root->right, z);
            root->right->parent = root;
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
    RBTree() : root(new SentinelNode()) {}
    void insert(const T& val) {
        Node* z = new ValueNode(val);
        root = rb_insert(root, z);
        root->color = Color::black;
    }
    bool find(const T& val) { return rb_find(root, val); }
};

#endif
