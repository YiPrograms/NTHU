#include <stdio.h>

int s[(int)1e6 + 5];

int main() {
    for (int i = 1; i <= 1e6+2; i++) {
        int k = i;
        s[i] = s[i - 1];
        int res = 0;
        while (k > 0) {
            if (k % 10 == 1)
                s[i] += 1;
            k /= 10;
        }
    }

    int n;
    scanf("%d", &n);
    while (n--) {
        int l, r;
        scanf("%d %d", &l, &r);
        printf("%d\n", s[r] - s[l-1]);
    }
}
