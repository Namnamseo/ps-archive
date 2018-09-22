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

struct gi {
	ll a, b;
	gi(ll A=0,ll B=0): a(A), b(B) {}

	ll norm(){ return a*a + b*b; }

	gi operator+(gi r) const {
		return gi(a+r.a, b+r.b);
	}
	gi operator-(gi r) const {
		return gi(a-r.a, b-r.b);
	}
};

bool operator==(gi l, gi r){
	return l.a==r.a && l.b==r.b;
}

gi operator*(ll a, gi b){ return gi(a*b.a, a*b.b); }
gi operator*(gi b, ll a){ return gi(a*b.a, a*b.b); }
gi operator*(gi a, gi b){ return gi(a.a*b.a - a.b*b.b, a.a*b.b + a.b*b.a); }

gi operator%(gi a, gi b){
	ll mo = b.norm();
	gi tmp = a * gi(b.a, -b.b);
	ll ba=(tmp.a - ((tmp.a%mo)+mo)%mo)/mo, bb=(tmp.b-(((tmp.b%mo)+mo)%mo))/mo;
	gi ans;
	rep(i, 4){
		gi v = a - b*gi(ba+i/2, bb+i%2);
		if(!i || ans.norm()>v.norm()) ans=v;
	}
	return ans;
}

int main()
{
	int tc; read(tc); for(;tc--;){
		ll a, b, c, d;
		read(a, b, c, d);
		gi x(a, b), y(c, d);
		vector<pll> ans;

		while(y.norm()){
			gi tmp = x % y;
			x = y; y = tmp;
		}
		ans.eb(x.a, x.b);

		auto tmp = ans[0];
		rep(i, 3){
			tmp = pll(-tmp.y, tmp.x);
			ans.pb(tmp);
		}
		sort(all(ans));
		printf("4\n");
		for(auto& tmp:ans) printf("%lld %lld\n", tmp.x, tmp.y);
	}
	return 0;
}

