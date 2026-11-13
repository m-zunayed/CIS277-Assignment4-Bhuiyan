# CIS-277 Assignment 4: Binary Tree Explorer

## Student

Md Zunayed Bhuiyan

## Design

My tree nodes will store an integer value and two pointers, `left` and `right`, for the child nodes.

For an empty tree, the recursive functions will use `root == nullptr` as the base case. Traversals will return an empty result for an empty tree, and the count, height, and sum functions will return 0.

For preorder, inorder, and postorder, I will use recursive helper functions that receive one output vector by reference. Each helper will add a node value to the vector in the correct traversal order.

For level order, I will use a `std::queue<const TreeNode*>`. I will push the root first, then repeatedly remove the front node from the queue, add its value to the result, and push its left and right children if they exist.

Each tree will own its own dynamically allocated nodes. The tree cleanup function will release every node using postorder so the children are deleted before their parent. `main.cpp` and my tests will call `destroyTree` on each root they create, and after cleanup the root pointer will be set to `nullptr`.

## How to Compile

## How to Run

## Tests and Results

## Analysis Questions

## AI Use