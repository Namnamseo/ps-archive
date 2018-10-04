#include <bits/stdc++.h>
using namespace std;

struct segtree {
	const static int M = 262144;
	int tree[M<<1];
	void upd(int p, int v){ for(p+=M; p; p>>=1) tree[p]=max(tree[p], v); }
	int rmax(int l, int r){
		int ret=0;
		for(l+=M, r+=M; l<=r; l/=2, r/=2){
			if(l%2==1) ret=max(ret, tree[l++]);
			if(r%2==0) ret=max(ret, tree[r--]);
		}
		return ret;
	}
} seg;

vector<int> edge[200010];
int par[200010];
int dep[200010];

int nt;
int tin[200010];
int tout[200010];

void dfs(int x){
	tin[x] = ++nt;
	for(int y:edge[x]) if(par[x]!=y){
		par[y]=x;
		dep[y]=dep[x]+1;
		dfs(y);
	}
	tout[x] = nt;
}

int cc[200010];
int ans[200010];

inline void cupd(int c, int df){
	ans[cc[c]]--;
	ans[cc[c] += df]++;
}

int n, C, q;

int upmost[200010];

int qc[200010];

#define pb push_back

int main(){
	scanf("%d%d%d", &n, &C, &q);
	for(int a,b,i=1; i<n; ++i){
		scanf("%d%d", &a,&b);
		edge[a].pb(b); edge[b].pb(a);
	}

	dfs(1);

	ans[0] = C;

	for(int i=1; i<=q; ++i){
		int u, c, m;
		scanf("%d%d%d", &u,&c,&m);
		qc[i] = c;

		for(int v=u; v!=1;){
			int lq = seg.rmax(tin[v], tout[v]);
			if(!lq){
				v = par[v];
				continue;
			}

			int bef = upmost[lq];

			upmost[lq] = v;
			cupd(qc[lq], (dep[bef]-dep[v]));
			v = bef;
		}

		cupd(c, dep[u]);
		upmost[i]=1;
		seg.upd(tin[u], i);

		printf("%d\n", ans[m]);
	}
	return 0;
}

