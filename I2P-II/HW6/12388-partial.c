#include<stdio.h>
#include "function.h"
#define MAX_N 1000006

int n, q;
int a[MAX_N];

int main() {
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	Node *root = NULL;
	build_tree(&root,a,0,n-1);
	scanf("%d",&q);
	while(q--) {
        print_tree(root);
        printf("\n");
		int x;
		scanf("%d",&x);
		if(query_heatstroke(root,x)!=0) {
			puts("We might as well eat it.");
			eat_rat(&root,x);
		}
		else puts("No dinner tonight.");
	}
	return 0;
}
