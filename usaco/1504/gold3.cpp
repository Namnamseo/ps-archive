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

int n;
pp d[100010];

const int inf = 2e9;

struct Seg {
	const static int M=131072;
	int tree[M<<1];
	Seg(){ for(int& x:tree) x=inf;}
	void put(int x, int v){
		for(x+=M; x; x/=2) tree[x]=min(tree[x], v);
	}
	int right_iha(int l, int r, int v){
		vector<int> lp, rp;
		l+=M; r+=M;
		while(l<=r){
			if(l%2==1) lp.pb(l++);
			if(r%2==0) rp.pb(r--);
			l>>=1; r>>=1;
		}
		reverse(all(lp)); rp.insert(rp.end(), all(lp));
		for(int p:rp){
			if(tree[p]>v) continue;
			while(p<M){
				p=p*2+1;
				if(tree[p]>v) --p;
			}
			return p-M;
		}
		return -1;
	}
} seg;

int pre[100010];

int main()
{
	read(n);
	for(int i=1; i<=n; ++i){
		int p, s; read(s, p); d[i]={p, s};
	}
	sort(d+1, d+n+1);
	for(int i=1; i<=n; ++i) seg.put(i, d[i].x-d[i].y);
	for(int i=1; i<n; ++i){
		int p, s; tie(p, s) = d[i];
		int r = lower_bound(d+1, d+n+1, pp{p+s+1, 0}) - d - 1;
		int rp = seg.right_iha(i+1, r, p);
		if(rp != -1){
			++pre[i]; --pre[rp];
		}
	}
	int ans = 0;
	for(int i=1; i<n; ++i){
		pre[i] += pre[i-1];
		if(pre[i]){
			ans += d[i+1].x - d[i].x;
		}
	}
	printf("%d\n", ans);
	return 0;
}
