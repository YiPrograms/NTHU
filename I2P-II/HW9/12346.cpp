#include <iostream>
#include <map>

using namespace std;

map<int, int> mp;

int main() {
    int n;
    cin >> n;
    while (n--) {
        int ai;
        cin >> ai;
        mp[ai]++;
    }
    int q;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        if (mp.find(x) == mp.end())
            cout << 0 << '\n';
        else
            cout << mp[x] << '\n';
    }
}
