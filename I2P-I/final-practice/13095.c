#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char buffer[105];

int pena[100005][15];
int totlpena[100005];
char solved[100005][15];
int acprobs[100005];
int times[100005][15];
char inlist[100005];
int usrs[100005];
int usrn = 0;

int cmp(const void *aa, const void *bb) {
    int a = *(int*)aa, b = *(int*)bb;
    if (acprobs[a] != acprobs[b])
        return acprobs[a] > acprobs[b]? -1: 1;
    if (totlpena[a] != totlpena[b])
        return totlpena[a] < totlpena[b]? -1: 1;
    return a < b? -1: 1;
}

int have_next() {
    fgets(buffer, sizeof(buffer), stdin);
    int i = 0;
    while (buffer[i] == ' ')
        i++;

    return buffer[i+2] == 'r';
}

char *trim() {
    int i = 0;
    while (buffer[i] == ' ')
        i++;
    i += 4;
    while (buffer[i] == ' ')
        i++;
    return buffer + i;
}

int main() {
    for (int i = 0; i < 10; i++)
        fgets(buffer, sizeof(buffer), stdin);
    while (have_next()) {
        fgets(buffer, sizeof(buffer), stdin);
        char *st = trim();
        int mins = ((st[0] - '0') * 10 + (st[1] - '0')) * 60 + (st[3] - '0') * 10 + (st[4] - '0');

        fgets(buffer, sizeof(buffer), stdin);
        st = trim();
        int usr = 0;
        while (*st >= '0' && *st <= '9') {
            usr = usr * 10 + (*st - '0');
            st++;
        }

        fgets(buffer, sizeof(buffer), stdin);
        st = trim();
        int prob = *st - 'A';

        //printf("%d %d %d %c\n", mins, usr, prob, *st);
        
        fgets(buffer, sizeof(buffer), stdin);
        st = trim();

        if (!inlist[usr]) {
            usrs[usrn++] = usr;
            inlist[usr] = 1;
        }

        if (!solved[usr][prob]) {
            times[usr][prob]++;
            if (*st == 'A') { // AC
                solved[usr][prob] = 1;
                pena[usr][prob] += mins;
                totlpena[usr] += pena[usr][prob];
                acprobs[usr]++;
            } else { // WA
                pena[usr][prob] += 20;
            }
        }

        fgets(buffer, sizeof(buffer), stdin);
    }

    qsort(usrs, usrn, sizeof(int), cmp);
    for (int i = 0; i < usrn; i++) {
        const int usr = usrs[i];
        printf("%d ", usr);
        for (int k = 0; k < 10; k++) {
            if (times[usr][k] != 0)
                printf("%d", times[usr][k]);
            else
                printf("-");

            printf("/");

            if (solved[usr][k])
                printf("%d", pena[usr][k]);
            else
                printf("-");

            printf(" ");
        }

        printf("%d %d\n", acprobs[usr], totlpena[usr]);
    }
}
