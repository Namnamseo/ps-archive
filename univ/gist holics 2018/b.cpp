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

char s[200010];
vector<int> pos[26];

int main()
{
	scanf("%s", s);
	for(int i=0; s[i]; ++i) pos[s[i]-'a'].pb(i);
	int q; read(q); for(;q--;){
		char tmp[5];
		scanf("%s", tmp);
		int l, r; read(l, r);
		auto& v=pos[tmp[0]-'a'];
		printf("%d\n", upper_bound(all(v), r) - lower_bound(all(v), l));
	}
	return 0;
}
