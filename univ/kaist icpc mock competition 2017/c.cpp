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

int n, k, a;

int main()
{
	read(n, k, a);
	k /= a;
	int ans = 1e9;
	rep(i, n){
		int t, s; read(t, s);
		int kai = (k+t-1)/t;
		int tm = (kai-1) * (t+s) + k - (kai-1)*t;
		ans = min(ans, tm);
	}
	printf("%d\n", ans);
	return 0;
}
