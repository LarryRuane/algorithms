#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main() {
    int t; 
    scanf("%d", &t);
    for (int a0 = 0; a0 < t; a0++){
        char expression[1000];
        scanf("%s", expression);
        
        char stack[2048];
        unsigned sp = 0; // empty
        
        bool failed = false;
        for (unsigned i = 0; !failed && expression[i]; i++) {
            switch (expression[i]) {
                case '(':
                case '{':
                case '[':
                    assert(sp < sizeof(stack));
                    stack[sp++] = expression[i];
                    break;
                case ')':
                    failed = !sp || stack[--sp] != '(' ;
                    break;
                case '}':
                    failed = !sp || stack[--sp] != '{' ;
                    break;
                case ']':
                    failed = !sp || stack[--sp] != '[' ;
                    break;
            }
        }
        printf("%s\n", sp || failed ? "NO" : "YES");
    }
    return 0;
}
