#include <iostream>
#include <utility>
#include <set>

using namespace std;

using pii = pair<long long, long long>;

set<pii> st; 

int main() {
    int n;
    cin >> n;
    while (n--) {
        string op;
        cin >> op;
        if (op[0] == 'H') { // House
            long long x, y;
            cin >> x >> y;
            st.emplace(y, x);

        } else if (op[0] == 'B') { // Bomb
            long long x, y;
            cin >> x >> y;

            auto f = st.find(pii(y, x));
            if (f != st.end())
                st.erase(f);
            f = st.find(pii(y + 1, x));
            if (f != st.end())
                st.erase(f);
            f = st.find(pii(y - 1, x));
            if (f != st.end())
                st.erase(f);
            f = st.find(pii(y, x + 1));
            if (f != st.end())
                st.erase(f);
            f = st.find(pii(y, x - 1));
            if (f != st.end())
                st.erase(f);

        } else if (op[5] == 'F') { // PrintFront
            cout << "PrintFront\n";
            for (const pii &p: st)
                cout << '(' << p.second << "," << p.first << ")\n";

        } else { // PrintEnd
            cout << "PrintEnd\n";
            for (auto it = st.rbegin(); it != st.rend(); it++)
                cout << '(' << it->second << "," << it->first << ")\n";
        }
    }
}
