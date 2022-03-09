#include <iostream>
#include <vector>


class Tree{ 
    struct Node { 
        std::string m_category;
        int m_value;
        int m_num_sons;
        std::vector<struct Node *> m_sons;

        Node () : m_category(""), m_value(0), m_num_sons(0) {}
        Node (const std::string category, const int value, const int num_sons) : m_category(category), m_value(value), m_num_sons(num_sons) {}
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

    Node* m_insert(Node *node, const std::string category, const int value, const int num_sons) {

        for (int i = 0; i < node->m_num_sons; ++i) {
            
        }



        if(node == nullptr) {
            node = new Node(category, value, num_sons);
        }

        return node;
    }


public:
    Tree () : m_root(nullptr) {}
    Tree (const std::string category, const int value, const int num_sons) : m_root(new Node(category, value, num_sons)) {}

    ~Tree () {
        m_free_tree(m_root);
        m_root = nullptr;
    }

    void insert(const std::string category, const int value, const int num_sons) {
        if (m_root == nullptr) {
            m_root = new Node(category, value, num_sons);
        } else {
            m_root = m_insert(m_root, category, value, num_sons);
        }
    }
};





int main() {




    return 0;
}