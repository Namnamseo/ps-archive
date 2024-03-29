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
void cppio(){ ios_base::sync_with_stdio(0); cin.tie(0); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rrep(i,n) for(int i = 1; i <= (n); ++i)
#define sz(x) (int)(x).size()

int n;
int w, h;
char s[10005];

int x[1010];
int y[1010];
const int mod = 1e7;

int main()
{
	cppio();
	cin >> w >> h >> n >> (s+1);
	++w; ++h;

	int dx, dy;

	if (s[1] == 'L') {
		fill(x+2, x+w+1, 1);
		y[1] = 1;

		dx = 1;
		dy = 0;
	} else {
		fill(y+2, y+h+1, 1);
		x[1] = 1;

		dx = 0;
		dy = 1;
	}

	rrep(i, n) {
		if (s[i] == 'L') {
			swap(dx, dy); dx = -dx;
		} else {
			swap(dx, dy); dy = -dy;
		}
		if (dx == 1) {
			int s = 0, tmp;
			rrep(j, w) {
				tmp = x[j];
				x[j] = s;
				(s += tmp) %= mod;
			}
		} else if (dx == -1) {
			int s = 0, tmp;
			for(int j=w; 1<=j; --j) {
				tmp = x[j];
				x[j] = s;
				(s += tmp) %= mod;
			}
		} else if (dy == 1) {
			int s = 0, tmp;
			rrep(j, h) {
				tmp = y[j];
				y[j] = s;
				(s += tmp) %= mod;
			}
		} else {
			int s = 0, tmp;
			for(int j=h; 1<=j; --j) {
				tmp = y[j];
				y[j] = s;
				(s += tmp) %= mod;
			}
		}
	}

	ll ans = x[w];
	ans *= y[h];
	ans %= mod;
	cout << ans << endl;

	return 0;
}
