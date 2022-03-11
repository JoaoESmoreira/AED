    void m_print(Node *node) {
        if (node != nullptr) {
            std::cout << node->m_category << " " << node->m_value << "\n";
            for (int i = 0; i < node->m_num_sons; ++i) {
                m_print(node->m_sons[i]);
            }
        }
    }

    void m_sum(Node *node, int sum) {
        if (node != nullptr) {
            for (int i = 0; i < node->m_num_sons; ++i) {
                m_sum(node->m_sons[i], sum + node->m_value);
            }
        }
    }

    void m_print_by_level(Node *node, int level) {
        if (node != nullptr) {
            if (node->m_height == level) {
                int return_value = 0;
                m_sum(node, return_value);
                std::cout << node->m_category << "(" << return_value << ")";
            }
        }
    }