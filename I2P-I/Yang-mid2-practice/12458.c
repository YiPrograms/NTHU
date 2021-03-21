#include <stdio.h>
#include <string.h>

int n, k;
char s[1005];

int dp[1005][1005];

int times(int l, int r) {
    if (dp[l][r] != -1)
        return dp[l][r];

    if (r - l <= 0)
        return dp[l][r] = 0;

    if (s[l] == s[r])
        return dp[l][r] = times(l + 1, r - 1);
    
    int a = times(l + 1, r), b = times(l, r - 1);
    if (a < b)
        return dp[l][r] = a + 1;
    else
        return dp[l][r] = b + 1;
}

int main() {
    memset(dp, -1, sizeof(dp));
    scanf("%d %d", &n, &k);
    scanf("%s", s);
    if (times(0, n-1) <= k)
        printf("Yes\n");
    else
        printf("No\n");
}
