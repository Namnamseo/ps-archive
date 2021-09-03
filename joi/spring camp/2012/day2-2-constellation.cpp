#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second

pp operator-(pp a,pp b){ return {a.x-b.x, a.y-b.y}; }
pair<pp,int> d[100010];
int n;
bool ccw(pp a, pp b){ return ll(b.y)*a.x-ll(b.x)*a.y>0; }
bool ccw(pp a, pp b, pp c){ return ccw(b-a, c-a); }

int hu[100010], hn;
int stk[100010], top;
void H(){
	top=1;
	for(int i=1; i<n; ++i){
		while(top>=2 && ccw(d[stk[top-2]].x, d[stk[top-1]].x, d[i].x)) --top;
		stk[top++] = i;
	}
	for(int i=0; i<top-1; ++i) hu[hn++]=d[stk[i]].y;
}

const ll m=1'000'000'007;
ll Ans(ll x){ ll r=1; for(;x--;) (r*=2)%=m; return r; }
ll Ans2(ll x){ return x*(x+1)/2%m;}

int main()
{
	read(n);
	int cnt[3]={0,0,0};
	for(int i=0; i<n; ++i){
		int a, b, c; read(a, b, c); d[i]={{a, b}, c}; ++cnt[c];
	}
	sort(d, d+n); H(); reverse(d, d+n); H();
	int hc[3]={0,0,0};
	for(int i=0; i<hn; ++i) ++hc[hu[i]];
	ll in=Ans(cnt[0]-hc[0]);
	int safe=int(!cnt[1])+!cnt[2];
	if(!hc[1] || !hc[2]){
		if(hc[0]==hn){
			printf("%lld\n", (in*(hn*(hn-1ll)%m+2)%m + m-safe) % m);
			return 0;
		}
		ll ans=1;
		int l=0, r=hn-1;
		while(!hu[l]) ++l; while(!hu[r]) --r;
		int cc=l+hn-1-r;
		for(int i=l; i<=r; ++i){
			if(hu[i]){
				(ans+=Ans2(cc))%=m; cc=0;
			} else ++cc;
		}
		printf("%lld\n", (in*ans%m + m-safe)%m);
		return 0;
	}
	rotate(hu,find(hu,hu+hn,1),hu+hn);
	int l=0, r=hn-1;
	while(hu[l]!=2) ++l; while(hu[r]!=2) --r;
	if(count(hu+l, hu+r+1, 1)){ puts("0"); return 0; }
	int cl=1, cr=1;
	while(l && !hu[l-1]) ++cl, --l;
	while(r+1<hn && !hu[r+1]) ++cr, ++r;
	printf("%lld\n", (in*cl%m*cr%m + m-safe) % m);
	return 0;
}
