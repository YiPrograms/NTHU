#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <cmath>
using namespace std;

int ax[int(1e5) + 5], ay[int(1e5) + 5];


int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0, xi = 0, yi = 0; i < 2 * n; i++) {
            int x, y;
            cin >> x >> y;
            if (x == 0)
                ay[yi++] = abs(y);
            else
                ax[xi++] = abs(x);
        }
        sort(ax, ax + n);
        sort(ay, ay + n);
        double sum = .0;
        for (int i = 0; i < n; i++) {
            sum += sqrt(ax[i] * 1.0 * ax[i] + ay[i] * 1.0 * ay[i]);
        }
        cout << fixed << setprecision(8) << sum << "\n";
    }
}
