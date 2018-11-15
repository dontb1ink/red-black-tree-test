#ifndef RB_TREE_HPP
#define RB_TREE_HPP
#include <iostream>
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
        Node(Node* left, Node* right, Color color) : left(left), right(right), parent(nullptr), color(color){};
        static Node* sentinel() {
            static SentinelNode sentinel;
            static Node* sentinel_ptr(static_cast<Node*>(static_cast<void*>(&sentinel)));
            return sentinel_ptr;
        }
        // TODO: Remove get_val when debugging is complete
        virtual T get_val() { throw std::runtime_error("Not an implmentation of Node"); }
        virtual void set_val(const T val) { throw std::runtime_error("Not an implmentation of Node"); }
    };
    class SentinelNode : public Node {
    public:
        SentinelNode() : Node(nullptr, nullptr, Color::black) {}
        T get_val() { throw std::runtime_error("Accessing sentinel value"); }
        void set_val(const T val) { throw std::runtime_error("Setting sentinel value"); }
    };
    class ValueNode : public Node {
    private:
        T val;

    public:
        ValueNode(T val) : Node(Node::sentinel(), Node::sentinel(), Color::red), val(val) {}
        T get_val() { return val; }
        void set_val(const T val) { this->val = val; }
    };
    /* ===== RBT ===== */
    Node* root;

    static Node* rb_insert_fixup_case1(Node* grandparent, Node* parent, Node* child) {
        grandparent->left = parent->right;
        grandparent->left->parent = grandparent;
        parent->right = grandparent;
        parent->right->parent = parent;
        grandparent->color = Color::red;
        parent->color = Color::black;
        return parent;
    }
    static Node* rb_insert_fixup_case2(Node* grandparent, Node* parent, Node* child) {
        grandparent->left = Node::sentinel();
        parent->right = Node::sentinel();
        child->left = parent;
        child->left->parent = child;
        child->right = grandparent;
        child->right->parent = child;
        grandparent->color = Color::red;
        child->color = Color::black;
        return child;
    }
    static Node* rb_insert_fixup_case3(Node* grandparent, Node* parent, Node* child) {
        grandparent->right = parent->left;
        grandparent->right->parent = grandparent;
        parent->left = grandparent;
        parent->left->parent = parent;
        grandparent->color = Color::red;
        parent->color = Color::black;
        return parent;
    }
    static Node* rb_insert_fixup_case4(Node* grandparent, Node* parent, Node* child) {
        grandparent->right = Node::sentinel();
        parent->left = Node::sentinel();
        child->right = parent;
        child->right->parent = child;
        child->left = grandparent;
        child->left->parent = child;
        grandparent->color = Color::red;
        parent->color = Color::black;
        return child;
    }
    static Node* rb_insert_fixup_case5(Node* grandparent, Node* parent, Node* uncle) {
        grandparent->color = Color::red;
        parent->color = Color::black;
        uncle->color = Color::black;
        return grandparent;
    }
    static Node* rb_insert_fixup_left(Node* grandparent) {
        Node* parent(grandparent->left);
        Node* uncle(grandparent->right);
        if (parent->color == Color::black) {
            return grandparent;
        } else if (parent->left->color == Color::red) {
            if (uncle->color == Color::red) {
                return rb_insert_fixup_case5(grandparent, parent, uncle);
            }
            return rb_insert_fixup_case1(grandparent, parent, parent->left);
        } else if (parent->right->color == Color::red) {
            if (uncle->color == Color::red) {
                return rb_insert_fixup_case5(grandparent, parent, uncle);
            }
            return rb_insert_fixup_case2(grandparent, parent, parent->right);
        } else {
            return grandparent;
        }
    }
    static Node* rb_insert_fixup_right(Node* grandparent) {
        Node* parent(grandparent->right);
        Node* uncle(grandparent->left);
        if (parent->color == Color::black) {
            return grandparent;
        } else if (parent->left->color == Color::red) {
            if (uncle->color == Color::red) {
                return rb_insert_fixup_case5(grandparent, parent, uncle);
            }
            return rb_insert_fixup_case4(grandparent, parent, parent->left);
        } else if (parent->right->color == Color::red) {
            if (uncle->color == Color::red) {
                return rb_insert_fixup_case5(grandparent, parent, uncle);
            }
            return rb_insert_fixup_case3(grandparent, parent, parent->right);
        } else {
            return grandparent;
        }
    }

    static Node* rb_insert(Node* root, Node* z) {
        if (!root->left) {
            root = z;
        } else if (z->get_val() < root->get_val()) {
            root->left = rb_insert(root->left, z);
            root->left->parent = root;
            root = rb_insert_fixup_left(root);
        } else {
            root->right = rb_insert(root->right, z);
            root->right->parent = root;
            root = rb_insert_fixup_right(root);
        }
        return root;
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
    /* ===== Delete ===== */
    static Node* rb_delete(Node* root, const T& val) {
        if (!root->left) {
            // pass
        } else if (val < root->get_val()) {
            root->left = rb_delete(root->left, val);
            root->left->parent = root;
        } else if (val > root->get_val()) {
            root->right = rb_delete(root->right, val);
            root->right->parent = root;
        } else {
            if (!root->left->left) {
                root->right->parent = root->parent;
                root = root->right;
            } else if (!root->right->left) {
                root->left->parent = root->parent;
                root = root->left;
            } else {
                Node* target = root->left;
                while (target->right->left) {
                    target = target->right;
                }
                if (target->parent->left == target) {
                    target->parent->left = target->left;
                } else {
                    target->parent->right = target->left;
                }
                root->set_val(target->get_val());
            }
        }
        return root;
    }

public:
    RBTree() : root(new SentinelNode()) {}
    void insert(const T& val) {
        Node* z = new ValueNode(val);
        root = rb_insert(root, z);

        root->color = Color::black;
    }
    bool find(const T& val) { return rb_find(root, val); }
    void remove(const T& val) { root = rb_delete(root, val); }
};

#endif
