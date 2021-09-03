#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
void cppio(){ ios_base::sync_with_stdio(0); cin.tie(0); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rrep(i,n) for(int i = 1; i <= (n); ++i)
#define sz(x) (int)(x).size()
#define XY(p) p.x, p.y
const int maxn = 3010;

int n;
pp p[maxn]; int type[maxn];
int js[maxn];

pp operator-(pp a, pp b) {
	return {a.x-b.x, a.y-b.y};
}

int sgn(const pp& v) {
	return (v.x < 0 && v.y == 0) || (v.y < 0);
}

bool ccw(const pp& a, const pp& b) {
	return (b.y*1ll*a.x) > (a.y*1ll*b.x);
}

int call[3], cup[3], cdown[3];

int main()
{
	cppio(); cin >> n;
	rrep(i, n) cin >> p[i].x >> p[i].y >> type[i];
	rrep(i, n) ++call[type[i]];

	ll ans = 0;

	rrep(i, n) {
		for (int j=1, k=0; j<=n; ++j) if (j!=i) js[k++]=j;
		sort(js, js+n-1, [&](const int& j, const int& k) {
			pp vj = p[j]-p[i];
			pp vk = p[k]-p[i];
			int sj = sgn(vj), sk = sgn(vk);
			if (sj != sk) return sj < sk;
			return ccw(vj, vk);
		});

		fill(cup, cup+3, 0);
		fill(cdown, cdown+3, 0);

		int lst = 0;
		auto ok = [&](int j, int k) {
			pp vj = p[js[j]]-p[i];
			pp vk = p[js[k]]-p[i];
			return ccw(vj, vk);
		};
		auto nxt = [](int i) { if (++i == n-1) i = 0; return i; };

		++cup[type[js[0]]];
		for (int j_=0; j_<n-1; ++j_) {
			while (nxt(lst) != j_ && ok(j_, nxt(lst))) {
				lst = nxt(lst);
				++cup[type[js[lst]]];
			}

			int j = js[j_];
			int ti = type[i], tj = type[j];
			--cup[tj];
			rep(k, 3) cdown[k] = call[k] - cup[k];

			--cdown[ti];
			--cdown[tj];

			ans += cup[(ti+1)%3] * 1ll * cup[(ti+2)%3] *
				cdown[(tj+1)%3] * cdown[(tj+2)%3];
			if (lst == j_) {
				lst = nxt(lst);
				++cup[type[js[lst]]];
			}
		}
	}

	ans /= 2;
	cout << ans << endl;
	return 0;
}
