#include <iostream>

using namespace std;
const int M = 1e9+7;

string s;
string r;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int x;
        cin >> x;
        cin >> s;
        int ans = s.length();
        for (int i = 0; i < x; i++) {
            int times = s[i] - '0';
            times -= 1;
            ans = (ans + ((ans - i - 1 + M) % M * times) % M) % M;
            if (s.length() <= x) {
                r = s.substr(i + 1);
                while (s.length() <= x && times--)
                    s.append(r);
            }
        }
        cout << ans << "\n";
    }
}
