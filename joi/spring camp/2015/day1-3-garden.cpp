#include <cstdio>
#include <algorithm>
using namespace std;
#define sz(v) ((int)((v).size()))
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define coord_comp(v) sort(all(v)), v.erase(unique(all(v)), v.end())
#define v_index(v, x) (lower_bound(all(v),x)-(v).begin())
typedef pair<int,int> pp;
typedef long long ll;
void read(int& x){ scanf("%d",&x); }
template<typename T1,typename T2>
void read(pair<T1,T2>& p){ read(p.first); read(p.second); }
template<typename T,typename... Args>
void read(T&a,Args&...b){ read(a); read(b...); }

ll inf = (1LL<<57);

struct segtree {
	static const int M=131072;
	ll tree[M*2];
	ll lazy[M*2];

	void init(){
		for(int i=1; i<2*M; ++i) tree[i]=-inf, lazy[i]=0;
	}

	void acq(int pos,ll val){
		tree[pos] += val;
		lazy[pos] += val;
	}

	void pd(int pos){
		if(pos>=M || !lazy[pos]) return;
		ll t=lazy[pos];
		int y=pos*2;
		acq(y++, t); acq(y, t); lazy[pos]=0;
	}

	void upd(int l,int r,ll val,int pos=1,int ml=0,int mr=M-1){
		pd(pos);
		if(r<ml || mr<l) return;
		if(l<=ml && mr<=r){
			acq(pos, val);
		} else {
			int mid=(ml+mr)/2;
			upd(l, r, val, pos<<1, ml, mid);
			upd(l, r, val, pos<<1|1, mid+1, mr);
			tree[pos] = max(tree[pos<<1], tree[pos<<1|1]);
		}
	}

	ll rangemax(int l,int r,int pos=1,int ml=0,int mr=M-1){
		pd(pos);
		if(r<ml || mr<l) return -inf;
		if(l<=ml && mr<=r) return tree[pos];
		int mid=(ml+mr)/2;
		return max(rangemax(l, r, pos*2, ml, mid),
				rangemax(l, r, pos*2+1, mid+1, mr));
	}

} segme, segthy;

int n;

struct fool{
	int h, price, cost;
};

vector<ll> calc(vector<fool>& v){
	vector<ll> ret;
	ret.resize(n+1, inf);

	segme.init(); segthy.init();
	segme .upd(0, 131071, inf);
	segthy.upd(0, 0, inf);

	vector<pp> tmp;
	for(int i=1; i<=n; ++i){
		tmp.pb({v[i-1].h, i});
		segme .upd(i, n, -v[i-1].cost);
		segthy.upd(i, n,  v[i-1].cost);
	}
	sort(all(tmp));
	for(pp& ppp:tmp){
		int p=ppp.second;
		segme .upd(p, n,  v[p-1].cost);
		segthy.upd(p, n, -v[p-1].cost);

		ll t=segthy.rangemax(0, p-1);
		ret[p]=v[p-1].price + segme.rangemax(p,p) + t;
		segthy.upd(p, p, inf+ret[p]);
	}

	return ret;
}

int main(){
	read(n);
	vector<fool> data; data.reserve(n);
	for(int i=1; i<=n; ++i){
		int a,b,c; read(a,b,c);
		data.pb({a,b,c});
	}

	auto v1=calc(data);
	reverse(all(data));
	auto v2=calc(data);
	for(int i=1, j=n; i<j; ++i,--j) swap(v2[i], v2[j]);
	reverse(all(data));

	ll ans=0;
	for(int i=1; i<=n; ++i){
		ans = max(ans, v1[i] + v2[i] - data[i-1].price);
	}
	printf("%lld\n", ans);

	return 0;
}
