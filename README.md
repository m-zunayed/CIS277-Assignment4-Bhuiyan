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


From the repository root, compile the demonstration program with:

```bash
g++ -std=c++23 -Wall -Wextra -pedantic main.cpp TreeExplorer.cpp -o tree_explorer
```

Compile the student tests with:

```bash
g++ -std=c++23 -Wall -Wextra -pedantic -I. tests/student_tests.cpp TreeExplorer.cpp -o student_tests
```

## How to Run

Run the demonstration program with:

```bash
./tree_explorer
```

Run the student tests with:

```bash
./student_tests
```

Run the supplied public validator with:

```bash
python3 validate.py
```

## Tests and Results

### Demonstration Results

The actual results from `main.cpp` matched my predictions for both trees.

| Result | Tree A | Tree B |
|---|---|---|
| Preorder | 50 30 20 40 70 60 80 | 10 30 5 20 15 |
| Inorder | 20 30 40 50 60 70 80 | 30 5 10 20 15 |
| Postorder | 20 40 30 60 80 70 50 | 5 30 15 20 10 |
| Level order | 50 30 70 20 40 60 80 | 10 30 20 5 15 |
| Nodes | 7 | 5 |
| Leaves | 4 | 2 |
| Height in levels | 3 | 3 |
| Sum | 350 | 80 |

After calling `destroyTree` on both trees, both root pointers were `nullptr`.

### Student Tests

| Test | Input / Shape | Expected Result | Actual Result | Corrections |
|---|---|---|---|---|
| Empty tree and repeated destruction | `nullptr` | Empty traversals, nodes 0, leaves 0, height 0, sum 0, and repeated destruction is safe | All checks passed and the root remained `nullptr` | None |
| Singleton | One node with value `-4` | Preorder, inorder, postorder, and level order: `-4`; nodes 1, leaves 1, height 1, sum -4 | All expected results matched | None |
| Four-node left-only chain | `4 -> 3 -> 2 -> 1` using left children | Preorder: `4 3 2 1`; inorder: `1 2 3 4`; postorder: `1 2 3 4`; level order: `4 3 2 1`; nodes 4, leaves 1, height 4, sum 10 | All expected traversals and measurements matched | None |
| Four-node right-only chain | `4 -> 3 -> 2 -> 1` using right children | Preorder: `4 3 2 1`; inorder: `4 3 2 1`; postorder: `1 2 3 4`; level order: `4 3 2 1`; nodes 4, leaves 1, height 4, sum 10 | All expected traversals and measurements matched | None |
| Duplicate, zero, and negative values | Root 0; children -2 and -2; left -2 has right child 0 | Preorder: `0 -2 0 -2`; inorder: `-2 0 0 -2`; postorder: `0 -2 -2 0`; level order: `0 -2 -2 0`; nodes 4, leaves 2, height 3, sum -4 | All four nodes appeared in every traversal, including both `-2` values and both `0` values. All expected measurements matched | None |
| Repeated traversals and changed returned vector | Root 7 with children 3 and 9 | Changing one returned vector must not change the tree or later traversal results | Later preorder remained `7 3 9`; inorder remained `3 7 9`; node count stayed 3 and sum stayed 19 | None |
| Destroy, rebuild, and destroy again | First tree: 5 with children 2 and 8. Rebuilt tree: -1 with left child -2 | First root becomes `nullptr`; rebuilt tree has preorder `-1 -2`, inorder `-2 -1`, postorder `-2 -1`, level order `-1 -2`, nodes 2, leaves 1, height 2, sum -3; second destruction is safe | Both destructions cleared the root and all rebuilt-tree results matched | None |
| Additional uneven tree | Root 8; left 4 with right child 6; right 12 with left child 10 | Preorder: `8 4 6 12 10`; inorder: `4 6 8 10 12`; postorder: `6 4 10 12 8`; level order: `8 4 12 6 10`; nodes 5, leaves 2, height 3, sum 40 | All expected traversals and measurements matched | None |

For these two chain tests, preorder, postorder, and level order are the same. Inorder is different because the left-only chain is visited from the bottom up, while the right-only chain is visited from the top down.

All student tests passed.

### Memory Check

I ran the macOS `leaks` tool on both executables.

For the student tests:

`leaks --atExit -- ./student_tests`

Result: `0 leaks for 0 total leaked bytes.`

For the demonstration program:

`leaks --atExit -- ./tree_explorer`

Result: `0 leaks for 0 total leaked bytes.`

### Public Validator

I ran the supplied public validator with:

`python3 validate.py`

Result: `PASS: 96 public behavioral checks`

The validator also compiled the demonstration successfully and finished with:

`PASS: public preflight completed.`

## Analysis Questions

### 1. Traversals of the subtree rooted at 30

