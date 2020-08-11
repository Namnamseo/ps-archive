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
#define sz(x) (ll)(x).size()

int n;

vector<ll> v[10];
bool ze[10];

bool origin;
bool zeroone;

ll ans;

int main()
{
	cppio();
	cin >> n;

	char buf[5];
	for(;n--;) {
		ll c;
		cin >> buf >> c;
		if(buf[0] == '^') {
			if(c > 0) v[1].pb(c);
			if(c == 0) ze[1] = 1;
			if(c < 0) v[2].pb(-c);
		} else if(buf[0] == '*') {
			if(c > 0) v[3].pb(c);
			if(c == 0) ze[2] = 1;
			if(c < 0) v[4].pb(-c);
		} else {
			if(c > 0) v[5].pb(c);
			if(c == 0) ze[3] = 1;
			if(c < 0) v[6].pb(-c);
		}
	}

	if(v[1].size() > 1u) zeroone = 1;
	if(v[2].size() > 1u) zeroone = 1;
	if(v[1].size() && v[2].size()) zeroone = 1;

	if(v[3].size() > 1u) origin = 1;
	if(v[4].size() > 1u) origin = 1;
	if(v[3].size() && v[4].size()) origin = 1;

	ans += sz(v[1]) * sz(v[4]);
	ans += sz(v[2]) * sz(v[3]);

	ans += sz(v[1]) * sz(v[5]);
	ans += sz(v[2]) * sz(v[6]);

	ans += sz(v[3]) * sz(v[5]) * 2;
	ans += sz(v[4]) * sz(v[6]) * 2;

	rrep(i, 6) sort(all(v[i]));

	for(auto tmp:{pp{1, 3}, pp{2, 4}}) {
		auto &V = v[tmp.y];
		for(int a : v[tmp.x]) {
			auto it = lower_bound(all(V), a);
			ans += 2 * (V.end() - it);
			if(it != V.end() && (*it) == a) --ans;
		}
	}

	for(auto tmp:{pp{1, 6}, pp{2, 5}}) {
		auto &V = v[tmp.y];
		for(int a : v[tmp.x]) {
			auto it = upper_bound(all(V), ll(a * (exp(2))));
			ans += 2 * (V.end() - it);
		}
	}

	for(auto tmp:{make_tuple(1, 3, 5), make_tuple(2, 4, 6)}) {
		int a, b, c; tie(a, b, c) = tmp;
		for(int x:v[a]) {
			auto has = [&](auto& v){
				auto it = lower_bound(all(v), x);
				return it != v.end() && (*it) == x;
			};
			if(has(v[b]) && has(v[c])) {
				ans -= 2;
			}
		}
	}

	if(ze[2] && (v[3].size() || v[4].size()))
		origin = 1;

	if(ze[1] && (v[1].size() || v[2].size()))
		zeroone = 1;

	if(ze[1]) for(int i=3; i<=6; ++i) ans += sz(v[i]);

	ans += origin;
	ans += zeroone;

	cout << ans << endl;

	return 0;
}
