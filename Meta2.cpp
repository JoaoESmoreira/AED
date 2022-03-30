#include <iostream>

class SplayTree {
    struct Node {
        std::string m_name;
        std::string m_hash;
        int         m_value;

        Node *right;
        Node *left;

        Node () : m_name(""), m_hash(""), m_value(0), right(nullptr), left(nullptr) {}
        Node (const std::string &name, const std::string &hash, int value) : m_name(name), m_hash(hash), m_value(value), 
                                                                           right(nullptr), left(nullptr) {}
    };

    Node *m_root;


    void m_free_Splay(Node *node) {
        if (node != nullptr) {
            m_free_Splay(node->left);
            m_free_Splay(node->right);
            delete node;
        }
    }

    // pass to son to zig
    Node* m_zig (Node *node) {
        Node *son  = node->left;

        node->left = son->right;
        son->right = node;

        return son;
    }

    Node* m_zag (Node *node) {
        Node *son   = node->right;

        node->right = son->left;
        son->left   = node;

        return son;
    }

    Node* m_splay(Node *node, const std::string &name) {

        // caso base de estarmos na raiz
        if (m_root->m_name.compare(node->m_name) == 0) {
            // do a zig or a zag rotation
            if (m_root->left != nullptr && name.compare(m_root->left->m_name) == 0) {
                return m_zig(node);
            } else if (m_root->right != nullptr && name.compare(m_root->right->m_name) == 0) {
                return m_zag(node);
            }
        } 
        if (node->left != nullptr) {
            if (node->left->left != nullptr && name.compare(node->left->left->m_name) == 0) {
                // zig zig
                node = m_zig(node);
                return m_zig(node);
            } if (node->left->right != nullptr && name.compare(node->left->right->m_name) == 0) {
                // zag zig
                node->left = m_zag(node->left);
                return m_zig(node);
            }
        } if (node->right != nullptr) {
            if (node->right->right != nullptr && name.compare(node->right->right->m_name) == 0) {
                // zag zag
                node = m_zag(node);
                return m_zag(node);
            } if (node->right->left != nullptr && name.compare(node->right->left->m_name) == 0) {
                // zig zag
                node->right = m_zig(node->right);
                return m_zag(node);
            }
        }
        return node;
    }

    Node* m_insert(Node* node, const std::string &name, const std::string &hash, int value) {

        if (node == nullptr) {
            node = new Node(name, hash, value);
            std::cout << "NOVO ARTIGO INSERIDO\n";
            return node;

        } else if (name.compare(node->m_name) < 0) {
            node->left = m_insert(node->left, name, hash, value);
        } else if (name.compare(node->m_name) > 0) {
            node->right = m_insert(node->right, name, hash, value);
        } else {
            std::cout << "ARTIGO JA EXISTENTE\n";
        }

        return m_splay(node, name);
    }

    void m_print(Node *node) {
        if (node != nullptr) {
            std::cout << node->m_name << "\n";
            m_print(node->left);
            m_print(node->right);
        }
    }

public:
    SplayTree () : m_root(nullptr) {}
    SplayTree (const std::string &name, const std::string &hash, int value) : m_root(new Node(name, hash, value)) {}

    ~SplayTree () {
        m_free_Splay(m_root);
        m_root =  nullptr;
    }


    void insert(const std::string &name, const std::string &hash, int value) {
        m_root = m_insert(m_root, name, hash, value);
    }

    void print() {
        m_print(m_root);
    }
};

int main() {

    SplayTree tree;

    tree.insert("10", "123", 123);
    tree.print();
    tree.insert("15", "123", 123);
    tree.print();
    tree.insert("20", "123", 123);
    tree.print();
    tree.insert("30", "123", 123);
    tree.print();

    tree.insert("25", "123", 123);
    tree.print();
    tree.insert("12", "123", 123);
    tree.print();
    tree.insert("22", "123", 123);
    tree.print();

    tree.insert("23", "123", 123);
    tree.print();
    tree.insert("17", "123", 123);
    tree.print();
    tree.insert("21", "123", 123);
    tree.print();

    tree.insert("40", "123", 123);
    tree.print();
    tree.insert("18", "123", 123);
    tree.print();
    tree.insert("19", "123", 123);
    tree.print();

    tree.insert("16", "123", 123);
    tree.print();
    tree.insert("50", "123", 123);
    tree.print();


    tree.insert("12", "123", 123);
    tree.print();
    tree.insert("20", "123", 123);
    tree.print();
    tree.insert("30", "123", 123);
    tree.print();

    tree.insert("10", "123", 123);
    tree.print();
    tree.insert("30", "123", 123);
    tree.print();
    tree.insert("20", "123", 123);
    tree.print();

    return 0;
}