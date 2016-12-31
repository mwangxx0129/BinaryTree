//
// Created by rx on 12/28/16.
//

#ifndef BINARYTREE_BINARYTREEPRATICE_H
#define BINARYTREE_BINARYTREEPRATICE_H

#include <iostream>

/*----------subroutine declaration---------*/
struct node *newNode(int data);

struct node *build123();

static int lookup(struct node *node, int target);

struct node *insert(struct node *node, int data);

void printPreorder(struct node *node);

void printInorder(struct node *node);

void printPostorder(struct node *node);

int minValue(struct node *node);

void printPathsRecur(struct node *node, int path[], int pathLen);

void mirror(struct node *node);

int hasPathSum(struct node *node, int sum);

void doubleTree(struct node *node);

int sameTree(struct node *a, struct node *b);

struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct node *newNode(int data) {
    struct node *new_node = new(struct node);
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

struct node *build123() {
    struct node *root = newNode(2);
    root->left = newNode(1);
    root->right = newNode(3);
}

static int lookup(struct node *node, int target) {
    if (node == NULL) return false;
    if (node->data == target) return true;
    else {
        if (node->data > target) return lookup(node->left, target);
        else return lookup(node->right, target);
    }
}

struct node *insert(struct node *node, int data) {
    if (node == NULL) {
        return newNode(data);
    }

    if (node->data >= data) {
        node->left = insert(node->left, data);
    } else {
        node->right = insert(node->right, data);
    }
    return node;
}

/**
 * 1. Check if the current node is empty
 * 2. Display the data part of the root (or current node)
 * 3. Traverse the left subtree by recursively calling the Pre-order function
 * 4. Traverse the right subtree by recursively calling the Pre-order function
 * @param node of tree
 */
void printPreorder(struct node *node) {
    if (node == NULL) return;
    printf("%d ", node->data);
    printPreorder(node->left);
    printPreorder(node->right);
}

/**
 * In a search tree, In-order traversal retrieves data in sorted order
 * 1. Check if the current node is empty
 * 2. Traverse the left subtree by recursively calling the In-order function
 * 3. Display the data part of the root (or current node)
 * 4. Traverse the right subtree by recursively calling the In-order function
 * @param node
 */
void printInorder(struct node *node) {
    if (node == NULL) return;
    printPreorder(node->left);
    printf("%d ", node->data);
    printPreorder(node->right);
}

/**
 * 1. Check if the current node is empty
 * 2. Traverse the left subtree by recursively calling the Post-order function
 * 3. Traverse the right subtree by recursively calling the Post-order function
 * 4. Display the data part of root (or current node)
 * @param node
 */
void printPostorder(struct node *node) {
    if (node == NULL) return;
    printPostorder(node->left);
    printPostorder(node->right);
    printf("%d ", node->data);
}

void mirror(struct node *node) {
    if (node == NULL) return;
    mirror(node->left);
    mirror(node->right);
    // swap left subtree with right
    struct node *tmp = node->left;
    node->left = node->right;
    node->right = tmp;
}

void printArray(int path[], int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", path[i]);
    }
}

void printPathsRecur(struct node *node, int path[], int pathLen) {
    if (node == NULL) return;
    path[pathLen++] = node->data;
    if (node->left == NULL && node->right == NULL)
        printArray(path, pathLen);
    else {
        printPathsRecur(node->left, path, pathLen);
        printPathsRecur(node->right, path, pathLen);
    }
}

int minValue(struct node *node){
    struct node * current = node;
    while(current->left != NULL){
        current = current->left;
    }
    return current->data;
}
int hasPathSum(struct node *node, int sum){
    if(node == NULL) return false;
    if(node->left == NULL && node->right == NULL)
        return sum == node->data;
    int subSum = sum-node->data;
    return hasPathSum(node->left, subSum) || hasPathSum(node->right, subSum);

}
void DriveTest() {
    struct node *root = build123();
    int path[1000];
    printPathsRecur(root, path, 0);

}

#endif //BINARYTREE_BINARYTREEPRATICE_H
