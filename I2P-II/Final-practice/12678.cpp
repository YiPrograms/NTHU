#include <iostream>

using namespace std;

int p[int(1e6) + 5];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    for (int i = 1; i <= 1e6 + 1; i++) {
        int res = 0;
        int n = i;
        while (n) {
            if (n % 10 == 1)
                res++;
            n /= 10;
        }
        p[i] = p[i - 1] + res;
    }

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        cout << p[b] - p[a-1] << "\n";
    }
}
