#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back

int n, m;
int col[1000010];

int ans[1000010];

vector<int> adj[1000010];
int self[1000010];

const int M=1048576;
int t[M<<1];

void upd(int p, int v){
	p+=M; t[p]+=v; p>>=1;
	while(p) t[p]=max(t[p*2], t[p*2+1]), p>>=1;
}

int rM(int l, int r){
	int ret=0;
	l+=M; r+=M;
	while(l<=r){
		if(l&1) ret=max(ret, t[l++]);
		if((r&1)==0) ret=max(ret, t[r--]);
		l>>=1; r>>=1;
	}
	return ret;
}

void Do(){
	for(auto& v:adj) v.clear(); memset(self, 0, sizeof(self)); memset(t, 0, sizeof(t));
    
    for(int i=1; i<=n; i+=2){
		if(i+1 <= n){
			int a=col[i], b=col[i+1];
			if(a == b){
				++self[a];
				upd(a, 2);
				continue;
			}
			adj[a].pb(b); adj[b].pb(a);
			upd(a, 1); upd(b, 1);
		} else upd(col[i], 1);
    }
    
    for(int i=1; i<=m; ++i){
		for(int x:adj[i]) upd(x, -1);
		int jib=rM(i, i); upd(i, -jib);
		ans[i]=min(ans[i],
			n-rM(1, m)-jib
		);
		for(int x:adj[i]) upd(x, 1);
		upd(i, jib);
    }
}

void Do2(){
	for(auto& v:adj) v.clear(); memset(self, 0, sizeof(self)); memset(t, 0, sizeof(t));
    
    upd(col[1], 1);
    for(int i=2; i<=n; i+=2){
		if(i+1 <= n){
			int a=col[i], b=col[i+1];
			if(a == b){
				++self[a];
				upd(a, 2);
				continue;
			}
			adj[a].pb(b); adj[b].pb(a);
			upd(a, 1); upd(b, 1);
		} else upd(col[i], 1);
    }
    
    for(int i=1; i<=m; ++i){
		for(int x:adj[i]) upd(x, -1);
		int jib=rM(i, i); upd(i, -jib);
		ans[i]=min(ans[i],
			n-rM(1, m)-jib
		);
		for(int x:adj[i]) upd(x, 1);
		upd(i, jib);
    }
}

int main()
{
	//freopen("in", "r", stdin);
    read(n, m);
    for(int i=1; i<=n; ++i) read(col[i]);
    fill(ans+1, ans+m+1, n+1);
    Do(); Do2();
    reverse(col+1, col+n+1);
    Do(); Do2();
    for(int i=1; i<=m; ++i) printf("%d\n", ans[i]);
    return 0;
}
