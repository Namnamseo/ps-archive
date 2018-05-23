#include "Anyalib.h"
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define all(x) x.begin(), x.end()

vector<int> edge[510];
vector<int> flat;
int par[510];
int fin[510];
int fout[510];

void dfs(int x){
	fin[x] = flat.size();
	flat.pb(x);
	for(int y:edge[x]) if(par[x] != y) par[y]=x, dfs(y), flat.pb(x);
	fout[x] = int(flat.size())-1;
}

int pari[510];
int N;
int tree[1010];

void tupd(int pos, int val){
	if(pos==0) tree[0]+=val;
	else while(pos<=1000) tree[pos]+=val, pos+=(pos&(-pos));
}

int tsum(int pos){
	if(pos > 1000) pos=1000;
	int ret=tree[0];
	while(pos) ret+=tree[pos], pos&=(pos-1);
	return ret;
}

void InitAnya(int N, int A[], int B[]){
	flat.clear();
	for(int i=0; i<n; ++i) edge[i].clear(), par[i]=0, fin[i]=0;
	for(int i=0; i<n-1; ++i) edge[a[i]].pb(b[i]), edge[b[i]].pb(a[i]);
	dfs(0);
	N=n;
	for(int i=0; i<n-1; ++i){
		int x=a[i], y=b[i];
		if(par[x]==y) pari[x]=i;
		else pari[y]=i;
	}
}

void Anya(int C[]){
	memset(tree, 0, sizeof(tree));
	int fn = flat.size();
	for(int i=1; i<N; ++i) if(C[pari[i]]){
		tupd(fin[i], 1);
		tupd(fout[i]+1, -1);
		Save(500+i, 1);
	}
	for(int i=0; i<fn; i+=20){
		int v=tsum(i);
		for(int j=0; j<10; ++j){
			Save(i/2+j, 1&(v>>(9-j)));
		}
	}
}