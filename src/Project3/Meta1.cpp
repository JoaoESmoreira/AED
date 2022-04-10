#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

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
    int m_capacity;
    int m_size;


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
                        m_capacity += num_sons;
                        m_size += 1;
                        return true;
                    }
                }
            } 
        } 
        return false;
    }

    void m_sum(Node *node, int &value) {
        
        for (int i = 0; i < node->m_num_sons; ++i) {
            value += node->m_sons[i]->m_value;
            m_sum(node->m_sons[i], value);
        }
    }

    void m_print_by_level(std::queue<Node *> queue) {

        while (!queue.empty()) {
            int s = queue.size();

            for (int j = 0; j < s; ++j) {
                Node *aux = queue.front();

                for (int i = 0; i < aux->m_num_sons; ++i) {
                    queue.push(aux->m_sons[i]);
                }

                int sum = 0;
                m_sum(aux, sum);

                if (j == s - 1) {
                    std::cout << aux->m_category << "(" << sum + aux->m_value << ")";
                } else {
                    std::cout << aux->m_category << "(" << sum + aux->m_value << ") ";
                }
                queue.pop();
            }
            std::cout << "\n";
        }
    }

public:
    Tree () : m_root(nullptr), m_capacity(1), m_size(0){}
    Tree (const std::string category, const int value, const int num_sons) : 
        m_root(new Node(category, value, num_sons)), m_capacity(num_sons), m_size(1) {}


    ~Tree () {
        m_free_tree(m_root);
        m_root = nullptr;
    }

    bool insert(const std::string &category, const int &value, const int &num_sons) {
        if (m_root == nullptr) {
            m_root = new Node(category, value, num_sons);
            m_capacity += num_sons;
            m_size += 1;
            return true;
        } else {
            return m_insert(m_root, category, value, num_sons);
        }
    }

    void print_by_level() {
        std::queue<Node *> queue;
        queue.push(m_root);
        m_print_by_level(queue);
    }

    int capacity() {
        return m_capacity;
    }

    int size() {
        return m_size;
    }
};



int main() {

    Tree tree;
    std::string category;
    int value, num_sons;

    std::ifstream file ("entradas.txt");

    while (tree.size() < tree.capacity() && file >> category && file >> value && file >> num_sons) {
        //std::cin >> category >> value >> num_sons;

        tree.insert(category, value, num_sons);
    }

    //tree.print_by_level();

    return 0;
}