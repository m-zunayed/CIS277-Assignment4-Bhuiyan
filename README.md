# CIS-277 Assignment 4: Binary Tree Explorer

## Student

Md Zunayed Bhuiyan

## Design

My tree nodes will store an integer value and two pointers, `left` and `right`, for the child nodes.

For an empty tree, the recursive functions will use `root == nullptr` as the base case. Traversals will return an empty result for an empty tree, and the count, height, and sum functions will return 0.

For preorder, inorder, and postorder, I will use recursive helper functions that receive one output vector by reference. Each helper will add a node value to the vector in the correct traversal order.

For level order, I will use a `std::queue<const TreeNode*>`. I will push the root first, then repeatedly remove the front node from the queue, add its value to the result, and push its left and right children if they exist.

Each tree will own its own dynamically allocated nodes. The tree cleanup function will release every node using postorder so the children are deleted before their parent. `main.cpp` and my tests will call `destroyTree` on each root they create, and after cleanup the root pointer will be set to `nullptr`.

### Tree Diagrams and Predictions

#### Tree A

```text
        50
       /  \
     30    70
    / \    / \
   20 40  60 80
```

Root: 50  
Leaves: 20, 40, 60, 80  

Parent-child connections:
- 50 has left child 30 and right child 70.
- 30 has left child 20 and right child 40.
- 70 has left child 60 and right child 80.

Predicted preorder: 50 30 20 40 70 60 80  
Predicted inorder: 20 30 40 50 60 70 80  
Predicted postorder: 20 40 30 60 80 70 50  
Predicted level order: 50 30 70 20 40 60 80  

Predicted nodes: 7  
Predicted leaves: 4  
Predicted height in levels: 3  
Predicted sum: 350  

#### Tree B

```text
        10
       /  \
     30    20
       \     \
        5     15
```

Root: 10  
Leaves: 5, 15  

Parent-child connections:
- 10 has left child 30 and right child 20.
- 30 has right child 5.
- 20 has right child 15.

Predicted preorder: 10 30 5 20 15  
Predicted inorder: 30 5 10 20 15  
Predicted postorder: 5 30 15 20 10  
Predicted level order: 10 30 20 5 15  

Predicted nodes: 5  
Predicted leaves: 2  
Predicted height in levels: 3  
Predicted sum: 80  

### Traversal Reasoning

For Tree B inorder traversal, I first go to the left subtree of 10. At node 30, there is no left child, so I record 30. Then I go to its right child and record 5. After finishing the left subtree, I return to 10 and record 10. Then I go to the right subtree, record 20, and then its right child 15.

This gives the inorder sequence:

`30 5 10 20 15`

## How to Compile

## How to Run

## Tests and Results

## Analysis Questions

## AI Use