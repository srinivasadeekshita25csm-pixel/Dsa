#include <stdio.h>
#include <stdlib.h>

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
    else
        printf("Duplicate value ignored.\n");

    return root;
}

struct Node *minimum(struct Node *root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

struct Node *deleteNode(struct Node *root, int value) {
    if (root == NULL)
        return NULL;

    if (value < root->data)
        root->left = deleteNode(root->left, value);
    else if (value > root->data)
        root->right = deleteNode(root->right, value);
    else {
        if (root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }

        if (root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        struct Node *temp = minimum(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct Node *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

int search(struct Node *root, int value) {
    while (root != NULL) {
        if (value == root->data)
            return 1;

        if (value < root->data)
            root = root->left;
        else
            root = root->right;
    }

    return 0;
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
    int choice, value;

    do {
        printf("\n--- BINARY SEARCH TREE ---\n");
        printf("1.Insert  2.Delete  3.Search\n");
        printf("4.Inorder  5.Preorder  6.Postorder  7.Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            freeTree(root);
            return 1;
        }

        switch (choice) {
            case 1:
                printf("Enter value: ");
                if (scanf("%d", &value) != 1) {
                    freeTree(root);
                    return 1;
                }
                root = insert(root, value);
                break;

            case 2:
                printf("Enter value to delete: ");
                if (scanf("%d", &value) != 1) {
                    freeTree(root);
                    return 1;
                }

                if (!search(root, value))
                    printf("Value not found!\n");
                else {
                    root = deleteNode(root, value);
                    printf("Value deleted.\n");
                }
                break;

            case 3:
                printf("Enter value to search: ");
                if (scanf("%d", &value) != 1) {
                    freeTree(root);
                    return 1;
                }

                if (search(root, value))
                    printf("Value found.\n");
                else
                    printf("Value not found.\n");
                break;

            case 4:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;

            case 5:
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                break;

            case 6:
                printf("Postorder: ");
                postorder(root);
                printf("\n");
                break;

            case 7:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 7);

    freeTree(root);
    return 0;
}
