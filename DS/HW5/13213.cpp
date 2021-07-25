#include <iostream>
#include "function.h"
#include <cstring>
#include <algorithm>

using namespace std;

int tmp[int(2e5) + 5];

template < class T >
void mysort(T arr[], int l, int r) {
    if (r <= l + 1)
        return;
    const int m = (l + r) /2;
    mysort(arr, l, m);
    mysort(arr, m, r);
    int li = l, ri = m, i = l;
    while (li < m && ri < r) {
        if (arr[li] < arr[ri])
            tmp[i++] = arr[li++];
        else
            tmp[i++] = arr[ri++];
    }
    while (li < m)
        tmp[i++] = arr[li++];
    while (ri < r)
        tmp[i++] = arr[ri++];
    for (int k = l; k < r; k++)
        arr[k] = tmp[k];
}

int lh[int(2e5) + 5];
int rh[int(2e5) + 5];

bool ldel[int(2e5) + 5];
bool rdel[int(2e5) + 5];

void solve() {
    int n, l, r, c;
    memset(rdel, 0, sizeof(rdel));
    memset(ldel, 0, sizeof(ldel));
    cin >> n >> l >> r >> c;
    for (int i = 0; i < l; i++)
        cin >> lh[i];
    for (int i = 0; i < r; i++)
        cin >> rh[i];
    mysort(lh, 0, l);
    mysort(rh, 0, r);

    int lc = l, rc = r;

    for (int i = 0, ri = 0; i < l && ri < r; i++) {
        while (ri < r && rh[ri] < lh[i])
            ri++;
        if (ri < r && rh[ri] == lh[i]) {
            rdel[ri] = ldel[i] = true;
            lc--;
            rc--;
            ri++;
        }
    }

    int lp = 0, rp = 0;

    for (int i = 0, last = -1, lasti = -1; i < l; i++) {
        if (ldel[i])
            continue;
        if (lh[i] == last) {
            lp++;
            last = -1;
        } else {
            last = lh[i];
            lasti = i;
        }
    }

    for (int i = 0, last = -1, lasti = -1; i < r; i++) {
        if (rdel[i])
            continue;
        if (rh[i] == last) {
            rp++;
            last = -1;
        } else {
            last = rh[i];
            lasti = i;
        }
    }

    int ld = lc - 2 * lp, rd = rc - 2 * rp;

    int cnt = 0;

    const int ldrd = min(ld, rd);
    ld -= ldrd;
    rd -= ldrd;
    cnt += ldrd;

    const int ldrp = min(ld, rp * 2);
    ld -= ldrp;
    rp -= ldrp / 2;
    cnt += ldrp;

    const int rdlp = min(rd, lp * 2);
    rd -= ldrp;
    lp -= rdlp / 2;
    cnt += ldrp;

    cnt += ld + rd + lp + rp;

    cout << c * 1LL * cnt << "\n";
}
