#include <stdio.h>

int main() {
    char c;
    int s;
    scanf("%c %d", &c, &s);
    if (c <= 'Z') {
        c = 'a' + (c - 'A' - s + 26)%26;
    } else {
        c = 'A' + (c - 'a' - s + 26)%26;
    }
    printf("%c\n", c);
}
