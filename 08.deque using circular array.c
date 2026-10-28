#include <stdio.h>

#define MAX 5

int deque[MAX];
int front = -1, rear = -1;

int isEmpty(void) {
    return front == -1;
}

int isFull(void) {
    return (rear + 1) % MAX == front;
}

void insertFront(int value) {
    if (isFull()) {
        printf("Deque Overflow!\n");
        return;
    }

    if (isEmpty())
        front = rear = 0;
    else
        front = (front - 1 + MAX) % MAX;

    deque[front] = value;
    printf("%d inserted at front.\n", value);
}

void insertRear(int value) {
    if (isFull()) {
        printf("Deque Overflow!\n");
        return;
    }

    if (isEmpty())
        front = rear = 0;
    else
        rear = (rear + 1) % MAX;

    deque[rear] = value;
    printf("%d inserted at rear.\n", value);
}

void deleteFront(void) {
    if (isEmpty()) {
        printf("Deque Underflow!\n");
        return;
    }

    printf("Deleted from front: %d\n", deque[front]);

    if (front == rear)
        front = rear = -1;
    else
        front = (front + 1) % MAX;
}

void deleteRear(void) {
    if (isEmpty()) {
        printf("Deque Underflow!\n");
        return;
    }

    printf("Deleted from rear: %d\n", deque[rear]);

    if (front == rear)
        front = rear = -1;
    else
        rear = (rear - 1 + MAX) % MAX;
}

void display(void) {
    if (isEmpty()) {
        printf("Deque is empty!\n");
        return;
    }

    printf("Deque: ");
    int i = front;

    while (1) {
        printf("%d ", deque[i]);
        if (i == rear)
            break;
        i = (i + 1) % MAX;
    }

    printf("\n");
}

int main(void) {
    int choice, value;

    do {
        printf("\n--- DEQUE ---\n");
        printf("1.Insert Front  2.Insert Rear\n");
        printf("3.Delete Front  4.Delete Rear\n");
        printf("5.Display  6.Exit\nChoice: ");

        if (scanf("%d", &choice) != 1)
            return 1;

        switch (choice) {
            case 1:
                printf("Enter value: ");
                if (scanf("%d", &value) != 1)
                    return 1;
                insertFront(value);
                break;
            case 2:
                printf("Enter value: ");
                if (scanf("%d", &value) != 1)
                    return 1;
                insertRear(value);
                break;
            case 3:
                deleteFront();
                break;
            case 4:
                deleteRear();
                break;
            case 5:
                display();
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 6);

    return 0;
}
