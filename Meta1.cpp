#include <iostream>
#include <vector>


class Tree { 
    struct Node { 
        std::string m_category;
        std::vector<struct Node *> m_sons;
        int m_value;
        int m_num_sons;
        int m_size;

        Node () : m_category(""), m_value(0), m_num_sons(0), m_size(0) {}

        Node (const std::string category, const int value, const int num_sons) : m_category(category), m_value(value), m_num_sons(num_sons), m_size(0) {
            for (int i = 0; i < m_num_sons; ++i) {
                m_sons.push_back(nullptr);
            }
        }
    };

    Node *m_root;


    void m_free_tree(Node *node) {
        if (node != nullptr) {
            for (auto son : node->m_sons) {
                m_free_tree(son);
            }

            delete node;
        }
    }

    bool m_insert(Node *node, const std::string &category, const int &value, const int &num_sons) {

        if (node != nullptr) {
            if (node->m_size <= node->m_num_sons) {
                for (int i = 0; i < node->m_num_sons; ++i) {

                    if (m_insert(node->m_sons[i], category, value, num_sons) == true) {
                        return true;
                    } else if (node->m_sons[i] == nullptr) {
                        node->m_sons[i] = new Node(category, value, num_sons);
                        node->m_size += 1;
                        return true;
                    }
                }
            } 
        } 
        return false;
    }

    void m_print(Node *node) {
        if (node != nullptr) {
            std::cout << node->m_category << " " << node->m_value << "\n";
            for (int i = 0; i < node->m_num_sons; ++i) {
                m_print(node->m_sons[i]);
            }
        }
    }

public:
    Tree () : m_root(nullptr) {}
    Tree (const std::string category, const int value, const int num_sons) : m_root(new Node(category, value, num_sons)) {}

    ~Tree () {
        m_free_tree(m_root);
        m_root = nullptr;
    }

    bool insert(const std::string &category, const int &value, const int &num_sons) {
        if (m_root == nullptr) {
            m_root = new Node(category, value, num_sons);
            return true;
        } else {
            return m_insert(m_root, category, value, num_sons);
        }
    }

    void print() {
        m_print(m_root);
        std::cout << "\n";
    }
};



int main() {

    Tree tree;
    std::cout << tree.insert("Todos", 0, 3)      << "\n";
    std::cout << tree.insert("Arte", 5, 2)       << "\n";
    std::cout << tree.insert("Classic", 1000, 0) << "\n";
    std::cout << tree.insert("Foto", 50, 0)      << "\n";
    std::cout << tree.insert("Livros", 100, 0)   << "\n";
    std::cout << tree.insert("Musica", 0, 3)     << "\n";
    std::cout << tree.insert("Rock", 20, 1)      << "\n";
    std::cout << tree.insert("softROck", 5, 0)   << "\n";
    std::cout << tree.insert("pop", 20, 0)       << "\n";
    std::cout << tree.insert("country", 20, 0)   << "\n";
    std::cout << tree.insert("ERRO", 2, 0)       << "\n";
    std::cout << tree.insert("NAO ENTRE?", 2,2)  << "\n";

    tree.print();

    return 0;
}