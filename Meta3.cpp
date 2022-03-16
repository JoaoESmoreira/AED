#include <iostream>
#include <unordered_map>

class AVL {
    struct Node {
        std::string m_user_name;
        std::unordered_map<int, int> m_credit_card;

        struct Node *left;
        struct Node *right;

        int m_height;

        Node() : m_user_name(0), left(nullptr), right(nullptr), m_height(0) {}
        Node(std::string user_name, int credit_card, int date) : m_user_name(user_name), left(nullptr), right(nullptr), m_height(1) {
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
        Node *left_son  = node->left;
        Node *grand_son = left_son->right;
    
        // Perform rotation
        left_son->right = node;
        node->left      = grand_son;
    
        // Update heights
        node->m_height     = m_node_height(node);
        left_son->m_height = m_node_height(left_son);

        return left_son;
    }

    Node* m_left_rotate(Node *node) {
        Node *right_son = node->right;
        Node *grand_son = right_son->left;
    
        // Perform rotation
        right_son->left = node;
        node->right = grand_son;
    
        // Update heights
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


    Node* m_insert(Node *node, std::string user_name, int credit_card, int date) {

        // Basic insertion
        if (node == nullptr) {
            node = new Node(user_name, credit_card, date);
            std::cout << "NOVO UTILIZADOR CRIADO\n";
        } else if (user_name.compare(node->m_user_name) < 0) {
            node->left = m_insert(node->left, user_name, credit_card, date);
        } else if (user_name.compare(node->m_user_name) >  0) {
            node->right = m_insert(node->right, user_name, credit_card, date);
        } else {
            
            if (node->m_credit_card.find(credit_card) != node->m_credit_card.end()) {
                node->m_credit_card[credit_card] = date;
                std::cout << "CARTAO ATUALIZADO\n";
            } else {
                node->m_credit_card[credit_card] = date;
                std::cout << "NOVO CARTAO INSERIDO\n";
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

public:

    AVL() : m_root(nullptr) {}
    AVL(std::string user_name, int credit_card, int date) : m_root(new Node(user_name, credit_card, date)) {}

    ~AVL() {
        m_free_AVL(m_root);
        m_root = nullptr;
    }

    void insert(std::string user_name, int credit_card, int date) {
        m_root = m_insert(m_root, user_name, credit_card, date);
    }

};


int main() {

    AVL tree;

    tree.insert("joao", 1234, 1414);
    tree.insert("joao", 1234, 1213);
    tree.insert("joao", 1235, 1414);
    tree.insert("emanuel", 1234, 1234);
    tree.insert("emanuel", 1234, 1243);
    tree.insert("emanuel", 12345, 1234);


    return 0;
}