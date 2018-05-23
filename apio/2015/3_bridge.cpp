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
 
int k, n;
vector<pp> d;
ll ans_base;
 
void in(){
	read(k, n);
	for(int i=1; i<=n; ++i){
		char p, q;
		int s, t;
		auto f = [](){char t; do{t=getchar();}while(t!='A'&&t!='B'); return t;};
		p = f(); read(s);
		q = f(); read(t);
		if(p == q){
			ans_base += abs(s - t);
		} else {
			++ans_base;
			d.eb(min(s, t), max(s, t));
		}
	}
	n = d.size();
}
 
ll dp1[100010];
ll dp2[100010];
 
struct SEG {
	const static int M = 262144;
	ll tree[M<<1];
	void init(){ memset(tree, 0, sizeof(tree)); }
	void upd(int p, ll v){for(p+=M;p;p/=2)tree[p]+=v;}
	ll s(int l,int r){
		ll ret=0;
		l+=M; r+=M;
		while(l<=r){
			if(l&1) ret+=tree[l++];
			if(r%2==0) ret+=tree[r--];
			l>>=1; r>>=1;
		}
		return ret;
	}
} sc, sl, sr;
 
int pt[200010], ptn;
multiset<int> low, high;
void Work(ll dp[100010]){
	sc.init(); sl.init(); sr.init();
	low.clear(); high.clear();
	auto add = [&](int a){
		((high.size() && a < (*high.begin())) ? low : high).insert(a);
		int b = lower_bound(pt, pt+ptn, a) - pt;
		sc.upd(b, 1);
		sl.upd(b, -a);
		sr.upd(b, a);
	};
	for(int i=1; i<=n; ++i){
		add(d[i-1].x);
		add(d[i-1].y);
		while(low.size() < high.size()){
			low.insert(*high.begin()); high.erase(high.begin());
		}
		while(low.size() > high.size()){
			high.insert(*--low.end()); low.erase(--low.end());
		}
		int mid = *high.begin();
		int p = lower_bound(pt, pt+ptn, mid) - pt;
		dp[i] = sc.s(0, p-1) * mid + sl.s(0, p-1) + 
			sr.s(p+1, ptn-1) - sc.s(p+1, ptn-1) * mid;
	}
}
 
int main()
{
	in();
	for(auto tmp:d) pt[ptn++]=tmp.x, pt[ptn++]=tmp.y;
	sort(pt, pt+ptn);
	if(k == 1){
		ll ans=0; int p=pt[n];
		for(auto tmp:d) ans += abs(tmp.x-p) + abs(tmp.y-p);
		printf("%lld\n", ans + ans_base);
		return 0;
	}
	ptn=unique(pt,pt+ptn)-pt;
	sort(all(d), [&](const pp& a, const pp& b){
		return a.x+a.y < b.x+b.y;
	});
	Work(dp1);
	reverse(all(d));
	Work(dp2); reverse(dp2, dp2+n+1);
	ll ans = 1LL << 60;
	for(int i=0; i<=n; ++i) ans = min(ans, dp1[i] + dp2[i]);
	printf("%lld\n", ans + ans_base);
	return 0;
}
