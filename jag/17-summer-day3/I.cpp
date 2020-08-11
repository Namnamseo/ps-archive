#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;
#define rep(i,n) for(int i=0; i<n; ++i)
#define rrep(i,n) for(int i=1; i<=n; ++i)
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define all(x) x.begin(), x.end()

ll co;

struct seg2d {
	static const int M = 131072;
	vector<int> t[M<<1];
	void ap(int x, int y){
		x += M;
		while(x) t[x].pb(y), x/=2;
	}

	void init(){ for(auto& v:t) sort(all(v)); }

	int cnt(int l, int r, int d, int u){
		auto f = [&](vector<int>& v){ return max(0, int(upper_bound(all(v), u) - lower_bound(all(v), d))); };
		int ret = 0;
		for(l+=M, r+=M; l<=r; l/=2, r/=2){
			if(l%2==1) ret += f(t[l++]);
			if(r%2==0) ret += f(t[r--]);
		}
		return ret;
	}
} seg2;

const int maxn = int(1e5) + 10;

int b[maxn];
ll w[maxn];
int n;

ll ans;

struct segtree {
	ll *t;
	int M;

	segtree(int sz){
		for(M=1; M<sz; M*=2);
		t = (ll*) calloc(M<<1, sizeof(ll));
	}

	~segtree(){
		free(t);
	}

	void upd(int p, int v){
		for(p+=M; p; p/=2) t[p] += v;
	}

	int rsum(int l, int r){
		int ret = 0;
		for(l+=M, r+=M; l<=r; l/=2, r/=2){
			if(l%2==1) ret+=t[l++];
			if(r%2==0) ret+=t[r--];
		}
		return ret;
	}
};

void solve(int l, int r){
	if(l >= r) return;
	int mid = (l+r)/2;
	solve(l, mid); solve(mid+1, r);

	vector<int> indices;
	for(int i=l; i<=r; ++i) indices.pb(i);
	sort(all(indices), [&](const int& a, const int& b){
		return w[a] < w[b];
	});

	vector<int> Y;
	for(int i=l; i<=r; ++i) Y.pb(b[i]);
	sort(all(Y));
	int ys = Y.size();
	segtree lt(ys), rt(ys);

	auto C = [&](int x){ return lower_bound(all(Y), x) - Y.begin(); };

	for(int i=l; i<=mid; ++i) lt.upd(C(b[i]), 1);
	for(int i=mid+1; i<=r; ++i) rt.upd(C(b[i]), 1);

	for(int i:indices){
		if(i <= mid){
			ans += co * w[i] * rt.rsum(0, C(b[i]));
			lt.upd(C(b[i]), -1);
		} else {
			ans += co * w[i] * lt.rsum(C(b[i]), ys-1);
			rt.upd(C(b[i]), -1);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> co; --co;
	rrep(i, n) cin >> b[i] >> w[i], seg2.ap(i,  b[i]);
	seg2.init();
	rrep(i, n) ans += w[i] * (seg2.cnt(1, i-1, b[i]+1, n) + seg2.cnt(i+1, n, 1, b[i]-1));

	solve(1, n);
	cout << ans << '\n';
	return 0;
}
