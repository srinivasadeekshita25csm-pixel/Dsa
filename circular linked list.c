#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *last = NULL;

struct Node *createNode(int value) {
    struct Node *n = malloc(sizeof(struct Node));
    if (n == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    n->data = value;
    n->next = NULL;
    return n;
}

void insertBeginning(int value) {
    struct Node *n = createNode(value);

    if (last == NULL) {
        last = n;
        n->next = n;
    } else {
        n->next = last->next;
        last->next = n;
    }
}

void insertEnd(int value) {
    insertBeginning(value);
    last = last->next;
}

void deleteBeginning(void) {
    if (last == NULL) {
        printf("List is empty!\n");
        return;
    }

    struct Node *first = last->next;

    if (first == last)
        last = NULL;
    else
        last->next = first->next;

    free(first);
    printf("Node deleted.\n");
}

void deleteEnd(void) {
    if (last == NULL) {
        printf("List is empty!\n");
        return;
    }

    struct Node *first = last->next;

    if (first == last) {
        free(last);
        last = NULL;
        printf("Node deleted.\n");
        return;
    }

    struct Node *temp = first;
    while (temp->next != last)
        temp = temp->next;

    temp->next = first;
    free(last);
    last = temp;
    printf("Node deleted.\n");
}

void display(void) {
    if (last == NULL) {
        printf("List is empty!\n");
        return;
    }

    struct Node *temp = last->next;
    printf("Circular List: ");

    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != last->next);

    printf("(back to first node)\n");
}

void search(int value) {
    if (last == NULL) {
        printf("List is empty!\n");
        return;
    }

    struct Node *temp = last->next;
    int pos = 1;

    do {
        if (temp->data == value) {
            printf("Found at position %d.\n", pos);
            return;
        }
        temp = temp->next;
        pos++;
    } while (temp != last->next);

    printf("Value not found!\n");
}

void freeList(void) {
    if (last == NULL)
        return;

    struct Node *first = last->next;
    last->next = NULL;

    while (first != NULL) {
        struct Node *temp = first;
        first = first->next;
        free(temp);
    }

    last = NULL;
}

int main(void) {
    int choice, value;

    do {
        printf("\n--- CIRCULAR LINKED LIST ---\n");
        printf("1.Insert Beginning  2.Insert End\n");
        printf("3.Delete Beginning  4.Delete End\n");
        printf("5.Display  6.Search  7.Exit\nChoice: ");

        if (scanf("%d", &choice) != 1) {
            freeList();
            return 1;
        }

        switch (choice) {
            case 1:
                printf("Enter value: ");
                if (scanf("%d", &value) != 1) {
                    freeList();
                    return 1;
                }
                insertBeginning(value);
                break;

            case 2:
                printf("Enter value: ");
                if (scanf("%d", &value) != 1) {
                    freeList();
                    return 1;
                }
                insertEnd(value);
                break;

            case 3:
                deleteBeginning();
                break;

            case 4:
                deleteEnd();
                break;

            case 5:
                display();
                break;

            case 6:
                printf("Enter value: ");
                if (scanf("%d", &value) != 1) {
                    freeList();
                    return 1;
                }
                search(value);
                break;

            case 7:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 7);

    freeList();
    return 0;
}