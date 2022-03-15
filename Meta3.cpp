#include <iostream>
#include <unordered_map>

class AVL {
    struct Node {
        std::string m_user_name;
        std::unordered_map<int, int> m_credit_card;

        struct Node *left;
        struct Node *right;

        Node() : m_user_name(0), left(nullptr), right(nullptr) {}
        Node(std::string user_name, int credit_card, int date) : m_user_name(user_name), left(nullptr), right(nullptr) {
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

    void m_insert(Node *node, std::string user_name, int credit_card, int date) {

        if (user_name.compare(node->m_user_name) == 0) {
            // TODO atualizar

            if (node->m_credit_card.find(credit_card) != node->m_credit_card.end()) {
                node->m_credit_card[credit_card] = date;
                std::cout << "CARTAO ATUALIZADO\n";
            } else {
                node->m_credit_card[credit_card] = date;
                std::cout << "NOVO CARTAO INSERIDO\n";
            }

        } else if (user_name.compare(node->m_user_name) < 0) {
            // TODO estou à esquerda
            if (node->left == nullptr) {
                node->left = new Node(user_name, credit_card, date);

                std::cout << "NOVO UTILIZADOR CRIADO\n";
                return;
            }
            m_insert(node->left, user_name, credit_card, date);

        } else if (user_name.compare(node->m_user_name) > 0) {
            // TODO estou à direita
            if (node->right == nullptr) {
                node->right = new Node(user_name, credit_card, date);

                std::cout << "NOVO UTILIZADOR CRIADO\n";
                return;
            }
            m_insert(node->right, user_name, credit_card, date);
        }
    }

public:

    AVL() : m_root(nullptr) {}
    AVL(std::string user_name, int credit_card, int date) : m_root(new Node(user_name, credit_card, date)) {}

    ~AVL() {
        m_free_AVL(m_root);
        m_root = nullptr;
    }

    void insert(std::string user_name, int credit_card, int date) {
        if (m_root == nullptr) {
            m_root = new Node(user_name, credit_card, date);
            std::cout << "NOVO UTILIZADOR CRIADO\n";
        } else {
            m_insert(m_root, user_name, credit_card, date);
        }
    }

};


int main() {

    AVL tree;

    tree.insert("joao", 1234, 1414);
    tree.insert("joao", 1234, 1213);
    tree.insert("joao", 1235, 1414);


    return 0;
}