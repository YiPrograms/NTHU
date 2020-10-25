#include <stdio.h>
#include <string.h>

char s[5];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int cnt[15];
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < 5; i++) {
            scanf("%s", s);
            if (s[0] == 'A')
                cnt[1]++;
            else if (s[0] == '1')
                cnt[10]++;
            else if (s[0] == 'J')
                cnt[11]++;
            else if (s[0] == 'Q')
                cnt[12]++;
            else if (s[0] == 'K')
                cnt[13]++;
            else
                cnt[s[0] - '0']++;
        }
        int p2 = 0, p3 = 0;
        for (int i = 1; i <= 13; i++) {
            if (cnt[i] == 2)
                p2 = 1;
            if (cnt[i] == 3)
                p3 = 1;
        }
        if (p2 && p3)
            printf("YES\n");
        else
            printf("NO\n");
    }
}
