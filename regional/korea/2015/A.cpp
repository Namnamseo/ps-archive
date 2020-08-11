#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;

int adj[510][510];
int cost[1010][1010];
int capa[1010][1010];
ll inf = 1e9;
int n, m;

ll dist[1010];
int par [1010];

queue<int> q;

int source = 1, sink = 2;
int V;

vector<int> edge[1010];

bool bfs(){
	for(int i=1; i<=V; ++i){
		dist[i] = inf;
		par [i] = -1;
	}

	dist[source] = 0;
	q.push(source);

	while(q.size()){
		int x = q.front(); q.pop();
		for(int y : edge[x]){
			if(capa[x][y] == 0) continue;
			if(dist[y] > dist[x] + cost[x][y]){
				dist[y] = dist[x] + cost[x][y];
				par [y] = x;
				q.push(y);
			}
		}
	}

	return dist[sink] != inf;
}

vector<int> bF, bT;

void aE(int a,int b,int c){
	capa[a][b] = 1;
	cost[a][b] = c;
	cost[b][a] =-c;

	edge[a].pb(b);
	edge[b].pb(a);
}

int ia[510];
int ib[510];

void in(){
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i) for(int j=1; j<=n; ++j) if(i!=j) adj[i][j]=inf;
	for(;m--;){
		int a, b;
		scanf("%d%d",&a,&b);
		adj[a][b] = adj[b][a] = 1;
	}

	for(int j=1; j<=n; ++j)
		for(int i=1; i<=n; ++i)
			for(int k=1; k<=n; ++k)
				adj[i][k] = min(adj[i][k], adj[i][j] + adj[j][k]);

	bF.clear(); bT.clear();

	for(int i=1; i<=n; ++i){
		int buf; scanf("%d", &buf); if(buf) bF.pb(i);
	}

	for(int i=1; i<=n; ++i){
		int buf; scanf("%d", &buf); if(buf) bT.pb(i);
	}

	for(auto& v:edge) v.clear();
	memset(cost, 0, sizeof(cost));
	memset(capa, 0, sizeof(capa));
	V = 2;

	for(int x : bF) aE(source, ia[x] = ++V, 0);
	for(int x : bT) aE(ib[x] = ++V, sink, 0);
	for(int x : bF) for(int y : bT) aE(ia[x], ib[y], adj[x][y]);
}

int main(){
	int tc; scanf("%d", &tc);
	for(;tc--;){
		in();
		int ans = 0;
		while(bfs()){
			int x = sink;
			ans += dist[x];
			while(x != source){
				int p = par[x];
				capa[p][x] = 0;
				capa[x][p] = 1;
				x = p;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

