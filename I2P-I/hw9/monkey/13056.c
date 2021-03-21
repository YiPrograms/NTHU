//typedef struct {
//	int num;
//	char* name;
//} Monkey;

#include "function.h"
#include <string.h>
#include <stdlib.h>

Monkey* CreateMonkeyArray(int n) {
    Monkey *res = malloc(n * sizeof(Monkey));
    for (int i = 0; i < n; i++)
        res[i].name = malloc(sizeof(char) * 55);
    return res;
}

void FreeMonkeyArray(Monkey* m, int n) {
    for (int i = 0; i < n; i++)
        free(m[i].name);
    free(m);
}

void SetVal(Monkey* m, int i, int n, char s[]) {
    m[i].num = n;
    strcpy(m[i].name, s);
}

int Compare(Monkey* m, int a, int b) {
    if (m[b].num != m[a].num)
        return m[b].num > m[a].num;
    int alen = strlen(m[a].name), blen = strlen(m[b].name);
    for (int i = 0; i < alen && i < blen; i++)
        if (m[b].name[i] != m[a].name[i])
            return m[b].name[i] > m[a].name[i];
    return blen > alen;
}

void Swap(Monkey* m, int a, int b) {
    Monkey t = m[a];
    m[a] = m[b];
    m[b] = t;
}


