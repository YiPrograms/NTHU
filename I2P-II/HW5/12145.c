#include <stdio.h>

int cnt[26];

int main() {
    int n;
    scanf("%d\n", &n);
    int cant = 1;
    if (n == 1)
        cant = 0;
    while (n--) {
        char c;
        scanf("%c", &c);
        cnt[c - 'a']++;
    }
    for (int i = 0; i < 26; i++) {
        if (cnt[i] >= 2) {
            cant = 0;
            break;
        }
    }
    if (cant) {
        printf("Different makes perfect\n");
    } else {
        printf("I'm the god of Knuckles!\n");
    }
}
