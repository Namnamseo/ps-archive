#include <bits/stdc++.h>
#define pb push_back
using namespace std;
void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args> void read(T& a,Args&... b){ read(a); read(b...); }

int n, m;
int a[51][51];
int ind[51][51];

int source = 1, sink = 2;
int V = 2;

int cap[3000][3000];
vector<int> edge[2510];
int inf = 1e9;
int A;

void addE(int f,int t,int x){
    cap[f][t] = x;
    edge[f].pb(t);
    edge[t].pb(f);
}

void in(){
    read(n, m);
    memset(cap, 0, sizeof(cap));
    V=2; A=0;
    for(auto& v:edge) v.clear();
    for(int i=1; i<=n; ++i) for(int j=1; j<=m; ++j){
        read(a[i][j]); A += a[i][j];
        if((i+j)&1) addE(source, ++V, a[i][j]);
        else addE(++V, sink, a[i][j]);
        ind[i][j] = V;
    }
}

int dist[3010];
int par [3010];
int minF[3010];

bool bfs(){
    queue<int> q;
    for(int i=1; i<=V; ++i) dist[i]=inf;
    q.push(source); dist[source]=0; par[source]=-1; minF[source]=inf;
    while(q.size()){
        int x = q.front(); q.pop();
        for(int y : edge[x]){
            if(!cap[x][y]) continue;
            if(dist[y] > dist[x] + 1){
                dist[y] = dist[x] + 1;
                par [y] = x;
                minF[y] = min(minF[x], cap[x][y]);
                q.push(y);
            }
        }
    }
    return dist[sink] != inf;
}

int dx[5] = {0,1,0,-1};

int main()
{
    int tc; read(tc);
    for(;tc--;){
        in();
        for(int i=1; i<=n; ++i) for(int j=1; j<=m; ++j) if((i+j)&1){
            for(int d=0; d<4; ++d){
                int nx=i+dx[d], ny=j+dx[d+1];
                if(1<=nx && 1<=ny && nx<=n && ny<=m){
                    addE(ind[i][j], ind[nx][ny], inf);
                }
            }
        }
        int flow = 0;
        while(bfs()){
            int x=sink;
            int v=minF[x]; flow += v;
            while(x != source){
                int p = par[x];
                cap[p][x] -= v;
                cap[x][p] += v;
                x = p;
            }
        }
        cout << A-flow << '\n';
    }
    return 0;
}
