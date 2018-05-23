#include "navigation_lib.h"

#include <vector>
using namespace std;
vector<int> edge[100010];

#define pb push_back

int par[100010];
void dfs(int x, int v){
	Flag(x, v);
	for(int y:edge[x]) if(par[x]!=y){
		par[y]=x;
		int nv = ((x<y) ^ v);
		dfs(y, nv);
	}
}

void Anna(int K, int N, int T, int A[], int B[]){
	for(int i=0; i<N-1; ++i){
		int a=A[i], b=B[i];
		edge[a].pb(b);
		edge[b].pb(a);
	}
	dfs(T, 0);
}

void Bruno(int K, int S, int F, int L, int P[], int Q[]){
	int nxt = S;
	for(int i=0; i<L; ++i){
		if((S < P[i]) == (Q[i] == F)) nxt=P[i];
	}
	Answer(nxt);
}