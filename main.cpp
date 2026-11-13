#include "TreeExplorer.h"

#include <iostream>
#include <vector>

void printValues(const std::vector<int>& values)
{
    for (int value : values)
        std::cout << value << ' ';

    std::cout << '\n';
}

void displayTreeResults(const TreeNode* root)
{
    std::cout << "Preorder: ";
    printValues(preorder(root));

    std::cout << "Inorder: ";
    printValues(inorder(root));

    std::cout << "Postorder: ";
    printValues(postorder(root));

    std::cout << "Level order: ";
    printValues(levelOrder(root));

    std::cout << "Nodes: " << countNodes(root) << '\n';
    std::cout << "Leaves: " << countLeaves(root) << '\n';
    std::cout << "Height in levels: " << treeHeight(root) << '\n';
    std::cout << "Sum: " << sumValues(root) << '\n';
}

int main()
{
    TreeNode* treeA = new TreeNode{50};
    treeA->left = new TreeNode{30};
    treeA->right = new TreeNode{70};
    treeA->left->left = new TreeNode{20};
    treeA->left->right = new TreeNode{40};
    treeA->right->left = new TreeNode{60};
    treeA->right->right = new TreeNode{80};

    TreeNode* treeB = new TreeNode{10};
    treeB->left = new TreeNode{30};
    treeB->right = new TreeNode{20};
    treeB->left->right = new TreeNode{5};
    treeB->right->right = new TreeNode{15};

    std::cout << "Tree A\n";
    displayTreeResults(treeA);

    std::cout << "\nTree B\n";
    displayTreeResults(treeB);

    destroyTree(treeA);
    destroyTree(treeB);

    std::cout << "\nAfter destruction\n";
    std::cout << std::boolalpha;
    std::cout << "Tree A root is null: " << (treeA == nullptr) << '\n';
    std::cout << "Tree B root is null: " << (treeB == nullptr) << '\n';

    return 0;
}