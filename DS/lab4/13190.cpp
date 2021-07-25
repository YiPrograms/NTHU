#include <iostream>
#include <algorithm>
#include <utility>
#include <map>
#include <set>

using namespace std;

using pii = pair<long long, long long>;

map<pii, long long> a;
set<pii> vsting;
long long r, c;

long long dfs(int x, int y, long long now) {
    auto af = a.find(make_pair(x, y));
    auto vst = vsting.find(make_pair(x, y));
    if (af == a.end() || vst != vsting.end())
        return 1e18;

    if (x == r-1 && y == c-1)
        return now;

    auto it = vsting.emplace(x, y).first;
    now += 1;
    long long res = 1e18;
    res = min(res, dfs(x - 1, y, now));
    res = min(res, dfs(x + 1, y, now));
    res = min(res, dfs(x, y - 1, now));
    res = min(res, dfs(x, y + 1, now));
    vsting.erase(it);
    return res;
}

int main() {
    cin >> r >> c;
    
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            long long v;
            cin >> v;
            if (v == 0)
                continue;
            a[make_pair(i, j)] = 1;
        }
    }

    long long res = dfs(0, 0, 0);
    if (res == 1e18)
        cout << 0 << "\n";
    else
        cout << res+1 << "\n";
}
