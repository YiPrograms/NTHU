#define lc left_child
#define rc right_child

#include "function.h"
#include <set>
using namespace std;

multiset<int> s;

void build_tree(Node **now, int *arr, int l, int r) {
    for (int i = l; i <= r; i++)
        s.emplace(arr[i]);
}

int query_heatstroke(Node *now, int x) {
    if (s.find(x) == s.end())
        return 0;
    return 1;
}

void eat_rat(Node **root, int x) {
    s.erase(s.find(x));
}

void buy_rat(Node **root, int x) {
    s.emplace(x);
}
