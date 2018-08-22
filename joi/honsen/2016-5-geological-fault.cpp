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

const int max_q = 200010, max_n2 = 524288;

int n;

int q;
int qx[max_q];
int qd[max_q];
int ql[max_q];

ll lx[max_n2];
ll ly[max_n2];
ll x[max_n2];
ll y[max_n2];

inline void col(int p){ x[p]=x[p*2+1]; y[p]=y[p*2]; }
inline void acq(int p, ll vx, ll vy){ x[p] += vx; lx[p] += vx; y[p] += vy; ly[p] += vy; }

void init(int p=1, int pl=1, int pr=n){
	if(pl == pr){
		x[p]=pl-1; y[p]=-pl; return;
	}
	int mid = (pl+pr)/2;
	init(p*2, pl, mid); init(p*2+1, mid+1, pr); col(p);
}

void pd(int p){
	acq(p*2, lx[p], ly[p]);
	acq(p*2+1, lx[p], ly[p]);
	lx[p] = 0; ly[p] = 0;
}

void upd(ll vx, ll vy, int l, int r, int p=1, int pl=1, int pr=n){
	if(pl!=pr) pd(p);
	if(r<pl || pr<l) return;
	if(l<=pl && pr<=r){
		acq(p, vx, vy); return;
	}
	int mid = (pl+pr)/2;
	upd(vx, vy, l, r, p*2, pl, mid);
	upd(vx, vy, l, r, p*2+1, mid+1, pr);
	col(p);
}

void dfs(int p=1, int pl=1, int pr=n){
	if(pl == pr){
		printf("%lld\n", -(x[p]+y[p])/2);
		return;
	}
	pd(p);
	int mid=(pl+pr)/2;
	dfs(p*2, pl, mid); dfs(p*2+1, mid+1, pr);
}

int main()
{
	read(n, q);
	rep(i, q) read(qx[i], qd[i], ql[i]);

	init();
	for(int i=q-1; 0<=i; --i){
		if(qd[i] == 1){
			ll v=-qx[i];
			if(v > y[1]) continue;
			int p=1, pl=1, pr=n;
			while(pl != pr){
				pd(p);
				int mid = (pl+pr)/2;
				if(y[p*2+1] >= v) p=p*2+1, pl=mid+1;
				else p=p*2, pr=mid;
			}
			upd(-2*ql[i], 0, 1, pl);
		} else {
			ll v=qx[i];
			if(x[1] < v) continue;
			int p=1, pl=1, pr=n;
			while(pl != pr){
				pd(p);
				int mid = (pl+pr)/2;
				if(x[p*2]<v) p=p*2+1, pl=mid+1;
				else p=p*2, pr=mid;
			}
			upd(0, -2*ql[i], pl, n);
		}
	}

	dfs();
	return 0;
}
