#ifndef TREESORT_TOURNAMENT_H
#define TREESORT_TOURNAMENT_H

#include <vector>
#include <functional>
#include <cassert>

class BinaryTree {
protected:
    struct BinaryTreeNode
    {
        BinaryTreeNode *left, *right;
        int key;
        BinaryTreeNode() {
            left = nullptr;
            right = nullptr;
            key = 0;
        }
    };

    BinaryTreeNode* m_root;

protected:
    void insert_recursive(BinaryTreeNode* cur_node, BinaryTreeNode* node_to_insert)
    {
        assert(cur_node != nullptr);

        bool insertIsLess = node_to_insert->key < cur_node->key;
        if(insertIsLess)
        {
            if(cur_node->left == nullptr)
                cur_node->left = node_to_insert;
            else
                insert_recursive(cur_node->left, node_to_insert);
        }
        else
        {
            if(cur_node->right == nullptr)
                cur_node->right = node_to_insert;
            else
                insert_recursive(cur_node->right, node_to_insert);
        }
    }

public:
    void insert(int key)
    {
        auto node_to_insert = new BinaryTreeNode();
        node_to_insert->key = key;

        if(m_root == nullptr)
        {
            m_root = node_to_insert;
            return;
        }

        insert_recursive(m_root, node_to_insert);
    }

public:
    typedef std::function<void(int key)> Visitor;

protected:
    void visit_recursive(BinaryTreeNode* cur_node, const Visitor& visitor)
    {
        assert(cur_node != nullptr);

        if(cur_node->left != nullptr)
            visit_recursive(cur_node->left, visitor);

        visitor(cur_node->key);

        if(cur_node->right != nullptr)
            visit_recursive(cur_node->right, visitor);
    }

public:
    void visit(const Visitor& visitor)
    {
        if(m_root == nullptr)
            return;
        visit_recursive(m_root, visitor);
    }

public:
    explicit BinaryTree(const std::vector<int>& values) {
        m_root = nullptr;
        for (auto value : values) {
            this->insert(value);
        }
    }

    std::vector<int> GetOrder() {
        std::vector<int> result;
        this->visit([&result](int visited_key){ result.push_back(visited_key); });
        return result;
    }
};


#endif