For the subtree rooted at 30 in Tree A:

- **Preorder:** Visit 30 first. Then go left to 20, visit it, and return because it has no children. Then go right to 40, visit it, and return. The result is `30 20 40`.

- **Inorder:** Go left to 20 and visit it. Return to 30 and visit it. Then go right to 40 and visit it. The result is `20 30 40`.

- **Postorder:** Go left to 20 and finish it first. Then go right to 40 and finish it. Finally, return to 30 and visit it. The result is `20 40 30`.

The sequences change because each traversal processes the root at a different time. The sum does not change because all three traversals still visit the same nodes with the same values. The sum is `30 + 20 + 40 = 90`.

### 2. Why Tree B is not a BST

Tree B is a binary tree because every node has at most two children. It is not a binary search tree because the left child of 10 is 30, which is greater than 10. This violates the BST rule that values in the left subtree should be smaller than the root.

Its inorder traversal is `30 5 10 20 15`, which is not sorted because Tree B does not follow BST ordering.

### 3. Depth and height

Node 40 has a depth of 2 because it takes two edges to reach it from the root: `50 -> 30 -> 40`.

Depth counts the number of edges from the root to a specific node. In this assignment, tree height counts levels. Tree A has a height of 3 levels, while node 40 has a depth of 2 edges.

### 4. FIFO queue and level order

Level-order traversal uses a FIFO queue. The root is pushed first. Then the node at the front is removed, its value is added to the result, and its left and right children are pushed if they exist.

Because the queue is FIFO, nodes that are added first are processed first. This makes the traversal move through the tree one level at a time from left to right. This is the same FIFO behavior used in our earlier queue work, where the first item added is the first item removed.

### 5. Time and auxiliary space

For a tree with `n` nodes, height `h`, and maximum level width `w`:

- Preorder, inorder, and postorder each take `O(n)` time because every node is visited once. Their recursive call stack uses `O(h)` auxiliary space.
- Level-order traversal takes `O(n)` time and uses `O(w)` auxiliary queue space.
- The returned traversal vector contains `n` values, so it requires `O(n)` space. This is separate from the recursive call stack or the level-order queue.
- Node count, leaf count, height, and sum each take `O(n)` time and use `O(h)` recursive stack space.
- `destroyTree` takes `O(n)` time and uses `O(h)` recursive stack space.

A balanced tree has height `O(log n)`, while a chain can have height `O(n)`.

Dynamic-programming tabulation is not needed for a normal tree traversal because each node is processed once and the same subproblems are not being solved repeatedly.

### 6. Postorder deletion and `TreeNode*&`

Deletion uses postorder so the left and right children are deleted before their parent. This keeps the child pointers available until their subtrees have been safely destroyed.

The `TreeNode*&` parameter is a reference to the caller's pointer, so `destroyTree` can set that pointer to `nullptr` after deleting the node.

If the parent were deleted before reading its child pointers, accessing those pointers afterward would mean using memory that has already been deleted. This would be unsafe and could also prevent the child nodes from being properly reached and deleted.

## AI Use

I used ChatGPT after completing and saving my initial design plan. I mainly used it to review my work, and double-check the assignment requirements.

I wrote `TreeExplorer.cpp`, `main.cpp`, and `tests/student_tests.cpp` myself and used ChatGPT to review the code, check the logic, and verify the expected traversal values and test results. Some of the most useful suggestions I used were putting the ASCII tree diagrams in `tests/student_tests.cpp` inside `/* */` block comments, because a backslash at the end of a `//` comment line can cause a multi-line comment warning on some compilers. I also used the suggestion to add an input/shape column and exact expected traversal sequences to the README test table, especially for the left-only chain, right-only chain, and duplicate-value test.

I decided not to use some of the suggestions because they were not necessary for the assignment. For example, I left out run timestamps in the memory-check section because they were not required, and I kept the student test program stopping at the first failed check instead of adding a system to count every failure.

One decision I made was to use an explicit `if` comparison in `treeHeight` instead of `std::max` because the logic is easy to trace by hand when predicting tree heights. I also built Tree B with direct pointer connections because it is not a BST and needed to match the exact shape given in the assignment.

One test that helped check my understanding was comparing the four-node left-only and right-only chains. They have the same height and several matching traversal results, but their inorder traversals are different because the child links go in opposite directions.

I verified the project by compiling with the required warning flags, running the demonstration, running my student tests, checking both executables with the macOS `leaks` tool, and running the supplied public validator. All student tests passed, both memory checks reported 0 leaks, and the public validator passed 96 behavioral checks.

This assignment helped me better understand recursive tree traversals, level-order traversal using a queue, height versus depth, and why postorder is useful when deleting a tree. I still need more practice tracing larger recursive trees by hand.
