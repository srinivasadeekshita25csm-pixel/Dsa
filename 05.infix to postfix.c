#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX 100

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' ||
           c == '/' || c == '^';
}

int infixToPostfix(char infix[], char postfix[]) {
    char stack[MAX];
    int top = -1, j = 0;
    int expectOperand = 1;

    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];

        if (isspace((unsigned char)c))
            continue;

        if (isdigit((unsigned char)c)) {
            if (!expectOperand)
                return 0;
            postfix[j++] = c;
            expectOperand = 0;
        } else if (c == '(') {
            if (!expectOperand)
                return 0;
            stack[++top] = c;
        } else if (c == ')') {
            if (expectOperand)
                return 0;

            while (top >= 0 && stack[top] != '(')
                postfix[j++] = stack[top--];

            if (top < 0)
                return 0;

            top--;
            expectOperand = 0;
        } else if (isOperator(c)) {
            if (expectOperand)
                return 0;

            while (top >= 0 && stack[top] != '(' &&
                  (precedence(stack[top]) > precedence(c) ||
                  (precedence(stack[top]) == precedence(c) &&
                   c != '^'))) {
                postfix[j++] = stack[top--];
            }

            stack[++top] = c;
            expectOperand = 1;
        } else {
            return 0;
        }

        if (j >= MAX - 1)
            return 0;
    }

    if (expectOperand)
        return 0;

    while (top >= 0) {
        if (stack[top] == '(')
            return 0;
        postfix[j++] = stack[top--];
    }

    postfix[j] = '\0';
    return 1;
}

int evaluatePostfix(char postfix[], double *result) {
    double stack[MAX];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];

        if (isdigit((unsigned char)c)) {
            if (top >= MAX - 1)
                return 0;
            stack[++top] = c - '0';
        } else if (isOperator(c)) {
            if (top < 1)
                return 0;

            double b = stack[top--];
            double a = stack[top--];
            double r;

            switch (c) {
                case '+': r = a + b; break;
                case '-': r = a - b; break;
                case '*': r = a * b; break;
                case '/':
                    if (b == 0)
                        return 0;
                    r = a / b;
                    break;
                case '^': r = pow(a, b); break;
                default: return 0;
            }

            stack[++top] = r;
        } else {
            return 0;
        }
    }

    if (top != 0)
        return 0;

    *result = stack[top];
    return 1;
}

int main(void) {
    char infix[MAX], postfix[MAX];
    double result;

    printf("Enter infix expression: ");

    if (fgets(infix, sizeof(infix), stdin) == NULL)
        return 1;

    infix[strcspn(infix, "\n")] = '\0';

    if (!infixToPostfix(infix, postfix)) {
        printf("Invalid infix expression!\n");
        return 1;
    }

    printf("Postfix expression: %s\n", postfix);

    if (!evaluatePostfix(postfix, &result)) {
        printf("Evaluation failed!\n");
        return 1;
    }

    printf("Result: %.2f\n", result);
    return 0;
}
