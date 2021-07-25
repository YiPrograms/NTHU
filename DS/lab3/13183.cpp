#include <iostream>
#include <set>

using namespace std;

set<long long> st;

int main() {
    int n;
    cin >> n;
    while (n--) {
       string s;
       cin >> s;
       if (s[0] == 'H') {
           long long x;
           cin >> x;
           st.emplace(x);
       } else if (s[0] == 'B') {
           long long a, d;
           cin >> a >> d;
           if (d < 0)
               continue;
           auto aa = st.lower_bound(a - d);
           auto bb = st.upper_bound(a + d);

           for (auto it = aa; it != bb;)
               it = st.erase(it);
       } else if (s[5] == 'F') {
           cout << "PrintFront\n";
           for (long long i: st)
               cout << i << "\n";
       } else {
           cout << "PrintEnd\n";
           for (auto it = st.rbegin(); it != st.rend(); ++it)
               cout << *it << "\n";
       }
    }
}
