#include <iostream>
#include <array>

using namespace std;

constexpr int calc1s(int n) {
    int res = 0;
    while (n) {
        if (n % 10 == 1)
            res++;
        n /= 10;
    }
    return res;
}

constexpr auto pfx = [] {
    array<int, int(1e6) + 5> p = {};

    for (int i = 1; i < int(1e6) + 5; i++) {
        p[i] = p[i-1] + calc1s(i);
    }

    return p;
}();


int main() {
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        cout << pfx[b] - pfx[a - 1] << "\n";
    }
}
