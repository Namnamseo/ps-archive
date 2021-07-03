#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)((v).size()))
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define coord_comp(v) sort(all(v)), v.erase(unique(all(v)), v.end())
#define v_index(v, x) (lower_bound(all(v),x)-(v).begin())
typedef pair<int,int> pp;
typedef long long ll;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
template<typename T1,typename T2>
void read(pair<T1,T2>& p){ read(p.first); read(p.second); }
template<typename T,typename... Args>
void read(T&a,Args&...b){ read(a); read(b...); }

int n,l;
vector<pp> edge[100010];

vector<int> hist;
typedef pair<ll,int> pli;
pli maxp;
bool vis[100010];
int par[100010];
ll vdist[100010];

void dfs(int x,ll dist){
	vis[x] = true;
	vdist[x]=dist;
	maxp = max(maxp, pli(dist, x));
	for(pp& yy:edge[x]){
		int y=yy.first, d=yy.second;
		if(!vis[y]) par[y]=x, dfs(y, dist+d);
	}
	hist.pb(x);
}

pli find_maxp(int a){
	maxp = pli(0LL,0);
	dfs(a, 0);
	for(int h : hist) vis[h]=false;
	return maxp;
}

bool viscompo[100010];

ll ans;
vector<ll> rad;

void compo(int x){
	int mp = find_maxp(x).second;
	hist.clear();
	int oth= find_maxp(mp).second;
	for(int h : hist){
		viscompo[h] = true;
	}
	hist.clear();
	ll dia= maxp.first;
	ll inf=(1LL<<59);
	ll put=inf;
	while(oth != mp){
		put = min(put, max(vdist[oth], dia-vdist[oth]));
		oth = par[oth];
	}
	if(put != inf) rad.pb(put);
	else rad.pb(0);

	ans=max(ans, dia);
}

extern "C" {
int travelTime(int N, int M, int L, int A[], int B[], int T[])
{
    n = N; l = L;
    for(int i=0; i<M; ++i) {
        edge[A[i]].pb({B[i], T[i]});
        edge[B[i]].pb({A[i], T[i]});
    }

	for(int i=0; i<n; ++i) if(!viscompo[i]) compo(i);
	sort(all(rad), greater<ll>());

	if(sz(rad) >= 2) ans=max(ans, rad[0]+l+rad[1]);
	if(sz(rad) >= 3) ans=max(ans, rad[1]+2*l+rad[2]);

	return ans;
}
}

