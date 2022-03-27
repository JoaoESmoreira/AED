#include <iostream>

class SplayTree {
    struct Node {
        std::string m_name;
        std::string m_hash;
        int         m_value;

        Node *right;
        Node *left;

        Node () : m_name(""), m_hash(""), m_value(0) {}
        Node (const std::string name, const std::string hash, int value) : m_name(name), m_hash(hash), m_value(value) {}
    };

    Node *m_root;


    Node* m_zig (Node *node) {
        if (node != nullptr) {
        // store son and grandson
        Node *leftSon  = node->left;
        Node *grandSon = leftSon->right;

        // swap
        node->left     = grandSon;
        leftSon->right = node;

        return leftSon;
        }
        return nullptr;
    }

    Node *m_zag (Node *node) {
        if (node != nullptr) {
        // store son and grand son
        Node *rightSon = node->right;
        Node *grandSon = rightSon->left;

        // swap
        node->right    = grandSon;
        rightSon->left = node;

        return rightSon;
        }
        return nullptr;
    }

    Node* m_insert(Node* node, const std::string name, const std::string hash, int value) {

        if (node == nullptr) {
            node = new Node(name, hash, value);

            std::cout << "NOVO ARTIGO INSERIDO\n";
        } else if (name.compare(node->m_name) < 0) {
            node->left = m_insert(node->left, name, hash, value);
        } else if (name.compare(node->m_name) > 0) {
            node->right = m_insert(node->right, name, hash, value);
        } else {
            std::cout << "ARTIGO JA EXISTENTE\n";
            return node;
        }

        if (node->left != nullptr && name.compare(node->left->m_name) == 0) {
            return m_zig(node);
        } else if (node->right != nullptr && name.compare(node->right->m_name) == 0) {
            return m_zag(node);
        }


        return node;
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
    SplayTree (const std::string name, const std::string hash, int value) : m_root(new Node(name, hash, value)) {}


    void insert(const std::string name, const std::string hash, int value) {
        m_root = m_insert(m_root, name, hash, value);
    }

    void print() {
        m_print(m_root);
    }
};

int main() {

    SplayTree tree;

    tree.insert("10", "123", 123);
    tree.insert("15", "123", 123);
    tree.insert("20", "123", 123);
    tree.insert("30", "123", 123);

    tree.insert("25", "123", 123);
    tree.insert("12", "123", 123);
    tree.insert("22", "123", 123);

    tree.print();

    return 0;
}