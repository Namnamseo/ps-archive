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
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rrep(i,n) for(int i = 1; i <= (n); ++i)
#define sz(x) (int)(x).size()

int n, m;
vector<int> ei[310];

int en;
int cp[5010];
int fl[5010];
int fr[5010];
int to[5010];

int md[510]; const int inf = 1e9;
bool vis[510];
vector<int> le[310];
bool bfs(){
	queue<int> q; q.push(1);
	fill(md+2, md+n+1, inf);
	while(q.size()){
		int x=q.front(); q.pop();
		for(int e:ei[x]){
			int y=fr[e]+to[e]-x;
			int yy=(to[e]==y ? cp[e]-fl[e]:fl[e]);
			if(!yy) continue;
			if(md[y] == inf){
				md[y]=md[x]+1; q.push(y);
			}
		}
	}
	if(md[n] == inf) return 0;
	rrep(x, n){
		le[x].clear();
		for(int e:ei[x]){
			int y=fr[e]+to[e]-x;
			int yy=(to[e]==y ? cp[e]-fl[e]:fl[e]);
			if(!yy) continue;
			if(md[y] == md[x]+1){
				le[x].pb(e);
			}
		}
	}
	return 1;
}

int pari[510];
int z;
bool dfs(int x, int mind){
	if(x == n) return z=mind, true;
	if(vis[x]) return false;
	vis[x]=1;
	for(int e:le[x]){
		int y=fr[e]+to[e]-x;
		int yy=(to[e]==y ? cp[e]-fl[e]:fl[e]);
		if(!yy) continue;
		if(dfs(y, min(mind, yy))) return pari[y]=e, 1;
	}
	return false;
}

int main()
{
	read(n, m);
	rrep(i, m){
		int a, b, c; read(a, b, c);
		++en;
		cp[en] = 2 * c;
		fl[en] = c;
		fr[en] = a; to[en] = b;
		ei[a].pb(en);
		ei[b].pb(en);
	}
	int ans = 0;
	while(bfs()){
		while(fill(vis+1, vis+n+1, false), dfs(1, inf)){
			for(int q=n; q!=1; ){
				int e=pari[q], p=fr[e]+to[e]-q;
				if(q == to[e]) fl[e] += z;
				else fl[e] -= z;
				q=p;
			}
			ans += z;
		}
	}
	printf("%d\n", ans);
	return 0;
}
