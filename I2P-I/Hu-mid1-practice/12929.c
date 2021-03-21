#include <stdio.h>

int main() {
    int ma, da, ha, mia, sa, mb, db, hb, mib, sb;
    scanf("%d/%d %d:%d:%d", &ma, &da, &ha, &mia, &sa);
    scanf("%d/%d %d:%d:%d", &mb, &db, &hb, &mib, &sb);
    da += ma * 30;
    ha += da * 24;
    mia += ha * 60;
    sa += mia * 60;

    db += mb * 30;
    hb += db * 24;
    mib += hb * 60;
    sb += mib * 60;
    
    int s = sa - sb;
    int m = 0, d = 0, h = 0, mi = 0;
    if (s < 0)
        s = -s;

    mi = s / 60;
    s %= 60;

    h = mi / 60;
    mi %= 60;

    d = h / 24;
    h %= 24;

    m = d / 30;
    d %= 30;

    printf("%d %d\n%02d:%02d:%02d\n", m, d, h, mi, s);
}
