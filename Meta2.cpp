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

    Node* m_find(Node *node, const std::string &name) {
        if (node != nullptr) {

            if (name.compare(node->m_name) == 0) {
                // i found it
                std::cout << node->m_name << " " << node->m_hash << " " << node->m_value << "\nFIM\n";
                return m_splay(node, name);
            } else if (name.compare(node->m_name) < 0) {
                node->left = m_find(node->left, name);
            } else if (name.compare(node->m_name) > 0) {
                node->right = m_find(node->right, name);
            }
            return m_splay(node, name);
        } else {
            std::cout << "ARTIGO NAO REGISTADO\n";
            return nullptr;
        }
    }

    Node* m_update(Node *node, const std::string &name, int value) {
        if (node != nullptr) {

            if (name.compare(node->m_name) == 0) {
                node->m_value = value;
                std::cout << "OFERTA ATUALIZADA\n";
                return m_splay(node, name);
            } else if (name.compare(node->m_name) < 0) {
                node->left = m_update(node->left, name, value);
            } else if (name.compare(node->m_name) > 0) {
                node->right = m_update(node->right, name, value);
            }
            return m_splay(node, name);
        } else {
            std::cout << "ARTIGO NAO REGISTADO\n";
            return nullptr;
        }
    }

    void m_print(Node *node) {
        if (node != nullptr) {
            m_print(node->left);
            std::cout << node->m_name << " " << node->m_hash << " " << node->m_value << "\n";
            m_print(node->right);
        }
    }

public:
    SplayTree () : m_root(nullptr) {}
    SplayTree (const std::string &name, const std::string &hash, int value) : m_root(new Node(name, hash, value)) {}

    ~SplayTree () {
        if (m_root != nullptr) {
            m_free_Splay(m_root);
            m_root =  nullptr;
        }
    }

    void insert(const std::string &name, const std::string &hash, int value) {
        m_root = m_insert(m_root, name, hash, value);
    }

    void print() {
        m_print(m_root);
        std::cout << "FIM\n";
    }

    void find(const std::string &name) {
        m_root = m_find(m_root, name);
    }

    void delete_tree() {
        if (m_root != nullptr) {
            m_free_Splay(m_root);
            m_root =  nullptr;
            std::cout << "CATALOGO APAGADO\n";
        }
    }

    void update(const std::string &name, int value) {
        m_root = m_update(m_root, name, value);
    }
    void fds() {
        m_root->m_value = 20;
    }
};

int main() {

    SplayTree tree;
    std::string option, name, hash;
    int value;

    do {
        std::cin >> option;

        if (option.compare("ARTIGO") == 0) {
            // add artigo
            std::cin >> name >> hash >> value;
            tree.insert(name, hash, value);

        } else if (option.compare("OFERTA") == 0) {
            // update clause
            std::cin >> name >> value;
            tree.update(name, value);

        } else if (option.compare("CONSULTA") == 0) {
            // search for a clause
            std::cin >> name;
            tree.find(name);

        } else if (option.compare("LISTAGEM") == 0) {
            tree.print();

        } else if (option.compare("APAGA") == 0) {
            tree.delete_tree();

        }
    } while (option.compare("FIM") != 0);

    return 0;
}