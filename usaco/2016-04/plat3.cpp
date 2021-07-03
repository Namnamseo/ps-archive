#include <bits/stdc++.h>
using namespace std;
void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
typedef long long ll;
typedef pair<int,int> pp;
#define all(x) (x).begin(),(x).end()
#define pb push_back

int n, x, y, z;
int A[100010];
int B[100010];

int a[1000010], an;
int b[1000010], bn;

ll inf = (1ll << 60);

ll f(pp x){ return (x.second == -1) ? ::x : ::y; }
ll f(pp x, pp y){ return z*1LL*abs(x.first - y.first); }

int main()
{
	int n;
	read(n, x, y, z);
	vector<pp> flags;
	for(int i=1; i<=n; ++i){
		read(A[i], B[i]);
		int t=min(A[i], B[i]);
		A[i] -= t;
		B[i] -= t;
		for(int j=0; j<A[i]; ++j) flags.pb(pp{i, 1});
		for(int j=0; j<B[i]; ++j) flags.pb(pp{i, -1});
	}
	int level=0;
	map<int, vector<pp>> vals;
	for(auto& tmp:flags){
		int x, d; tie(x, d) = tmp;
		if(d == -1) --level;
		vals[level].pb(tmp);
		if(d == 1) ++level;
	}
	ll ans=0;
	for(auto& tmp:vals){
		auto& v=tmp.second;
		int n=v.size();
		vector<ll> dp(n, inf);
		for(int i=0; i<n; ++i){
			ll a=f(v[i]), b=inf;
			if(i) a+=dp[i-1], b=f(v[i-1], v[i]);
            if(i>=2) b += dp[i-2];
			dp[i]=min(a, b);
		}
		ans += dp[n-1];
	}
	printf("%lld\n", ans);
	return 0;
}
