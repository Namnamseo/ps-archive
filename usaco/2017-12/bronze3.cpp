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

int n;

vector<pp> el[101];

char buf[10];

int main()
{
	read(n);
	rep(i, n){
		int day, df;
		scanf("%d%s%d", &day, buf, &df);
		int c = 0;
		if(buf[0] == 'E') c = 1;
		else if(buf[0] == 'M') c = 2;

		el[day].eb(c, df);
	}

	int msk = 7;
	int p[3]={7,7,7};
	int ans = 0;

	rrep(d, 100){
		for(auto& tmp:el[d]) p[tmp.x] += tmp.y;
		int cm = 0, mx = *max_element(p, p+3);
		rep(i, 3) if(mx == p[i]) cm |= (1<<i);
		if(cm != msk) ++ans;
		msk = cm;
	}

	printf("%d\n", ans);
	return 0;
}
