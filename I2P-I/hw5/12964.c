#include <stdio.h>

int b[3*3*3*3*3*3*3*3][3*3*3*3*3*3*3*3];

void draw(int x, int y, int n) {
    if (n == 1)
        return;
    draw(x, y, n / 3);
    draw(x + n/3, y, n / 3);
    draw(x + n/3*2, y, n / 3);
    draw(x + n/3*2, y + n/3, n / 3);
    draw(x + n/3*2, y + n/3*2, n / 3);
    draw(x + n/3, y + n/3*2, n / 3);
    draw(x, y + n/3*2, n / 3);
    draw(x, y + n/3, n / 3);

    for (int i = x + n/3; i < x + n/3*2; i++)
        for (int j = y + n/3; j < y + n/3*2; j++)
            b[i][j] = 1;
}


int main() {
    int n;
    scanf("%d", &n);
    int k = 1;
    while (n--)
        k *= 3;
    draw(0, 0, k);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            if (b[i][j] == 1)
                printf("#");
            else
                printf(".");
        }
        printf("\n");
    }
}
