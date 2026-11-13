#include "TreeExplorer.h"

#include <queue>

namespace
{
    void preorderHelper(const TreeNode* root, std::vector<int>& result)
    {
        if (root == nullptr)
            return;

        result.push_back(root->value);
        preorderHelper(root->left, result);
        preorderHelper(root->right, result);
    }

    void inorderHelper(const TreeNode* root, std::vector<int>& result)
    {
        if (root == nullptr)
            return;

        inorderHelper(root->left, result);
        result.push_back(root->value);
        inorderHelper(root->right, result);
    }

    void postorderHelper(const TreeNode* root, std::vector<int>& result)
    {
        if (root == nullptr)
            return;

        postorderHelper(root->left, result);
        postorderHelper(root->right, result);
        result.push_back(root->value);
    }
}

std::vector<int> preorder(const TreeNode* root)
{
    std::vector<int> result;
    preorderHelper(root, result);
    return result;
}

std::vector<int> inorder(const TreeNode* root)
{
    std::vector<int> result;
    inorderHelper(root, result);
    return result;
}

std::vector<int> postorder(const TreeNode* root)
{
    std::vector<int> result;
    postorderHelper(root, result);
    return result;
}

std::vector<int> levelOrder(const TreeNode* root)
{
    std::vector<int> result;

    if (root == nullptr)
        return result;

    std::queue<const TreeNode*> nodes;
    nodes.push(root);

    while (!nodes.empty())
    {
        const TreeNode* current = nodes.front();
        nodes.pop();

        result.push_back(current->value);

        if (current->left != nullptr)
            nodes.push(current->left);

        if (current->right != nullptr)
            nodes.push(current->right);
    }

    return result;
}

std::size_t countNodes(const TreeNode* root)
{
    if (root == nullptr)
        return 0;

    return 1 + countNodes(root->left) + countNodes(root->right);
}

std::size_t countLeaves(const TreeNode* root)
{
    if (root == nullptr)
        return 0;

    if (root->left == nullptr && root->right == nullptr)
        return 1;

    return countLeaves(root->left) + countLeaves(root->right);
}

int treeHeight(const TreeNode* root)
{
    if (root == nullptr)
        return 0;

    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);

    if (leftHeight > rightHeight)
        return 1 + leftHeight;

    return 1 + rightHeight;
}

long long sumValues(const TreeNode* root)
{
    if (root == nullptr)
        return 0;

    return static_cast<long long>(root->value)
        + sumValues(root->left)
        + sumValues(root->right);
}

void destroyTree(TreeNode*& root)
{
    if (root == nullptr)
        return;

    destroyTree(root->left);
    destroyTree(root->right);

    delete root;
    root = nullptr;
}