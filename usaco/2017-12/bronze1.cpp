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

int s[3010][3010];

void nur(int c){
	int l, d, r, u;
	read(l, d, r, u);
	l += 1000;
	d += 1000;
	r += 1000;
	u += 1000;
	for(int i=l; i<r; ++i) for(int j=d; j<u; ++j) s[i][j] = c;
}

int main()
{
	nur(1);
	nur(1);
	nur(0);
	int a = 0;
	rep(i, 2001) a += accumulate(s[i], s[i]+2001, 0);
	printf("%d\n", a);
	return 0;
}

