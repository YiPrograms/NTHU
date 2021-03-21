#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char p[5005];
char s[5005];

int len = 0;
char ss[5005][5005];
int cnts[5005];
int sortlist[5005];

int cmp(const void *aa, const void *bb) {
    int a = *(int*)aa, b = *(int*)bb;
    if (cnts[a] != cnts[b])
        return cnts[a] > cnts[b]? -1: 1;
    return a < b? -1: 1;
}

int samepattern(char *s) {
    char ch[26] = {0};
    char used[26] = {0};
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != p[i]) {
            if (ch[s[i] - 'a'] != 0) {
                if (ch[s[i] - 'a'] != p[i])
                    return 0;
            } else {
                if (used[p[i] - 'a'])
                    return 0;
                ch[s[i] - 'a'] = p[i];
                used[p[i] - 'a'] = 1;
            }
        }
    }
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);
    scanf("%s", p);
    int plen = strlen(p);
    while (n--) {
        scanf("%s", s);
        if (strlen(s) != plen || !samepattern(s))
            continue;
        if (len == 0 || strcmp(s, ss[len - 1]) != 0) {
            strcpy(ss[len], s);
            cnts[len] = 1;
            len++;
        } else {
            cnts[len - 1]++;
        }
    }

    printf("%d\n", len);
    for (int i = 0; i < len; i++)
        sortlist[i] = i;
    qsort(sortlist, len, sizeof(int), cmp);
    for (int i = 0; i < len; i++) {
        int id = sortlist[i];
        printf("%s %d\n", ss[id], cnts[id]);
    }
}
