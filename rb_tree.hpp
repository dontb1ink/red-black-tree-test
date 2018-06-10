#ifndef RB_TREE_HPP
#define RB_TREE_HPP

template <class T>
class RBTree {
private:
    enum class Color { red, black };

    struct Node {
        Node(T val) : left(sentinel()), right(sentinel()), color(Color::red), val(val) {}
        static Node* sentinel() {
            static unsigned char sentinel[sizeof(Node)] = {0};
            static Node* sentinel_ptr(static_cast<Node*>(static_cast<void*>(&sentinel)));
            return sentinel_ptr;
        }
        Node *left, *right;
        Color color;
        T val;
    };

    Node* root;

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
                parent->right = Node::sentinel();
                grandparent->left = Node::sentinel();
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
                parent->left = Node::sentinel();
                grandparent->right = Node::sentinel();
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
        /* No fixup */
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

    static int rb_height(Node* root) {
        int leftHeight, rightHeight;

        if (!root->left) {
            return -1;
        } else {
            leftHeight = rb_height(root->left);
            rightHeight = rb_height(root->right);
            return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
        }
    }

public:
    RBTree() : root(Node::sentinel()) {
        Node::sentinel()->color = Color::black;
    }
    void insert(const T& val) {
        Node* z = new Node(val);
        root = rb_insert(root, z);
    }
    bool find(const T& val) {
        return rb_find(root, val);
    }
    int height(){
       return rb_height(root);
    }
};

#endif
