#include <iostream>
#include <set>

using namespace std;

using person = pair<int, string>;
set<person> st;

int main() {
    int n;
    cin >> n;
    while (n--) {
        string op;
        cin >> op;
        if (op[0] == 'b') { // born
            string name;
            int age;
            cin >> name >> age;
            st.emplace(age, name);
        } else if (op[0] == 'f') { // find
            string name;
            int age;
            cin >> name >> age;
            if (st.find(make_pair(age, name)) != st.end())
                cout << "YES\n";
            else
                cout << "NO\n";
        } else if (op[0] == 'k') { // kill
            string name;
            int age;
            cin >> name >> age;
            auto f = st.find(make_pair(age, name));
            if (f != st.end())
                st.erase(f);
        } else { // young
            if (st.empty())
                continue;
            
            auto const &[age, name] = *st.begin();
            cout << name << " " << age << "\n";
        }
    }
}
