#include "function.h"
int changeCharacter(char *str, char a, char b) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == a)
            str[i] = b;
    }
}
