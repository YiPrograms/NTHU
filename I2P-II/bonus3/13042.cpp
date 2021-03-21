#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;

using pii = pair<int, int>;

pii a[100005];
long long s[100005];

bool cmp(pii a, pii b) {
    return a.second > b.second;
}

int main() {
    int n, x, A, B;
    long long m;
    cin >> n >> x >> A >> B >> m;
    for (int i = 0, i < n; i++) {
        int xi;
        cin >> xi;
        a[i] = make_pair(i, xi);
    }

    sort(a, a + n, cmp);

    long long curmax = B * a[n-1].second;
    int maxid = -1;
    for (int i = 0; i < n && m >= s[i]; i++) {
        m -= s[i];

    }
}
