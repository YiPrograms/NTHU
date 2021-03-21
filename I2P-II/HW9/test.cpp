int fa[MAXN];
void init(){
    for(int i = 0 ; i < MAXN ; i++)fa[i] = i;
}
int fifa(int a){
    if(fa[a]==a)return a;
    return fa[a] = fifa(fa[a]);
}
int unio(int a, int b){
    fa[fifa:w(a)] = fifa(b);
}
