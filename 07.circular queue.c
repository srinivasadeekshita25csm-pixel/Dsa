#include <stdio.h>

#define MAX 5

int queue[MAX];
int front = -1, rear = -1;

int isEmpty(void) {
    return front == -1;
}

int isFull(void) {
    return (rear + 1) % MAX == front;
}

void enqueue(int value) {
    if (isFull()) {
        printf("Circular Queue Overflow!\n");
        return;
    }

    if (isEmpty())
        front = 0;

    rear = (rear + 1) % MAX;
    queue[rear] = value;
    printf("%d inserted.\n", value);
}

void dequeue(void) {
    if (isEmpty()) {
        printf("Circular Queue Underflow!\n");
        return;
    }

    printf("Deleted element: %d\n", queue[front]);

    if (front == rear)
        front = rear = -1;
    else
        front = (front + 1) % MAX;
}

void peek(void) {
    if (isEmpty())
        printf("Queue is empty!\n");
    else
        printf("Front element: %d\n", queue[front]);
}

void display(void) {
    if (isEmpty()) {
        printf("Queue is empty!\n");
        return;
    }

    printf("Queue: ");
    int i = front;

    while (1) {
        printf("%d ", queue[i]);
        if (i == rear)
            break;
        i = (i + 1) % MAX;
    }

    printf("\n");
}

int main(void) {
    int choice, value;

    do {
        printf("\n--- CIRCULAR QUEUE ---\n");
        printf("1.Enqueue  2.Dequeue  3.Peek  4.Display  5.Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
            return 1;

        switch (choice) {
            case 1:
                printf("Enter value: ");
                if (scanf("%d", &value) != 1)
                    return 1;
                enqueue(value);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                peek();
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
