#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
void read(pp& x){ scanf("%d%d",&x.first, &x.second); }
void read(pll& x){ scanf("%lld%lld",&x.first, &x.second); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rrep(i,n) for(int i = 1; i <= (n); ++i)
#define sz(x) (int)(x).size()

vector<int> e[50010];
int vis[50010];
int stone[50010];

void dfs(int x){
	vis[x]=1;
	for(int y:e[x]) if(stone[y]==1 && !vis[y]) dfs(y);
}

int main()
{
	int n, m, s;
	read(n, m, s);
	bool ex = 0;
	rrep(i, n){
		read(stone[i]);
		if(stone[i] != 1) ex=1;
	}
	if(!ex){
		puts((n&1)?"hwy":"sjh");
		return 0;
	}
	for(;m--;){
		int a, b; read(a, b); if(a!=b) e[a].pb(b), e[b].pb(a);
	}
	if(stone[s] >= 2){ puts("hwy"); return 0; }
	dfs(s);
	if(accumulate(vis+1, vis+n+1, 0) & 1){
		puts("sjh");
	} else puts("hwy");
	return 0;
}
