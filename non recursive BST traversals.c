#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node *createNode(int value) {
    struct Node *n = malloc(sizeof(struct Node));

    if (n == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    n->data = value;
    n->left = n->right = NULL;
    return n;
}

struct Node *insert(struct Node *root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);

    return root;
}

void inorder(struct Node *root) {
    struct Node *stack[MAX];
    int top = -1;
    struct Node *current = root;

    while (current != NULL || top != -1) {
        while (current != NULL) {
            if (top == MAX - 1) {
                printf("Stack capacity exceeded!\n");
                return;
            }
            stack[++top] = current;
            current = current->left;
        }

        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }
}

void preorder(struct Node *root) {
    if (root == NULL)
        return;

    struct Node *stack[MAX];
    int top = -1;
    stack[++top] = root;

    while (top != -1) {
        struct Node *current = stack[top--];
        printf("%d ", current->data);

        if (current->right != NULL) {
            if (top == MAX - 1) {
                printf("Stack capacity exceeded!\n");
                return;
            }
            stack[++top] = current->right;
        }

        if (current->left != NULL) {
            if (top == MAX - 1) {
                printf("Stack capacity exceeded!\n");
                return;
            }
            stack[++top] = current->left;
        }
    }
}

void postorder(struct Node *root) {
    if (root == NULL)
        return;

    struct Node *s1[MAX], *s2[MAX];
    int top1 = -1, top2 = -1;

    s1[++top1] = root;

    while (top1 != -1) {
        struct Node *current = s1[top1--];

        if (top2 == MAX - 1) {
            printf("Stack capacity exceeded!\n");
            return;
        }

        s2[++top2] = current;

        if (current->left != NULL) {
            if (top1 == MAX - 1) {
                printf("Stack capacity exceeded!\n");
                return;
            }
            s1[++top1] = current->left;
        }

        if (current->right != NULL) {
            if (top1 == MAX - 1) {
                printf("Stack capacity exceeded!\n");
                return;
            }
            s1[++top1] = current->right;
        }
    }

    while (top2 != -1)
        printf("%d ", s2[top2--]->data);
}

void freeTree(struct Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main(void) {
    struct Node *root = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++)
        root = insert(root, values[i]);

    printf("BST created using fixed values.\n");

    printf("Non-recursive Inorder: ");
    inorder(root);

    printf("\nNon-recursive Preorder: ");
    preorder(root);

    printf("\nNon-recursive Postorder: ");
    postorder(root);

    printf("\n");

    freeTree(root);
    return 0;
}