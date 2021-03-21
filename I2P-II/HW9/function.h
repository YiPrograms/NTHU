typedef struct _NODE {
	int level;
	struct _NODE *left_child, *right_child;
} Node;

void build_tree(Node **now, int *arr, int l, int r);
int query_heatstroke(Node *now, int x);
void eat_rat(Node **root, int x);
void buy_rat(Node **root, int x);
