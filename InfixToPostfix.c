#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Stack for operators in infix to postfix conversion
typedef struct {
    char data[100];
    int top;
} OperatorStack;

void initOperatorStack(OperatorStack *s) {
    s->top = -1;
}

void pushOperator(OperatorStack *s, char c) {
    s->data[++(s->top)] = c;
}

char popOperator(OperatorStack *s) {
    if (s->top == -1)
        return '\0';
    return s->data[(s->top)--];
}

char peekOperator(OperatorStack *s) {
    if (s->top == -1)
        return '\0';
    return s->data[s->top];
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int precedence(char c) {
    switch(c) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        default: return 0;
    }
}

void infixToPostfix(char* infix, char* postfix) {
    OperatorStack s;
    initOperatorStack(&s);
    int k = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        if (isdigit(infix[i])) {
            postfix[k++] = infix[i];
        } else if (infix[i] == '(') {
            pushOperator(&s, infix[i]);
        } else if (infix[i] == ')') {
            while (peekOperator(&s) != '(') {
                postfix[k++] = popOperator(&s);
            }
            popOperator(&s);  // pop '('
        } else if (isOperator(infix[i])) {
            while (precedence(peekOperator(&s)) >= precedence(infix[i])) {
                postfix[k++] = popOperator(&s);
            }
            pushOperator(&s, infix[i]);
        }
    }
    while (s.top != -1) {
        postfix[k++] = popOperator(&s);
    }
    postfix[k] = '\0';
}

// Stack for operands in postfix evaluation
typedef struct {
    int data[100];
    int top;
} OperandStack;

void initOperandStack(OperandStack *s) {
    s->top = -1;
}

void pushOperand(OperandStack *s, int value) {
    s->data[++(s->top)] = value;
}

int popOperand(OperandStack *s) {
    if (s->top == -1)
        return -1;
    return s->data[(s->top)--];
}

int evaluatePostfix(char* postfix) {
    OperandStack s;
    initOperandStack(&s);
    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isdigit(postfix[i])) {
            pushOperand(&s, postfix[i] - '0');
        } else if (isOperator(postfix[i])) {
            int val2 = popOperand(&s);
            int val1 = popOperand(&s);
            switch(postfix[i]) {
                case '+': pushOperand(&s, val1 + val2); break;
                case '-': pushOperand(&s, val1 - val2); break;
                case '*': pushOperand(&s, val1 * val2); break;
                case '/': pushOperand(&s, val1 / val2); break;
            }
        }
    }
    return popOperand(&s);
}

int main() {
    char infix[100], postfix[100];
    printf("Enter infix expression: ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    int result = evaluatePostfix(postfix);
    printf("Result of evaluation: %d\n", result);
    return 0;
}
