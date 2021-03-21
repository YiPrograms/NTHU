#include <stdio.h>
void hanoi(int n, char A, char B, char C) {
    if (n == 0)
        return;
    hanoi(n - 1, A, C, B);
    printf("move disk %d from rod %c to rod %c\n", n, A, C);
    hanoi(n - 1, B, A, C);
}

int main(){
    int n;
    scanf("%d", &n);
    hanoi(n, 'A', 'B', 'C');
    return 0;
}
