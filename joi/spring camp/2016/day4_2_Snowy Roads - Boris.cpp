#include "Borislib.h"
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

int getVal(int pos){
	if(pos >= int(flat.size())) return 0;
	pos /= 20;
	int ret=0;
	for(int i=0; i<10; ++i) ret=ret*2+Ask(10*pos + i);
	return ret;
}

void InitBoris(int N, int A[], int B[]){
	flat.clear();
	for(int i=0; i<n; ++i) edge[i].clear(), par[i]=0, fin[i]=0;
	for(int i=0; i<n-1; ++i) edge[a[i]].pb(b[i]), edge[b[i]].pb(a[i]);
	dfs(0);
}

int Boris(int city){
	int p = fin[city];
	int left = p/20*20;
	int right= left+20;

	int fn=flat.size();

	if(abs(p-left) < abs(p-right)){
		int val=getVal(left);
		for(int i=left+1; i<=p; ++i){
			int from=flat[i-1], to=flat[i];
			if(par[from] == to){
				if(Ask(500 + from)) --val;
			} else {
				if(Ask(500 + to)) ++val;
			}
		}
		return val;
	} else {
		int val=getVal(right);
		for(int i=right-1; p<=i; --i){
			if(i >= int(flat.size())) continue;
			int from=flat[i+1], to=flat[i];
			if(par[from] == to){
				if(Ask(500 + from)) --val;
			} else {
				if(Ask(500 + to)) ++val;
			}
		}
		return val;
	}
}