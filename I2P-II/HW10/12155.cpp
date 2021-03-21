#include <iostream>

using namespace std;

int x[1005], y[1005];

int ds[1005];
bool dead[1005];
bool appear[1005];

int find(int a) {
    if (ds[a] == a)
        return a;
    return ds[a] = find(ds[a]);
}

void merge(int a, int b) {
    int fa = find(a), fb = find(b);
    if (fa == fb)
        return;
    ds[fa] = fb;
}

int main() {
    int n, r;
    cin >> n >> r;
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];

    for (int i = 0; i < n; i++)
        ds[i] = i;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dx = x[i] - x[j], dy = y[i] - y[j];
            if (dx * dx + dy * dy <= r * r) {
                dead[i] = dead[j] = true;
                merge(i, j);
            }
        }
    }
    
    int alive = 0, bh = 0;
    for (int i = 0; i < n; i++) {
        if (!dead[i])
            alive++;
        else {
            if (!appear[find(i)]) {
                bh++;
                appear[find(i)] = true;
            }
        }
    }
    cout << alive << " " << bh << "\n";
}
