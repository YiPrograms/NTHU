#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool CanWin(int n, int k, int state, char *state_mem) {
    //if we already have the result of current state, just return it
    //0 = Unknown, 1 = player 1 win, -1 = player 2 win 
    if (state_mem[state]!=0) return state_mem[state] == 1; 
    //try all number selection
    for (int i=0; i<n; i++) {
        //if the number has already been chosen, do not choose it
        if (state & (1 << i)) continue; 
        //If current player reach target or next player can't win, return true 
        if (k-(i+1)<=0 || !CanWin(n, k-(i + 1), state | (1 << i), state_mem)){
            state_mem[state] = 1;
            return true; 
        }
    }
    //Can't find any selection order that makes first player win, return false
    state_mem[state] = -1; 
    return false; 
}

int main(){
    int q;
    scanf("%d",&q);
    int N, K;
    while (q--){
        scanf("%d %d",&N,&K); 
        char *state_mem = calloc(1<<N, sizeof(char)); 
        if (CanWin(N, K, 0, state_mem)) printf("True\n"); 
        else printf("False\n"); 
        free(state_mem); 
    }
    return 0;
}
