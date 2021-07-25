#include <iostream>
#include <algorithm>
#include <utility>
#include <map>
#include <set>

using namespace std;

using pii = pair<int, int>;

map<pii, long long> a;
set<pii> vsting;
int r, c;

long long dfs(int x, int y, long long now) {
    auto af = a.find(make_pair(x, y));
    auto vst = vsting.find(make_pair(x, y));
    if (af == a.end() || vst != vsting.end())
        return 1e18;

    auto it = vsting.emplace(x, y).first;
    now += af->second;
    long long res = 1e18;
    res = min(res, dfs(x - 1, y, now));
    res = min(res, dfs(x + 1, y, now));
    res = min(res, dfs(x, y - 1, now));
    res = min(res, dfs(x, y + 1, now));
    vsting.erase(it);
    if (res == 1e18) {
        return now;
    }
    return res;
}

int main() {
    cin >> r >> c;
    int sx, sy;
    cin >> sy >> sx;
    
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            long long v;
            cin >> v;
            if (v == 0)
                continue;
            if (v == -1)
                v = 1e11;
            a[make_pair(i, j)] = v;
        }
    }

    cout << dfs(sx, sy, 0) << "\n";
}
