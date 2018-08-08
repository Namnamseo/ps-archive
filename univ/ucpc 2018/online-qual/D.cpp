#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second

int n;
vector<int> edge[500010];
int par[500010];
int dep[500010];
int ans = 0;
void dfs(int x){
	bool ce=0;
	for(int y:edge[x]){
		if(y == par[x])continue;
		par[y]=x;
		dep[y]=dep[x]+1;
		ce=1;
		dfs(y);
	}
	if(!ce) (ans += dep[x]) %= 2;
}

int main()
{
	read(n);
	for(int i=1; i<n; ++i){
		int a, b; read(a, b);
		edge[a].pb(b);
		edge[b].pb(a);
	}
	dfs(1);
	puts(ans?"Yes":"No");
	return 0;
}
