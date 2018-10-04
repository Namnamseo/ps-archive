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

set<ll> s;
map<ll,int> id;

void dfs(ll x){
	if(!s.insert(x).y) return;
	if(x == 1) return;
	if(x&1){
		dfs(x/2);
		dfs(x/2+1);
	} else {
		dfs(x/2);
	}
}

int l[130], r[130], v;

int main()
{
int tc; read(tc);
for(;tc--;){
	ll n; read(n);
	s.clear(); dfs(n);
	v=0;
	id.clear();
	for(ll x:s){
		if(x == 1){
			l[v]=r[v]=-1;
			id[1]=v++;
			continue;
		}
		l[v]=id[(x+1)/2];
		r[v]=id[x/2];
		id[x]=v;
		++v;
	}
	printf("%d\n", v);
	rep(i, v){
		printf("%d %d\n", l[i], r[i]);
	}
	printf("%d\n", v-1);
}
	return 0;
}
