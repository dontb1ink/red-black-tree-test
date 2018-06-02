#ifndef RB_TREE_HPP
#define RB_TREE_HPP

template <class T>
class RBTree {
private:
    enum class Color { red, black };

    struct Node {
        Node(T val) : left(new Node()), right(new Node()), color(Color::red), val(val) {}
        Node() : left(nullptr), right(nullptr), color(Color::black) { /* TODO: support no default constructor for T */
        }
        Node *left, *right;
        Color color;
        T val;
    };

    static Node* rb_insert_fixup(Node* grandparent) {
        Node *node, *parent;
        if (grandparent->left->color == Color::red && grandparent->right->color == Color::red) {
            /* case 5 */
            grandparent->color = Color::red;
            grandparent->left->color = Color::black;
            grandparent->right->color = Color::black;
            return grandparent;
        } else if (grandparent->left->color == Color::red) {
            parent = grandparent->left;
            if (parent->left->color == Color::red) {
                /* case 1 */
                node = parent->left;
                grandparent->left = parent->right;
                parent->right = grandparent;
                parent->color = Color::black;
                grandparent->color = Color::red;
                return parent;
            }
            if (parent->right->color == Color::red) {
                /* case 2 */
                node = parent->right;
                parent->right = new Node();
                grandparent->left = new Node();
                node->left = parent;
                node->right = grandparent;
                node->color = Color::black;
                grandparent->color = Color::red;
                return node;
            }
        } else if (grandparent->right->color == Color::red) {
            parent = grandparent->right;
            if (parent->left->color == Color::red) {
                /* case 4 */
                node = parent->left;
                parent->left = new Node();
                grandparent->right = new Node();
                node->left = grandparent;
                node->right = parent;
                node->color = Color::black;
                grandparent->color = Color::red;
                return node;
            }
            if (parent->right->color == Color::red) {
                /* case 3 */
                node = parent->right;
                grandparent->right = parent->left;
                parent->left = grandparent;
                parent->color = Color::black;
                grandparent->color = Color::red;
                return parent;
            }
        }
        /* case 0 */
        return grandparent;
    }

    static Node* rb_insert(Node* root, Node* z) {
        if (!root->left) {
            root = z;
        } else if (z->val < root->val) {
            root->left = rb_insert(root->left, z);
        } else {
            root->right = rb_insert(root->right, z);
        }
        return rb_insert_fixup(root);
    }
    static bool rb_find(Node* root, const T& val) {
        if (!root->left) {
            return false;
        } else if (val < root->val) {
            return rb_find(root->left, val);
        } else if (val > root->val) {
            return rb_find(root->right, val);
        } else {
            return true;
        }
    }
    Node* root;

public:
    RBTree() : root(new Node()) {}
    void insert(const T& val) {
        Node* z = new Node(val);
        root = rb_insert(root, z);
    }
    bool find(const T& val) {
        return rb_find(root, val);
    }
};

#endif
