//
// Created by rx on 12/28/16.
//

#ifndef BINARYTREE_BINARYTREE_H
#define BINARYTREE_BINARYTREE_H
#include <iostream>

/*----------subroutine declaration---------*/
struct node *newNode(int data);

static int lookup(struct node *node, int target);

struct node *insert(struct node *node, int data);

struct node *build123a();

struct node *build123b();

struct node *build123c();

int minValue(struct node *node);

void printPreorder(struct node *node);

void printPostorder(struct node *node);

int hasPathSum(struct node *node, int sum);

void printPathsRecur(struct node *node, int path[], int pathLen);

void mirror(struct node *node);

void doubleTree(struct node *node);

int sameTree(struct node *a, struct node *b);

struct node {
    int data;
    struct node *left;
    struct node *right;
};

/*
 Helper function that allocates a new node
 with the given data and NULL left and right
 pointers.
 * */
struct node *newNode(int data) {
    struct node *node = new (struct node);
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return (node);
}

static int lookup(struct node *node, int target) {
    if (node == NULL) {
        return false;
    } else {
        if (target == node->data) return true;
        else {
            if (target < node->data) return (lookup(node->left, target));
            else return (lookup(node->right, target));
        }
    }
}

/*
 Give a binary search tree and a number, inserts a new node
 with the given number in the correct place in the tree.
 Returns the new root pointer which the caller should
 then use (the standard trick to avoid using reference
 parameters).
*/
struct node *insert(struct node *node, int data) {
    // 1. If the tree is empty, return a new, single node
    if (node == NULL) {
        return (newNode(data));
    } else {
        // 2. Otherwise, recur down the tree
        if (data <= node->data) node->left = insert(node->left, data);
        else node->right = insert(node->right, data);

        return (node); // return the (unchanged) node pointer
    }
}

// call newNode() three times
struct node *build123a() {
    struct node *root = newNode(2);
    struct node *lChild = newNode(1);
    struct node *rChild = newNode(3);
    root->left = lChild;
    root->right = rChild;
    return root;
}

// call newNode() three times, and use only one lcoal variable
struct node *build123b() {
    struct node *root = newNode(2);
    root->left = newNode(1);
    root->right = newNode(3);
    return root;
}

struct node *build123c() {
    struct node *root = NULL;
    root = insert(root, 2);
    root = insert(root, 1);
    root = insert(root, 3);
}

/*
 Compute the number of nodes in a tree.
*/
int size(struct node *node) {
    if (node == NULL) {
        return 0;
    } else {
        return size(node->left) + 1 + size(node->right);
    }
}

/*
 Compute the "maxDepth" of a tree -- the number of nodes along
 the longest path from the root node down to the farthest leaf node.
*/
int maxDepth(struct node *node) {
    if (node == NULL) {
        return 0;
    } else {
        int lDepth = maxDepth(node->left);
        int rDepth = maxDepth(node->right);
        // use the larger one
        if (lDepth > rDepth) return lDepth + 1;
        else return rDepth + 1;
    }
}

/*
 Given a non-empty binary search tree,
 return the minimum data value found in that tree.
 Note that the entire tree does not need to be searched.
*/
int minValue(struct node *node) {
    struct node *current = node;
    // loop down to find the leftmost leaf
    while (current->left != NULL) {
        current = current->left;
    }
    return current->data;
}

/*
 Given a binary search tree, print out
 its data elements in increasing
 sorted order.
*/
void printPreorder(struct node *node) {
    if (node == NULL) return;

    printPreorder(node->left);
    printf("%d ", node->data);
    printPreorder(node->right);
}

/*
 Given a binary tree, print its
 nodes according to the "bottom-up"
 postorder traversal.
*/
void printPostorder(struct node *node) {
    if (node == NULL) return;

    printPreorder(node->left);
    printPreorder(node->right);
    printf("%d ", node->data);
}

/*
 Given a tree and a sum, return true if there is a path from the root
 down to a leaf, such that adding up all the values along the path
 equals the given sum.

 Strategy: subtract the node value from the sum when recurring down,
 and check to see if the sum is 0 when you run out of tree.
*/
int hasPathSum(struct node *node, int sum) {
    if (node == NULL) {
        return (sum == 0);
    } else { // otherwise check both subtrees
        int subSum = sum - node->data;
        return hasPathSum(node->left, subSum) || hasPathSum(node->right, subSum);
    }
}

void printArray(int *a, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void printPathsRecur(struct node *node, int path[], int pathLen) {
    if (node == NULL) return;

    path[pathLen] = node->data;
    pathLen++;

    if (node->left == NULL && node->right == NULL) {
        printArray(path, pathLen);
    } else {
        // otherwise try both subtrees
        printPathsRecur(node->left, path, pathLen);
        printPathsRecur(node->right, path, pathLen);
    }
}

void printPaths(struct node *node) {
    int path[1000];

    printPathsRecur(node, path, 0);
}

/*
 Change a tree so that the roles of the
 left and right pointers are swapped at every node.

 So the tree...
       4
      / \
     2   5
    / \
   1   3

 is changed to...
       4
      / \
     5   2
        / \
       3   1
*/
void mirror(struct node *node) {
    if (node == NULL) return;
    else {
        struct node *tmp;

        // do the subtrees
        mirror(node->left);
        mirror(node->right);

        // swap the pointers in this node
        tmp = node->left;
        node->left = node->right;
        node->right = tmp;
    }
}

/*
10. doubleTree() Solution (C/C++)

For each node in a binary search tree,
create a new duplicate node, and insert
the duplicate as the left child of the original node.
The resulting tree should still be a binary search tree.

So the tree...
   2
  / \
 1   3

Is changed to...
      2
     / \
    2   3
   /   /
  1   3
 /
1

*/
void doubleTree(struct node *node) {
    struct node *oldLeft;
    if (node == NULL) return;

    // do the subtrees
    doubleTree(node->left);
    doubleTree(node->right);

    //duplicate this node to its left
    oldLeft = node->left;
    node->left = newNode(node->data);
    node->left->left = oldLeft;
}

/*
 Given two trees, return true if they are
 structurally identical.
*/
int sameTree(struct node *a, struct node *b) {
    // 1. both empty -> true
    if (a == NULL && b == NULL) return true;
        // 2. both non-empty -> compare them
    else if (a != NULL && b != NULL) {
        return (a->data == b->data && sameTree(a->left, b->left) && sameTree(a->right, b->right));
    }
        // 3. one empty, one not -> false
    else return false;
}

void Drive() {
    struct node *root = build123b();

    printf("maxDepth : %d\n", maxDepth(root));

    printPostorder(root);

    printf("\n%d\n", hasPathSum(root, 6));

    printPaths(root);


    doubleTree(root);
    printPaths(root);
}
#endif //BINARYTREE_BINARYTREE_H
