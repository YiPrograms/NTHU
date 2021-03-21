#include <iostream>
#include <set>
#include <iterator>

using namespace std;

set<int> s;

int main() {
    int n;
    cin >> n;
    while (n--) {
        string op;
        cin >> op;
        if (op[0] == 'i')  { // insert
            int ai;
            cin >> ai;
            s.emplace(ai);
        } else if (op[0] == 'p') { // print
            if (s.empty())
                continue;
            bool first = true;
            for (int k:s) {
                if (!first)
                    cout << " ";
                else
                    first = false;

                cout << k;
            }
            cout << '\n';
        } else if (op[0] == 'm') { // min
            if (!s.empty())
                cout << *s.begin() << '\n';
        } else { // range_erase
            int l, r;
            cin >> l >> r;
            auto il = s.lower_bound(l), ir = s.upper_bound(r);
            for (auto it = il; it != ir;) {
                it = s.erase(it);
            }
        }
    }
}
