#include "linked_list.h"

#include <assert.h> /* assert */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */

/* functions to create lists */
node *make_node(int v, node *q) {
    node *p = malloc(sizeof(node));
    p->value = v;
    p->next = q;
    return p;
}

/* free all nodes in the list p */
void free_list(node *p) {
    node *q;
    while (p != NULL) {
        q = p->next;
        free(p);
        p = q;
    }
}

/* print list to console */
void print_list(node *p) {
    // Basecase
    if (p == NULL) {
        return;
    }
    // Printing the lists value
    int t = p->value;
    printf("%d, ", t);
    // Recursive step
    print_list(p->next);
}

int sum_squares(node *p) {
    // Basecase
    if (p == NULL) {
        return 0;
    } else {
        // returning the current value squared, added with the next values
        // squared
        return p->value * p->value + sum_squares(p->next);
    }
}

typedef int (*fn_int_to_int)(int);

node *map(node *p, fn_int_to_int f) {
    // Basecase
    if (p == NULL) {
        return NULL;
    } else {
        // Since we are making a new list, we must return a node, the value of
        // that node being the squared value of pvalue, and the next node being
        // the next map made node
        return make_node(f(p->value), map(p->next, f));
    }
}

int square(int x) { return x * x; }

// example of another function that can be passed to map
// returns the sign of the number
// -1 if negative, 0 if zero, 1 if positive
int sign(int x) { return x == 0 ? 0 : (x < 0 ? -1 : 1); }
