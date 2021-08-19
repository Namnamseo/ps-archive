#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
#define isinf asdf

char sand[410][410];
int n, m;

bool onstk[410][410];
bool vis[410][410];
int dpU[410][410];
int dpD[410][410];

int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

/*
  1
2 x 0
  3
*/

bool isinf;

int dfs(int x, int y,int last_dir){
    onstk[x][y] = 1;
    vis[x][y] = 1;
    int ret = 1;
    int nxt_dir = 0;
    if(sand[x][y] == 'Z'){
        nxt_dir = 3-last_dir;
    } else { // N
        nxt_dir = last_dir^1;
    }
    int dirs[2] = {last_dir, nxt_dir};
    for(int d=0; d<2; ++d){
        int nx=x+dx[dirs[d]], ny=y+dy[dirs[d]];
        if(nx<1 || nx>n || ny<1 || ny>m) continue;
        if(!vis[nx][ny]) ret += dfs(nx, ny, dirs[d]);
        else if(onstk[nx][ny]) isinf=true;
    }
    onstk[x][y] = 0;
    return ret;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1; i<=n; ++i) scanf("%s", sand[i]+1);

    for(int j=1; j<=m; ++j){
        memset(vis, 0, sizeof(vis));
        isinf = 0;
        for(int i=1; i<=n; ++i){
            int val = dfs(i, j, 1);
            if(isinf) dpU[i][j] = inf;
            else dpU[i][j] = dpU[i-1][j] + val;
        }
    }

    for(int j=1; j<=m; ++j){
        memset(vis, 0, sizeof(vis));
        isinf = 0;
        for(int i=n; i>=1; --i){
            int val = dfs(i, j, 3);
            if(isinf) dpD[i][j] = inf;
            else dpD[i][j] = dpD[i+1][j] + val;
        }
    }

    for(int i=1; i<=n; ++i){
        for(int j=1; j<=m; ++j){
            int v=min(dpU[i][j], dpD[i][j]);
            if(v == inf) v=-1;
            else v<<=1;
            printf("%d", v);
            if(j<m) putchar(' ');
        }
        putchar(10);
    }
    return 0;
}
