#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Stack for operators and operands
typedef struct {
    char data[100];
    int top;
} CharStack;

typedef struct {
    int data[100];
    int top;
} IntStack;

void initCharStack(CharStack *s) {
    s->top = -1;
}

void pushChar(CharStack *s, char c) {
    s->data[++(s->top)] = c;
}

char popChar(CharStack *s) {
    if (s->top == -1)
        return '\0';
    return s->data[(s->top)--];
}

char peekChar(CharStack *s) {
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
    CharStack s;
    initCharStack(&s);
    int k = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        if (isdigit(infix[i])) {
            postfix[k++] = infix[i];
        } else if (infix[i] == '(') {
            pushChar(&s, infix[i]);
        } else if (infix[i] == ')') {
            while (peekChar(&s) != '(') {
                postfix[k++] = popChar(&s);
            }
            popChar(&s);  // pop '('
        } else if (isOperator(infix[i])) {
            while (precedence(peekChar(&s)) >= precedence(infix[i])) {
                postfix[k++] = popChar(&s);
            }
            pushChar(&s, infix[i]);
        }
    }
    while (s.top != -1) {
        postfix[k++] = popChar(&s);
    }
    postfix[k] = '\0';
}

void reverseString(char* str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

void replaceParentheses(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(') {
            str[i] = ')';
        } else if (str[i] == ')') {
            str[i] = '(';
        }
    }
}

void infixToPrefix(char* infix, char* prefix) {
    reverseString(infix);
    replaceParentheses(infix);
    char postfix[100];
    infixToPostfix(infix, postfix);
    reverseString(postfix);
    strcpy(prefix, postfix);
}

void initIntStack(IntStack *s) {
    s->top = -1;
}

void pushInt(IntStack *s, int value) {
    s->data[++(s->top)] = value;
}

int popInt(IntStack *s) {
    if (s->top == -1)
        return -1;
    return s->data[(s->top)--];
}

int evaluatePrefix(char* prefix) {
    IntStack s;
    initIntStack(&s);
    int n = strlen(prefix);
    for (int i = n - 1; i >= 0; i--) {
        if (isdigit(prefix[i])) {
            pushInt(&s, prefix[i] - '0');
        } else if (isOperator(prefix[i])) {
            int val1 = popInt(&s);
            int val2 = popInt(&s);
            switch(prefix[i]) {
                case '+': pushInt(&s, val1 + val2); break;
                case '-': pushInt(&s, val1 - val2); break;
                case '*': pushInt(&s, val1 * val2); break;
                case '/': pushInt(&s, val1 / val2); break;
            }
        }
    }
    return popInt(&s);
}

int main() {
    int choice;
    char infix[100];
    char prefix[100];
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Convert Infix to Prefix\n");
        printf("2. Evaluate Prefix Expression\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter infix expression: ");
                scanf("%s", infix);
                infixToPrefix(infix, prefix);
                printf("Prefix expression: %s\n", prefix);
                break;
                
            case 2:
                printf("Enter prefix expression: ");
                scanf("%s", prefix);
                int result = evaluatePrefix(prefix);
                printf("Result of evaluation: %d\n", result);
                break;
                
            case 3:
                exit(0);
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}
