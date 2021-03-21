#include <iostream>
#include <set>
#include <algorithm>
#include <map>
using namespace std;

set<int> vcnt;
map<pair<int, char>, int> samecnt;

int main() {
    int n;
    cin >> n;

    int cntpairs = 0;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int vowcnt = 0;
        char lastvow;
        for (char c:s) {
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                vowcnt++;
                lastvow = c;
            }
        }
        auto f = vcnt.find(vowcnt);
        if (f == vcnt.end())
            vcnt.emplace(vowcnt);
        else {
            cntpairs++;
            vcnt.erase(f);
        }
        samecnt[make_pair(vowcnt, lastvow)]++;
    }

    int pairs = 0;
    for (auto p: samecnt) {
        if (p.second >= 2) {
            int licpairs = min(p.second / 2, cntpairs / 2);
            pairs += licpairs;
            cntpairs -= 2 * licpairs;
        }
    }
    cout << pairs << '\n';
}
