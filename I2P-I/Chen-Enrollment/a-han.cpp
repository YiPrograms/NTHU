#include<bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define pii pair<int,int>
int ans = 0;
int n, m;
int ma[15][15] = {};
bool check(int ty, pii now){
    if(ma[now.F][now.S] != 0)return false;
    for(int i = 0 ; i < n + m ; i++){
        if(ma[i][now.S] != 0)return false;
        if(ma[now.F][i] != 0)return false;
    }
    for(int i = now.F,q = now.S ; i < n + m && q < n + m; i++ , q++){
        if(ma[i][q] == 2 || (ty == 2 && ma[i][q] != 0))return false;
    }
    for(int i = now.F,q = now.S ; i >= 0  && q >= 0; i-- , q--){
        if(ma[i][q] == 2 || (ty == 2 && ma[i][q] != 0))return false;
    }
    for(int i = now.F,q = now.S ; i < n + m && q >= 0; i++ , q--){
        if(ma[i][q] == 2 || (ty == 2 && ma[i][q] != 0))return false;
    }
    for(int i = now.F,q = now.S ; i >= 0  && q < n+m; i-- , q++){
        if(ma[i][q] == 2 || (ty == 2 && ma[i][q] != 0))return false;
    }
    return true;
}
void dfs(int dep, int ro, int qu){
    if(dep == n + m){
        ans++;
    }else{
        for(int i = 1 ; i < 3 ; i++){
            if(i == 1 && ro < n){
                for(int q = 0 ; q < n+m ; q++){
                    if(check(i, pii(dep,q))){
                        ma[dep][q] = 1;
                        dfs(dep + 1, ro + 1, qu);
                        ma[dep][q] = 0;
                    }
                }
            }else if(i == 2 && qu < m){
                for(int q = 0 ; q < n+m ; q++){
                    if(check(i, pii(dep,q))){
                        ma[dep][q] = 2;
                        dfs(dep + 1, ro, qu + 1);
                        ma[dep][q] = 0;
                    }
                }
            }else{
                continue;
            }
        }
    }
}
int main(){
    cin >> m >> n;
    dfs(0, 0, 0);
    cout << ans << endl;
    return 0;
}

