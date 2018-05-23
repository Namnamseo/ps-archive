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

int n,m;
int x[310];

ll inf=(1LL<<60);

int K;

int zp;

ll dp[310][310][2];
bool chk[310][310][2];

void init(){
	for(int i=1; i<=n; ++i){
		for(int j=i; j<=n; ++j){
			chk[i][j][0] = chk[i][j][1] = false;
		}
	}
}

int P(int l,int r,int wh){
	return x[wh?r:l];
}

ll work(int l, int r, int wh){
	if(chk[l][r][wh]) return dp[l][r][wh];
	chk[l][r][wh] = true;
	ll& ret=dp[l][r][wh];
	ret = inf;
	if(l == r){
		if(x[l] == 0) return ret=0;
		else return ret;
	}
	if(r<zp || zp<l) return ret;

	int mp=P(l, r, wh);
	for(int w=0; w<2; ++w){
		if(wh==0 && P(l+1,r, w) != mp)
			ret = min(ret, work(l+1, r, w) + abs(P(l+1,r,w)-mp)*1LL*(K+1+l-r));
		if(wh==1 && P(l,r-1, w) != mp)
			ret = min(ret, work(l, r-1, w) + abs(P(l,r-1,w)-mp)*1LL*(K+1+l-r));
	}
	return ret;
}

int main(){
	read(n,m);
	int init_cand = 0;
	for(int i=1; i<=n; ++i) {
		read(x[i]);
		if(x[i] == 0){
			init_cand += m;
			--i; --n;
		}
	}
	++n;

	sort(x+1, x+n+1);
	zp = lower_bound(x+1, x+n+1, 0) - x;

	ll ans = 0;

	for(K=1; K<n; ++K){
		init();

		for(int i=max(1, zp-K); i-K <= zp && i+K<=n; ++i){
			ll t=min(work(i, i+K, 0), work(i, i+K, 1));
			if(t == inf) continue;
			if(t < m*K)
				ans=max(ans, m*K-t);
		}

	}
	printf("%lld\n", ans + init_cand);

	return 0;
}

