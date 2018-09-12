#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define pb push_back

#define rep(i,n) for(int i=0; i<(n); ++i)
#define rrep(i,n) for(int i=1; i<=(n); ++i)

ll ask(const vector<int>&);
void answer(int, int);

vector<int> asking;

int n, m;

vector<int> e[90010];
int es[130010];

ll base;

bool dead[90010];

int find_cut(){
	int l=-1, r=n-1;
	while(l+1<r){
		int mid=(l+r)/2;

		for(int i=l+1; i<=mid; ++i){
			for(int ei:e[i]) asking[ei]=1;
		}

		bool res = (ask(asking) > base);

		if(res){
			for(int i=l+1; i<=mid; ++i){
				for(int ei:e[i]){
					int j=es[ei]-i;
					if(!dead[j]) asking[ei]=0;
				}
			}

			r = mid;
		} else {
			for(int i=l+1; i<=mid; ++i) dead[i]=1;
			l = mid;
		}
	}
	return r;
}

int cut;

int dst[90010];
int q[90010], hd, tl;
bool vis[90010];

int find_deep(int l, int r){
	if(l == r){
		return q[l];
	}
	int mid=(l+r)/2;
	for(int i=mid+1; i<=r; ++i) for(int ei:e[q[i]]) asking[ei]=1;
	bool res = (ask(asking) > base);
	for(int i=mid+1; i<=r; ++i) for(int ei:e[q[i]]){
		int j=es[ei]-q[i];
		if(!dead[j]) asking[ei]=0;
	}
	if(res) return find_deep(mid+1, r);
	else return find_deep(l, mid);
}

void muko(int z){
	queue<int> q;
	q.push(z);
	dead[z]=1;
	for(;q.size();){
		int x = q.front(); q.pop();
		for(int ei:e[x]){
			int y=es[ei]-x;
			if(dst[y]==dst[x]-1 && !dead[y]){
				dead[y]=1;
				q.push(y);
			}
		}
	}
}

void find_pair(int N, vector<int> U, vector<int> V, int A, int B) {
	// find cut vertex
	n = N;
	m = U.size();
	asking.resize(m);

	base = ask(asking);

	for(int i=0; i<m; ++i){
		int a = U[i], b = V[i];
		e[a].pb(i); e[b].pb(i);
		es[i]=a+b;
	}

	cut = find_cut();

	q[hd++] = cut;
	vis[cut]=1;
	while(hd>tl){
		int x=q[tl++];
		for(int ei:e[x]){
			int y=es[ei]-x;
			if(dead[y]) continue;
			if(!vis[y]){
				vis[y]=1;
				dst[y]=dst[x]+1;
				q[hd++]=y;
			}
		}
	}

	int deep = find_deep(0, hd-1);
	muko(deep);
	dead[cut]=0;

	vector<int> tmp;
	int tg = base / A - dst[deep];

	rep(i, n){
		if(dead[i]) continue;
		if(dst[i] == tg) tmp.pb(i);
	}

	int s = tmp.size();
	rep(i, s) q[i] = tmp[i];
	int d2 = find_deep(0, s-1);

	answer(deep, d2);
}
