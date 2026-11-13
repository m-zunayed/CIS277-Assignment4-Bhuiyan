#include "TreeExplorer.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

void check(bool condition, const std::string& message)
{
    if (!condition)
        throw std::runtime_error(message);
}

void checkTree(const TreeNode* root,
               const std::vector<int>& expectedPreorder,
               const std::vector<int>& expectedInorder,
               const std::vector<int>& expectedPostorder,
               const std::vector<int>& expectedLevelOrder,
               std::size_t expectedNodes,
               std::size_t expectedLeaves,
               int expectedHeight,
               long long expectedSum)
{
    check(preorder(root) == expectedPreorder, "preorder failed");
    check(inorder(root) == expectedInorder, "inorder failed");
    check(postorder(root) == expectedPostorder, "postorder failed");
    check(levelOrder(root) == expectedLevelOrder, "level order failed");

    check(countNodes(root) == expectedNodes, "node count failed");
    check(countLeaves(root) == expectedLeaves, "leaf count failed");
    check(treeHeight(root) == expectedHeight, "height failed");
    check(sumValues(root) == expectedSum, "sum failed");
}

int main()
{
    try
    {
        // Test 1: Empty tree and repeated destruction
        TreeNode* root = nullptr;

        checkTree(root, {}, {}, {}, {}, 0, 0, 0, 0);
        destroyTree(root);
        check(root == nullptr, "empty tree destruction failed");
        destroyTree(root);
        check(root == nullptr, "repeated empty tree destruction failed");

        std::cout << "PASS: empty tree and repeated destruction\n";

        // Test 2: Singleton with value -4
        root = new TreeNode{-4};

        checkTree(root, {-4}, {-4}, {-4}, {-4}, 1, 1, 1, -4);

        destroyTree(root);
        check(root == nullptr, "singleton destruction failed");

        std::cout << "PASS: singleton tree\n";

        // Test 3: Four-node left-only chain
        root = new TreeNode{4};
        root->left = new TreeNode{3};
        root->left->left = new TreeNode{2};
        root->left->left->left = new TreeNode{1};

        checkTree(root,
                  {4, 3, 2, 1},
                  {1, 2, 3, 4},
                  {1, 2, 3, 4},
                  {4, 3, 2, 1},
                  4, 1, 4, 10);

        destroyTree(root);

        std::cout << "PASS: left-only chain\n";

        // Test 4: Four-node right-only chain
        root = new TreeNode{4};
        root->right = new TreeNode{3};
        root->right->right = new TreeNode{2};
        root->right->right->right = new TreeNode{1};

        checkTree(root,
                  {4, 3, 2, 1},
                  {4, 3, 2, 1},
                  {1, 2, 3, 4},
                  {4, 3, 2, 1},
                  4, 1, 4, 10);

        destroyTree(root);

        std::cout << "PASS: right-only chain\n";

        // Test 5: Duplicate, zero, and negative values
        /*
       0
      / \
    -2  -2
      \
       0
     */
        root = new TreeNode{0};
        root->left = new TreeNode{-2};
        root->right = new TreeNode{-2};
        root->left->right = new TreeNode{0};

        checkTree(root,
                  {0, -2, 0, -2},
                  {-2, 0, 0, -2},
                  {0, -2, -2, 0},
                  {0, -2, -2, 0},
                  4, 2, 3, -4);

        destroyTree(root);

        std::cout << "PASS: duplicate, zero, and negative values\n";

        // Test 6: Repeated traversals and snapshot independence
        root = new TreeNode{7};
        root->left = new TreeNode{3};
        root->right = new TreeNode{9};

        std::vector<int> firstResult = preorder(root);
        firstResult[0] = 100;

        check(preorder(root) == std::vector<int>({7, 3, 9}),
              "changed returned vector affected later preorder");
        check(inorder(root) == std::vector<int>({3, 7, 9}),
              "repeated traversal changed the tree");
        check(countNodes(root) == 3, "snapshot test changed node count");
        check(sumValues(root) == 19, "snapshot test changed tree values");

        destroyTree(root);

        std::cout << "PASS: repeated traversals and snapshot independence\n";

        // Test 7: Destroy, rebuild, and destroy again
        root = new TreeNode{5};
        root->left = new TreeNode{2};
        root->right = new TreeNode{8};

        destroyTree(root);
        check(root == nullptr, "first destruction did not clear root");

        root = new TreeNode{-1};
        root->left = new TreeNode{-2};

        checkTree(root,
                  {-1, -2},
                  {-2, -1},
                  {-2, -1},
                  {-1, -2},
                  2, 1, 2, -3);

        destroyTree(root);
        check(root == nullptr, "rebuilt tree destruction failed");

        std::cout << "PASS: destruction and rebuilding\n";

        // Test 8: Additional uneven tree
       /*
       8
      / \
     4   12
      \  /
       6 10
     */
        root = new TreeNode{8};
        root->left = new TreeNode{4};
        root->right = new TreeNode{12};
        root->left->right = new TreeNode{6};
        root->right->left = new TreeNode{10};

        checkTree(root,
                  {8, 4, 6, 12, 10},
                  {4, 6, 8, 10, 12},
                  {6, 4, 10, 12, 8},
                  {8, 4, 12, 6, 10},
                  5, 2, 3, 40);

        destroyTree(root);
        check(root == nullptr, "additional tree destruction failed");

        std::cout << "PASS: additional uneven tree\n";

        std::cout << "\nAll student tests passed.\n";
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
