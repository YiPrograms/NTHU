#include <bits/stdc++.h>
using namespace std;


string nums[105];

int main() {
    int n;
    while (cin >> n) {
        for (int i = 0; i < n; i++)
            cin >> nums[i];
        sort(nums, nums + n);
        for (int i = n-1; i >= 0; i--)
            cout << nums[i];
        cout << "\n";
    }
}
