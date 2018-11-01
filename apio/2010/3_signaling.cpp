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

int n;
pp d[1501];

ll ans;

pp x[1501];

pp operator-(pp a, pp b){ return {a.x-b.x, a.y-b.y}; }
pp operator-(pp a){ return {-a.x, -a.y}; }

int qv(const pp& x){ return !((x.y > 0) || (x.y == 0 && x.x >= 0)); }
bool ccw(const pp& a, const pp& b){ return (a.x*1ll*b.y - a.y*1ll*b.x) > 0; }

typedef pair<pp,int> flag;

flag f[3001];

bool flag_cmp(const flag& a, const flag& b){
	int va = qv(a.x), vb = qv(b.x);
	if(va != vb) return va < vb;
	return ccw(a.x, b.x);
}

pp pt[3001];
int S[3001];
int T[3001];

void solve(int n){
	rrep(i, n){
		f[i].x = x[i];
		f[i].y = 1;
		f[i+n].x = -x[i];
		f[i+n].y = 0;
	}
	sort(f+1, f+2*n+1, flag_cmp);

	int ptn = 0, cc = 0;
	rep($, 2){
		rrep(i, 2*n){
			if(f[i].y == 1){
				pt[ptn] = f[i].x;
				S [ptn] = (ptn?S[ptn-1]:0) + cc;
				T [ptn] = (ptn?T[ptn-1]:0) + S[ptn];
				++ptn;
				cc = 0;
			} else ++cc;
		}
	}

	for(int i=0, j=1; i<n; ++i){
		while(j==i || ccw(pt[i], pt[j])) ++j;
		ans += T[j-1]-T[i] - S[i] * (j-1-i);
	}
}

int main()
{
	read(n);
	rrep(i, n) read(d[i]);
	rrep(i, n){
		int xn = 0;
		rrep(j, n) if(i!=j) x[++xn]=d[j]-d[i];
		solve(n-1);
	}

	ll nc3 = n * (n-1) / 2ll * (n-2) / 3ll;
	ll nc4 = nc3 * (n-3) / 4ll;

	printf("%.3f\n", 3. + double(2 * nc4 - ans / 3) / nc3);
	return 0;
}
