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

int n, k;

char s[300010];

int p[300010];

deque<int> q;
deque<int> qlv[600010];
int dp[300010];

int main()
{
	cin >> n >> k >> (s+1);

	int ans = 0, last = 0, lev = 3e5 + 1;

	qlv[lev].pb(0); q.pb(0);

	for(int i=1; i<=n; ++i){
		if(s[i] == 'H') ++lev;
		else --lev;

		while(q.size() && q.front() < i-k) q.pop_front();

		dp[i] = dp[q.front()] + 1;
		auto &v1 = qlv[lev-1];
		while(v1.size() && v1.front() < i-k) v1.pop_front();
		if(v1.size()){
			dp[i] = min(dp[i], dp[v1.front()]);
		}

		auto &v = qlv[lev];
		while(v.size() && dp[v.back()] >= dp[i]) v.pop_back();
		v.push_back(i);

		while(q.size() && dp[q.back()] >= dp[i]) q.pop_back();
		q.push_back(i);
	}

	cout << dp[n] << endl;
	return 0;
}

