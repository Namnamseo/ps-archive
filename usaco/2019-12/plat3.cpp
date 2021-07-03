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

int pre[301][46000];
int pos[301][46000];
int nc2[301];

int al[301];
int ar[301];

int n, k, m;

int main()
{
	cppio();
	cin >> n >> k >> m;
	pre[0][0] = pos[0][0] = 1;

	rrep(i, n) nc2[i] = i * (i-1) / 2;

	rrep(i, n) {
		ll s = 0;
		for(int j=0; j<=nc2[i]; ++j) {
			(s += pre[i-1][j]) %= m;
			if (j >= i) (s += m-pre[i-1][j-i]) %= m;
			pre[i][j] = s;
		}
	}

	{ int sm = 0;
	rrep(i, n) {
		ll s = 0;
		for(int j=0; j<=sm+n-i; ++j) {
			(s += pos[i-1][j]) %= m;
			if (j >= (n-i+1)) (s += m-pos[i-1][j-(n-i+1)]) %= m;
			pos[i][j] = s;
		}
		sm += n-i;
	}
	}

	rrep(i, n-1) {
		auto f = [=](int t)->int {
			ll ret = 0;
			for (int j=0; j<=t; ++j)
				(ret += pre[i][j] * 1ll * pos[n-i-1][t-j]) %= m;
			return ret;
		};
		al[i] = f(k);
		ar[i] = f(k-i);
	}

	auto ms = [&](const int& a, const int& b) { return (a+b)%m; };
	partial_sum(al+1, al+n, al+1, ms);
	partial_sum(ar+1, ar+n, ar+1, ms);

	rrep(i, n) {
		cout << (al[i-1] + ar[n-i] + pre[n][k])%m;
		if (i < n) cout << ' ';
	}
	cout << endl;

	return 0;
}
