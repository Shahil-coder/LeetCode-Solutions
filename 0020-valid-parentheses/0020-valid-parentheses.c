#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool isValid(char* s) {
    int n = strlen(s);
    if (n % 2 != 0) return false; // Odd length valid nahi ho sakti

    char* stack = (char*)malloc(n * sizeof(char));
    int top = -1;

    for (int i = 0; i < n; i++) {
        char c = s[i];

        // Agar opening bracket hai toh stack me push karo
        if (c == '(' || c == '{' || c == '[') {
            stack[++top] = c;
        } 
        // Agar closing bracket hai toh check karo
        else {
            if (top == -1) {
                free(stack);
                return false;
            }

            char last = stack[top];
            if ((c == ')' && last == '(') ||
                (c == '}' && last == '{') ||
                (c == ']' && last == '[')) {
                top--; // Pop element
            } else {
                free(stack);
                return false;
            }
        }
    }

    bool result = (top == -1);
    free(stack);
    return result;
}