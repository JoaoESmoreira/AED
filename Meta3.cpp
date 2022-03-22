#include <iostream>
#include <map>
#include <fstream>

class AVL {
    struct Node {
        std::string m_user_name;
        std::map<std::string, int> m_credit_card;

        struct Node *left;
        struct Node *right;

        int m_height;

        Node() : m_user_name(0), left(nullptr), right(nullptr), m_height(0) {}
        Node(const std::string user_name, const std::string credit_card, int date) : m_user_name(user_name), left(nullptr), right(nullptr), m_height(1) {
            m_credit_card[credit_card] = date;
        }
    };

    Node *m_root;

    void m_free_AVL(Node *node) {
        if (node != nullptr) {
            m_free_AVL(node->left);
            m_free_AVL(node->right);
            delete node;
        }
    }

    int m_node_height(Node *node) {
        int a, b;

        if (node->left == nullptr) {
            a = 0;
        } else {
            a = node->left->m_height;
        }
        if (node->right == nullptr) {
            b = 0;
        } else {
            b = node->right->m_height;
        }


        if (a < b) {
            return 1 + b;
        } else {
            return 1 + a;
        }
    }

    Node* m_right_rotate(Node *node) {
        // aux variables
        Node *left_son  = node->left;
        Node *grand_son = left_son->right;

        // rebalance
        left_son->right = node;
        node->left      = grand_son;

        // "re-height" 
        node->m_height     = m_node_height(node);
        left_son->m_height = m_node_height(left_son);

        return left_son;
    }

    Node* m_left_rotate(Node *node) {
        // aux variables
        Node *right_son = node->right;
        Node *grand_son = right_son->left;
    
        // rebalance
        right_son->left = node;
        node->right = grand_son;
    
        // "re-height" 
        node->m_height = m_node_height(node);
        right_son->m_height = m_node_height(right_son);
    
        return right_son;
    }

    int m_balance(Node *node) {
        int a, b;
        if (node == nullptr)
            return 0;

        if (node->left == nullptr) {
            a = 0;
        } else {
            a = node->left->m_height;
        }
        if (node->right == nullptr) {
            b = 0;
        } else {
            b = node->right->m_height;
        }
        return a - b;
    }


    Node* m_insert(Node *node, const std::string user_name, const std::string credit_card, int date) {

        // Basic insertion
        if (node == nullptr) {
            node = new Node(user_name, credit_card, date);
            // TODO std::cout << "NOVO UTILIZADOR CRIADO\n";
        } else if (user_name.compare(node->m_user_name) < 0) {
            node->left = m_insert(node->left, user_name, credit_card, date);
        } else if (user_name.compare(node->m_user_name) >  0) {
            node->right = m_insert(node->right, user_name, credit_card, date);
        } else {
            
            if (node->m_credit_card.find(credit_card) != node->m_credit_card.end()) {
                node->m_credit_card[credit_card] = date;
                // TODO std::cout << "CARTAO ATUALIZADO\n";
            } else {
                node->m_credit_card[credit_card] = date;
                // TODO std::cout << "NOVO CARTAO INSERIDO\n";
            }
        }

        // Update height
        node->m_height = m_node_height(node);

        // Balance all tree
        int balance = m_balance(node);
        if (balance > 1 && user_name < node->left->m_user_name) {
            // left letf
            return m_right_rotate(node);
        } if (balance < -1 && user_name > node->right->m_user_name) {
            // right right
            return m_left_rotate(node);
        } if (balance > 1 && user_name > node->left->m_user_name) {
            // left right
            node->left = m_left_rotate(node->left);
            return m_right_rotate(node);
        } if (balance < -1 && user_name < node->right->m_user_name) {
            // right left
            node->right = m_right_rotate(node->right);
            return m_left_rotate(node);
        }

        return node;
    }

    void m_find(Node *node, const std::string user_name) {
        if (node == nullptr) {
            // TODO std::cout << "NAO ENCONTRADO\n";

        } else if (user_name.compare(node->m_user_name) == 0) {
            for (auto key : node->m_credit_card) {
                // TODO std::cout << key.first << " " << key.second << "\n";
            } // TODO std::cout << "FIM" << "\n";

        } else if (user_name.compare(node->m_user_name) < 0){
            m_find(node->left, user_name);
        } else if (user_name.compare(node->m_user_name) > 0) {
            m_find(node->right, user_name);
        }
    }

    void m_print(Node *node) {
        if (node != nullptr) {
            m_print(node->left);

            std::cout << node->m_user_name << " ";

            for (std::map<std::string, int>::iterator it = node->m_credit_card.begin(); it != node->m_credit_card.end(); ) {
                std::cout << it->first<< " " << it->second;
                if (++it != node->m_credit_card.end()) {
                    std::cout << " ";
                } else {
                    std::cout << "\n";
                }
            }
            m_print(node->right);
        }
    }

public:

    AVL() : m_root(nullptr) {}
    AVL(const std::string user_name, const std::string credit_card, int date) : m_root(new Node(user_name, credit_card, date)) {}

    ~AVL() {
        if (m_root != nullptr) {
            m_free_AVL(m_root);
            m_root = nullptr;
        }
    }

    void insert(const std::string user_name, const std::string credit_card, int date) {
        // insert/update a node 
        m_root = m_insert(m_root, user_name, credit_card, date);
    }

    void find(const std::string user_name) {
        // print all credit cards of an user_name
        m_find(m_root, user_name);
    }

    void print() {
        // print all AVLT
        m_print(m_root);
        std::cout << "FIM\n";
    }
    void apaga() {
        m_free_AVL(m_root);
        m_root = nullptr;
    }
};


int main() {

    AVL tree;
    std::string comand, user_name, credit_card;
    int date;

    std::ifstream file ("input.txt");

    do {
        // std::cin >> comand;
        file >> comand;

        if (comand.compare("ACRESCENTA") == 0) {
           // std::cin >> user_name >> credit_card >> date;
           file >> user_name >> credit_card >> date;

           tree.insert(user_name, credit_card, date);
        } else if (comand.compare("CONSULTA") == 0) {
            // std::cin >> user_name;
            file >> user_name;

            tree.find(user_name);
        } else if (comand.compare("LISTAGEM") == 0) {
            tree.print();
        } else if (comand.compare("APAGA") == 0) {
            tree.apaga();
            std::cout << "LISTAGEM APAGADA\n";
        } 
    } while (!comand.compare("FIM") == 0);
    
    return 0;
}