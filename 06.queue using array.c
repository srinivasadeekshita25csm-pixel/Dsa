#include <stdio.h>

#define MAX 5

int queue[MAX];
int front = -1, rear = -1;

void enqueue(int value) {
    if (rear == MAX - 1) {
        printf("Queue Overflow!\n");
        return;
    }

    if (front == -1)
        front = 0;

    queue[++rear] = value;
    printf("%d inserted.\n", value);
}

void dequeue(void) {
    if (front == -1) {
        printf("Queue Underflow!\n");
        return;
    }

    printf("Deleted element: %d\n", queue[front++]);

    if (front > rear)
        front = rear = -1;
}

void peek(void) {
    if (front == -1)
        printf("Queue is empty!\n");
    else
        printf("Front element: %d\n", queue[front]);
}

void display(void) {
    if (front == -1) {
        printf("Queue is empty!\n");
        return;
    }

    printf("Queue: ");
    for (int i = front; i <= rear; i++)
        printf("%d ", queue[i]);
    printf("\n");
}

int main(void) {
    int choice, value;

    do {
        printf("\n--- LINEAR QUEUE ---\n");
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
