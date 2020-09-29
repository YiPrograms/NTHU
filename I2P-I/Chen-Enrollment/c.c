#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* nums[105];

int str_gt(char* a, char* b) {
    char ab[2005];
    strcpy(ab, a);
    strcpy(ab + strlen(a), b);
    char ba[2005];
    strcpy(ba, b);
    strcpy(ba + strlen(b), a);
    return strcmp(ab, ba) > 0;
}

void sort(int l, int r) {
    if (r - l <= 1)
        return;
    int m = (l + r) / 2;
    sort(l, m);
    sort(m, r);
    int li = l, ri = m, i = 0;
    char* new[105];
    while (li < m && ri < r) {
        if (str_gt(nums[li], nums[ri])) {
            new[i++] = nums[li++];
        } else {
            new[i++] = nums[ri++];
        }
    }
    while (li < m) {
        new[i++] = nums[li++];
    }
    while (ri < r) {
        new[i++] = nums[ri++];
    }
    for (int i = 0; l+i < r; i++) {
        nums[l+i] = new[i];
    }
}

int main() {
    for (int i = 0; i < 105; i++) {
        nums[i] = (char*)malloc(1005 * sizeof(char));
    }
    int n;
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++) {
            scanf("%s", nums[i]);
        }
        sort(0, n);
        for (int i = 0; i < n; i++) {
            printf("%s", nums[i]);
        }
        printf("\n");
    }
}
