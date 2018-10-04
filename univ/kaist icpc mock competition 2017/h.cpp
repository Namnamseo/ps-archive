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

ll ps[1000010];
int n;

int main()
{
	read(n);
	rrep(i, n) read(ps[i*2-1]);
	rrep(i, n){ ll x; read(x); ps[i*2]=-x; }
	partial_sum(ps+1, ps+2*n+1, ps+1);

	int ans = 0;
	ll mv = *min_element(ps+1, ps+2*n+1);
	rrep(i, n) if(ps[2*(i-1)] == mv) ++ans;
	printf("%d\n", ans);
	return 0;
}
