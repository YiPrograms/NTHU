#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
 
#define STRING_SIZE 10000
char input_str[STRING_SIZE];
 
int main() {
    char a, b;
    scanf("%s", input_str);
 
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%c", &a);
        scanf("%c %c", &a, &b);
        changeCharacter(input_str, a, b);
    }
    printf("%s\n", input_str);
}

