#include <iostream>
#include <set>
#include <vector>

using namespace std;

vector<int> v;
multiset<pair<int, int>> s;

int main() {
    int n;
    cin >> n;
    int curid = 0;
    while (n--) {
        string op;
        cin >> op;

        if (op == "push_back") {
            int val;
            cin >> val;
            auto p = make_pair(val, curid++);
            v.emplace_back(val);
            s.emplace(p);
        } else if (op == "pop_back") {
            if (v.empty())
                continue;
            int val = *v.rbegin();
            v.pop_back();
            s.erase(make_pair(val, --curid));
        } else if (op == "find") {
            int i;
            cin >> i;
            i -= 1;
            if (i < 0 || i >= curid)
                continue;
            cout << v[i] << "\n";
        } else if (op == "min") {
            if (v.empty())
                continue;
            cout << s.begin()->first << " " << s.begin()->second + 1 << "\n";
        } else if (op == "max") {
            if (v.empty())
                continue;
            cout << s.rbegin()->first << " " << s.rbegin()->second + 1 << "\n";
        }
        //for (auto p: s) {
        //    cout << p.first << ":" << p.second << " ";
        //}
        //cout << "\n";
    }
}
