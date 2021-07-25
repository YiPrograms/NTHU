#include <bits/stdc++.h>

using namespace std;


using pii=pair<int, int>;
set<pii> st;
set<pii> vis;
int n, k;


int dfs(int x, int y) {
    cout << x << y << "\n";
    if (vis.find(pii(x,y)) != vis.end() || st.find(pii(x,y)) != st.end() 
    || x <= 0 || x > n || y<=0 || y >n )
        return 0;
    vis.emplace(pii(x,y));

    int res=1;
    res += dfs(x, y+1);
    res += dfs(x, y-1);
    res += dfs(x+1, y);
    res += dfs(x-1, y);
    return res;
}

int main() {
    cin >> n >> k;
    while (k--) {
        int x, y;
        cin >> x >> y;
        st.emplace(x, y);
    }

    int ans = 0;
    for (pii p: st) {
        ans = max(ans, dfs(p.first-1, p.second));
        ans = max(ans, dfs(p.first+1, p.second));
        ans = max(ans, dfs(p.first, p.second-1));
        ans = max(ans, dfs(p.first, p.second+1));
    }
    cout << ans << "\n";
}