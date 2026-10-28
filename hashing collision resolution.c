#include <stdio.h>

#define SIZE 10
#define EMPTY -1
#define DELETED -2

int table[SIZE];

void initialize(void) {
    for (int i = 0; i < SIZE; i++)
        table[i] = EMPTY;
}

int hashFunction(int key) {
    return ((key % SIZE) + SIZE) % SIZE;
}

void insert(int key) {
    int index = hashFunction(key);

    for (int i = 0; i < SIZE; i++) {
        int pos = (index + i) % SIZE;

        if (table[pos] == key) {
            printf("Key already exists!\n");
            return;
        }

        if (table[pos] == EMPTY || table[pos] == DELETED) {
            table[pos] = key;
            printf("Key inserted at index %d.\n", pos);
            return;
        }
    }

    printf("Hash table is full!\n");
}

int search(int key) {
    int index = hashFunction(key);

    for (int i = 0; i < SIZE; i++) {
        int pos = (index + i) % SIZE;

        if (table[pos] == EMPTY)
            return -1;

        if (table[pos] == key)
            return pos;
    }

    return -1;
}

void deleteKey(int key) {
    int pos = search(key);

    if (pos == -1) {
        printf("Key not found!\n");
        return;
    }

    table[pos] = DELETED;
    printf("Key deleted.\n");
}

void display(void) {
    printf("\nIndex\tValue\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%d\t", i);

        if (table[i] == EMPTY)
            printf("EMPTY\n");
        else if (table[i] == DELETED)
            printf("DELETED\n");
        else
            printf("%d\n", table[i]);
    }
}

int main(void) {
    int choice, key;

    initialize();

    do {
        printf("\n--- HASHING ---\n");
        printf("1.Insert  2.Search  3.Delete  4.Display  5.Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
            return 1;

        switch (choice) {
            case 1:
                printf("Enter key: ");
                if (scanf("%d", &key) != 1)
                    return 1;

                if (key == EMPTY || key == DELETED) {
                    printf("Keys -1 and -2 are reserved!\n");
                    break;
                }

                insert(key);
                break;

            case 2:
                printf("Enter key to search: ");
                if (scanf("%d", &key) != 1)
                    return 1;

                int pos = search(key);
                if (pos == -1)
                    printf("Key not found!\n");
                else
                    printf("Key found at index %d.\n", pos);
                break;

            case 3:
                printf("Enter key to delete: ");
                if (scanf("%d", &key) != 1)
                    return 1;
                deleteKey(key);
                break;

            case 4:
                display();
                break;

            case 5:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}