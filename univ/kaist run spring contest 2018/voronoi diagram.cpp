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

int n, m;

int ea[250010];
int eb[250010];
int wei[250010];
vector<int> eis[250010];

int ks[250001], k;

const ll inf = 1ll<<60;

ll dijk[250001];
int par[250010];

priority_queue<pair<ll,int>> pq;

ll ans1[250010];
ll ans2[250010];

int main()
{
	read(n, m);
	for(int i=1; i<=m; ++i){
		int a, b, c;
		read(a, b, c);
		ea[i]=a;
		eb[i]=b;
		wei[i]=c;
		eis[a].pb(i);
		eis[b].pb(i);
	}
	read(k);
	fill(dijk+1, dijk+n+1, inf);
	for(int i=1; i<=k; ++i) read(ks[i]), dijk[ks[i]]=0, par[ks[i]]=ks[i], pq.emplace(0, ks[i]);
	
	while(pq.size()){
		ll d; int p; tie(d, p)=pq.top(); pq.pop(); d = -d;
		if(d != dijk[p]) continue;
		for(int ei:eis[p]){
			int q = ea[ei]+eb[ei]-p;
			int w = wei[ei];
			if(dijk[q] > d+w){
				dijk[q] = d+w;
				par[q] = par[p];
				pq.emplace(-d-w, q);
			} else if(dijk[q] == d+w){
				par[q] = min(par[q], par[p]);
			}
		}
	}
	
	for(int i=1; i<=m; ++i){
		int a=ea[i], b=eb[i], c=wei[i];
		int pa = par[a], pb = par[b];
		if(pa == pb){
			ans1[pa] += c;
			continue;
		}
		ll xa2 = dijk[b]-dijk[a] + c;
		ans1[pa] += xa2/2;
		ans2[pa] += xa2%2;
		ll xb2 = dijk[a]-dijk[b] + c;
		ans1[pb] += xb2/2;
		ans2[pb] += xb2%2;
	}
	
	for(int i=1; i<=k; ++i){
		ll a = ans1[ks[i]] + ans2[ks[i]]/2;
		printf("%lld.%d\n", a, ans2[ks[i]]%2*5);
	}
	return 0;
}
