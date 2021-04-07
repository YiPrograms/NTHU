#include <iostream>
#include <algorithm>

using namespace std;

int v[15], w[15];
int n, k;

int getVal(int curV, int curW, int i) {
    if (curV >= k)
        return curW;
    if (i == n)
        return 1e9;
    return min(getVal(curV, curW, i+1), getVal(curV + v[i], curW + w[i], i+1));
}

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> v[i] >> w[i];

    cout << getVal(0, 0, 0) << "\n";
}
