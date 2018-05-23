#include <cstdio>
#include <vector>
using namespace std;
#define pb push_back
typedef pair<int,int> pp;

int n, m;

struct unf {
	int par[100010];
	void init(){ for(int i=1; i<=n; ++i) par[i]=i; }

	int root(int x){ return (x==par[x])?x:(par[x]=root(par[x])); }
	bool merge(int a,int b){
		a=root(a); b=root(b);
		if(a==b) return false;
		par[a]=b;
		return true;
	}
} f1, f2;

int par[100010];
int idx[100010];
int lowl[100010];
int nt;
vector<int> edge[100010];

void dfs(int x){
	idx[x] = lowl[x] = ++nt;
	bool cl = false;
	for(int y:edge[x]){
		if(par[x] == y && !cl){
			cl=true; continue;
		}
		if(!idx[y]){
			par[y]=x;
			dfs(y);
			lowl[x] = min(lowl[x], lowl[y]);
		} else lowl[x] = min(lowl[x], idx[y]);
	}
	if(par[x] && idx[x]==lowl[x]) printf("%d %d\n", x, par[x]);
}

int main(){
	scanf("%d%d", &n, &m);
	f1.init(); f2.init();
for(;m--;){
	int a,b;
	scanf("%d%d", &a, &b);
	if(f1.merge(a,b) || f2.merge(a,b)) edge[a].pb(b), edge[b].pb(a);
}
	for(int i=1; i<=n; ++i) if(par[i]==0) dfs(i);
	return 0;
}

