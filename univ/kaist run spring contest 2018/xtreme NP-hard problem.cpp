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

int n, m, k;
vector<pp> e[1'000'010];
const ll inf = 1ll<<60;

const int LIM = 3;
struct ASDF {
	ll dst[1'000'010];
	pp par[1'000'010][LIM];
	int pn[1'000'010];
	
	void spread(int s, int donot){
		fill(dst+1, dst+n+1, inf);
		for(auto tmp:e[s]){
			int y=tmp.x, d=tmp.y;
			if(y == donot) continue;
			dst[y]=min(dst[y], ll(d));
		}
		for(int i=1; i<=n; ++i) if(dst[i]!=inf){
			for(auto tmp:e[i]){
				int j=tmp.x, d=tmp.y+dst[i];
				if(j == s || j == donot) continue;
				pp A[LIM+1];
				for(int i=0; i<LIM+1; ++i) A[i]={2e9, -1};
				for(int t=0; t<pn[j]; ++t) A[t]=par[j][t];
				A[pn[j]]={d, i};
				sort(A, A+pn[j]+1);
				if(pn[j]<LIM) ++pn[j];
				for(int i=0; i<pn[j]; ++i) par[j][i]=A[i];
			}
		}
	}
} d1, dn;

void k5(){
	d1.spread(1, n);
	dn.spread(n, 1);
	ll ans = inf;
	for(int x=2; x<n; ++x) for(auto tmp:e[x]){
		int y=tmp.x;
		if(y==1 || y==n) continue;
		int d=tmp.y;
		
		int sx=d1.pn[x]; pp *px=d1.par[x];
		int sy=dn.pn[y]; pp *py=dn.par[y];
		
		if(sx && sy) for(int i=0; i<sx; ++i){
			for(int j=0; j<sy; ++j){
				if(px[i].y != py[j].y && px[i].y != y && py[j].y != x)
					ans = min(ans, ll(px[i].x + py[j].x + d));
			}
		}
	}
	if(ans == inf) ans = -1;
	printf("%lld\n", ans);
}

void k4(){
	d1.spread(1, n);
	dn.spread(n, 1);
	ll ans = inf;
	for(int x=2; x<n; ++x){
		int sx=d1.pn[x]; pp *px=d1.par[x];
		int sy=dn.pn[x]; pp *py=dn.par[x];
		
		if(sx && sy) for(int i=0; i<sx; ++i){
			for(int j=0; j<sy; ++j){
				if(px[i].y != py[j].y)
					ans = min(ans, ll(px[i].x + py[j].x));
			}
		}
	}
	if(ans == inf) ans = -1;
	printf("%lld\n", ans);
}

void k3(){
	d1.spread(1, n);
	dn.spread(n, 1);
	ll ans = inf;
	for(int x=2; x<n; ++x){
		if(d1.pn[x]) ans = min(ans, dn.dst[x] + d1.par[x][0].x);
	}
	if(ans == inf) ans = -1;
	printf("%lld\n", ans);
}

int main()
{
	read(n, m, k);
	if(k > m || k > n-1){
		puts("-1");
		return 0;
	}
	for(int i=1; i<=m; ++i){
		int a, b, c; read(a, b, c);
		e[a].eb(b, c); e[b].eb(a, c);
	}
	if(k == 5){
		k5();
		return 0;
	}
	if(k == 4){
		k4();
		return 0;
	}
	if(k == 3){
		k3();
		return 0;
	}
	if(k == 2){
		d1.spread(1, n);
		dn.spread(n, 1);
		ll ans = inf;
		for(int i=2; i<n; ++i){
			ans = min(ans, d1.dst[i] + dn.dst[i]);
		}
		if(ans == inf) ans = -1;
		printf("%lld\n", ans);
		return 0;
	}
	if(k == 1){
		ll ans = inf;
		for(auto tmp:e[1]) if(tmp.x == n) ans = min(ans, ll(tmp.y));
		if(ans == inf) ans = -1;
		printf("%lld\n", ans);
		return 0;
	}
	return 0;
}
