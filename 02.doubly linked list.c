#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *prev, *next;
};

struct Node *head = NULL, *tail = NULL;

struct Node *createNode(int value) {
    struct Node *n = malloc(sizeof(struct Node));
    if (n == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    n->data = value;
    n->prev = n->next = NULL;
    return n;
}

void insertBeginning(int value) {
    struct Node *n = createNode(value);

    if (head == NULL)
        head = tail = n;
    else {
        n->next = head;
        head->prev = n;
        head = n;
    }
}

void insertEnd(int value) {
    struct Node *n = createNode(value);

    if (tail == NULL)
        head = tail = n;
    else {
        tail->next = n;
        n->prev = tail;
        tail = n;
    }
}

void deleteBeginning(void) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }

    struct Node *temp = head;
    head = head->next;

    if (head != NULL)
        head->prev = NULL;
    else
        tail = NULL;

    free(temp);
    printf("Node deleted.\n");
}

void deleteEnd(void) {
    if (tail == NULL) {
        printf("List is empty!\n");
        return;
    }

    struct Node *temp = tail;
    tail = tail->prev;

    if (tail != NULL)
        tail->next = NULL;
    else
        head = NULL;

    free(temp);
    printf("Node deleted.\n");
}

void displayForward(void) {
    struct Node *temp = head;

    if (temp == NULL) {
        printf("List is empty!\n");
        return;
    }

    printf("Forward: ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void displayBackward(void) {
    struct Node *temp = tail;

    if (temp == NULL) {
        printf("List is empty!\n");
        return;
    }

    printf("Backward: ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->prev;
    }
    printf("NULL\n");
}

void search(int value) {
    struct Node *temp = head;
    int pos = 1;

    while (temp != NULL) {
        if (temp->data == value) {
            printf("Found at position %d.\n", pos);
            return;
        }
        temp = temp->next;
        pos++;
    }

    printf("Value not found!\n");
}

void freeList(void) {
    while (head != NULL) {
        struct Node *temp = head;
        head = head->next;
        free(temp);
    }
    tail = NULL;
}

int main(void) {
    int choice, value;

    do {
        printf("\n--- DOUBLY LINKED LIST ---\n");
        printf("1.Insert Beginning  2.Insert End\n");
        printf("3.Delete Beginning  4.Delete End\n");
        printf("5.Display Forward  6.Display Backward\n");
        printf("7.Search  8.Exit\nChoice: ");

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
                displayForward();
                break;

            case 6:
                displayBackward();
                break;

            case 7:
                printf("Enter value: ");
                if (scanf("%d", &value) != 1) {
                    freeList();
                    return 1;
                }
                search(value);
                break;

            case 8:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 8);

    freeList();
    return 0;
}
