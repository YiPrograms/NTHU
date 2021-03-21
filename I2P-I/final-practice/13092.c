#include <stdio.h>
#include <string.h>

int a[5][5];
int b[5][5];

int compressl() {
    int moved = 0;
    for (int i = 0; i < 4; i++) {
        int org[4], tmp[4];
        int cnt = 0;
        for (int j = 0; j < 4; j++)
            org[j] = b[i][j];
        for (int j = 0; j < 4; j++)
            if (org[j] != 0)
                tmp[cnt++] = org[j];
        for (int j = 0; j < cnt - 1; j++) {
            if (tmp[j] == tmp[j+1]) {
                tmp[j] *= 2;
                tmp[j+1] = 0;
                j++;
            }
        }
        int k = 0;
        for (int j = 0; j < cnt; j++)
            if (tmp[j] != 0)
                b[i][k++] = tmp[j];
        for (; k < 4; k++)
            b[i][k] = 0;
        for (int j = 0; j < 4; j++)
            if (org[j] != b[i][j])
                moved = 1;
    }
    return moved;
}

int compressu() {
    int moved = 0;
    for (int i = 0; i < 4; i++) {
        int org[4], tmp[4];
        int cnt = 0;
        for (int j = 0; j < 4; j++)
            org[j] = b[j][i];
        for (int j = 0; j < 4; j++)
            if (org[j] != 0)
                tmp[cnt++] = org[j];
        for (int j = 0; j < cnt - 1; j++) {
            if (tmp[j] == tmp[j+1]) {
                tmp[j] *= 2;
                tmp[j+1] = 0;
                j++;
            }
        }
        int k = 0;
        for (int j = 0; j < cnt; j++)
            if (tmp[j] != 0)
                b[k++][i] = tmp[j];
        for (; k < 4; k++)
            b[k][i] = 0;
        for (int j = 0; j < 4; j++)
            if (org[j] != b[j][i])
                moved = 1;
    }
    return moved;
}



int compressr() {
    int moved = 0;
    for (int i = 0; i < 4; i++) {
        int org[4], tmp[4];
        int cnt = 0;
        for (int j = 0; j < 4; j++)
            org[j] = b[i][j];
        for (int j = 3; j >= 0; j--)
            if (org[j] != 0)
                tmp[cnt++] = org[j];
        for (int j = 0; j < cnt - 1; j++) {
            if (tmp[j] == tmp[j+1]) {
                tmp[j] *= 2;
                tmp[j+1] = 0;
                j++;
            }
        }
        int k = 0;
        for (int j = 0; j < cnt; j++)
            if (tmp[j] != 0)
                b[i][3 - k++] = tmp[j];
        for (; k < 4; k++)
            b[i][3 - k] = 0;
        for (int j = 0; j < 4; j++)
            if (org[j] != b[i][j])
                moved = 1;
    }
    return moved;
}

int compressd() {
    int moved = 0;
    for (int i = 0; i < 4; i++) {
        int org[4], tmp[4];
        int cnt = 0;
        for (int j = 0; j < 4; j++)
            org[j] = b[j][i];
        for (int j = 3; j >= 0; j--)
            if (org[j] != 0)
                tmp[cnt++] = org[j];
        for (int j = 0; j < cnt - 1; j++) {
            if (tmp[j] == tmp[j+1]) {
                tmp[j] *= 2;
                tmp[j+1] = 0;
                j++;
            }
        }
        int k = 0;
        for (int j = 0; j < cnt; j++)
            if (tmp[j] != 0)
                b[3 - k++][i] = tmp[j];
        for (; k < 4; k++)
            b[3 - k][i] = 0;
        for (int j = 0; j < 4; j++)
            if (org[j] != b[j][i])
                moved = 1;
    }
    return moved;
}

int main() {
    while (~scanf("%d", &a[0][0])) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == 0 && j == 0)
                    continue;
                scanf("%d", &a[i][j]);
            }
        }

        int (*funcs[])() = {compressu, compressd, compressl, compressr};

        for (int k = 0; k < 4; k++) {
            memcpy(b, a, sizeof(b));
            int valid = 0;
            if (!funcs[k]())
                printf("Invalid\n");
            else {
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 4; j++) {
                        printf("%d", b[i][j]);
                        if (j == 3)
                            printf("\n");
                        else
                            printf(" ");
                    }
                }
            }
        }

    }
}
