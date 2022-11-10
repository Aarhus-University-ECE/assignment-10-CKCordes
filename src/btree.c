#include "btree.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct tree_node *Insert(int x, struct tree_node *t) {
    if (t == NULL) {
        // Base case, I allocate memory for the new node and initialize its
        // values
        t = (struct tree_node *)malloc(sizeof(struct tree_node));
        t->item = x;
        t->left = NULL;
        t->right = NULL;
        return t;
    }
    // The recursive steps, if the value we wish to insert is greater than the
    // current node, i go to the right, if smaller i go left.
    if (x > t->item) {
        t->right = Insert(x, t->right);
    }
    if (x < t->item) {
        t->left = Insert(x, t->left);
    }
    // The edge case: if the value we wish to insert is equal the nodes item,
    // its inserted right underneath to the left
    if (x == t->item) {
        struct tree_node *newNode = malloc(sizeof(struct tree_node));
        newNode->item = x;
        newNode->left = t->left;
        newNode->right = NULL;
        t->left = newNode;
    }
    return t;
}

struct tree_node *Remove(int x, struct tree_node *t) {
    // if the tree is empty, it returns the empty tree
    if (t == NULL) {
        return t;
    }
    // If the tree doesnt contain the value x we just return the root
    if (!Contains(x, t)) {
        return t;
    } else if (x == t->item) {
        // We have found the node, we have two cases:
        // First up, if the node has one or zero branches

        if (t->left == NULL) {
            // if it doesnt have a left node, we grab the node to the right and
            // return it, as we can "shuffle" it up

            struct tree_node *newInPlace = t->right;
            free(t);
            return newInPlace;
        } else if (t->right == NULL) {
            // Same principle for an empty right child, i shuffle the node to
            // the left and shuffle it up

            struct tree_node *newInPlace = t->left;
            free(t);
            return newInPlace;
        } else {
            // If it has two children i set a temporary pointer equal to one
            // step to the right, and then i run it as far left as possible

            struct tree_node *temp = t->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            // I give the
            t->item = temp->item;
            free(temp);
            return t;
        }
    }

    else if (x > t->item) {
        printf("\nSearching right\n");
        t->right = Remove(x, t->right);

    } else if (x < t->item) {
        printf("\nSearching left\n");
        t->left = Remove(x, t->left);
    }

    return t;
}

int Contains(int x, struct tree_node *t) {
    // Return true if the tree t contains item x. Return false otherwise.

    if (Empty(t)) {
        return 0;
    }
    if (x == t->item) {
        return 1;
        printf("contains %d\n", x);
    } else if (x > t->item) {
        return Contains(x, t->right);
    } else if (x < t->item) {
        return Contains(x, t->left);
    }
    return 0;
}

struct tree_node *Initialize(struct tree_node *t) {
    t = NULL;
    return t;
}

int Empty(struct tree_node *t) {
    if (t == NULL) {
        return 1;
    } else {
        return 0;
    }
}

int Full(struct tree_node *t) {
    // Can never be full, therefore returns false
    return 0;
}
