#include <iostream>

using namespace std;

string s;

int main() {
    int n;
    cin >> n;
    cin >> s;

    int l = 0, r = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'L')
            l++;
        else
            r++;
    }

    cout << l + r + 1 << "\n";
}
