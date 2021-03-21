#include <string.h>
#include <stdio.h>

int n;
int a[105];
int dp[105];
int siz[105];
int rec[105][105];

int solve(int n) {
    if (dp[n] != -1)
        return dp[n];
    if (solve(n-2) + a[n] > solve(n-1)) {
        for (int i = 0; i < siz[n-2]; i++)
            rec[n][i] = rec[n-2][i];
        rec[n][siz[n-2]] = n;
        siz[n] = siz[n-2] + 1;
        return dp[n] = dp[n-2] + a[n];
    } else {
        for (int i = 0; i < siz[n-1]; i++)
            rec[n][i] = rec[n-1][i];
        siz[n] = siz[n-1];
        return dp[n] = dp[n-1];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    dp[1] = a[1];
    siz[1] = 1;
    rec[1][0] = 1;
    solve(n);
    for (int i = 0; i < siz[n]; i++)
        printf("%d ", rec[n][i]);
}
