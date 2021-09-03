#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)((v).size()))
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define coord_comp(v) sort(all(v)), v.erase(unique(all(v)), v.end())
#define v_index(v, x) (lower_bound(all(v),x)-(v).begin())
typedef pair<int,int> pp;
typedef long long ll;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
template<typename T1,typename T2>
void read(pair<T1,T2>& p){ read(p.first); read(p.second); }
template<typename T,typename... Args>
void read(T&a,Args&...b){ read(a); read(b...); }

int n;

struct gugan {
	int left, right;
	int on, off;
	ll cost;

	bool operator<(const gugan& other) const {
		return left < other.left;
	}

	gugan operator+(gugan R) const {
		gugan ret;
		ret.left = left; ret.right = R.right;
		ret.on = on + R.on;
		ret.off= off+ R.off;
		ret.cost = cost + R.cost;
		return ret;
	}

	gugan inv(){
		gugan ret = *this;
		swap(ret.on, ret.off);
		ret.cost = -ret.cost;
		return ret;
	}
};

set<gugan> g;

struct costcomp {
	bool operator()(const gugan& a, const gugan& b) const {
		return tie(a.cost, a.left) > tie(b.cost, b.left);
	}
};

set<gugan, costcomp> CS;

int a[200010];

int main(){
	scanf("%d", &n);
	for(int i=1; i<=n; ++i){
		scanf("%d",a + i);
	}

	for(int i=1; i<=n; ++i){
		gugan tmp = {i, i+1, 0, 1, a[i]};
		g.insert(tmp);
		CS.insert(tmp);
	}

	ll ans=0;
	for(int cnt=1; cnt<=(n+1)/2; ++cnt){
		gugan a = *CS.begin(); CS.erase(CS.begin());
		gugan ng = a.inv();
		ans += a.cost;

		auto it = g.find(a);
		auto il=it, ir=it;
        bool noin = false;
		if(il != g.begin()){
			--il;
			ng = (*il) + ng;
			g.erase(*il);
			CS.erase(*il);
		} else noin = true;
		++ir;
		if(ir != g.end()){
			ng = ng + *ir;
			g.erase(*ir);
			CS.erase(*ir);
		} else noin = true;
		g.erase(it);

        if(!noin){
            g.insert(ng);
		    CS.insert(ng);
        }

        printf("%lld\n", ans);
	}
	return 0;
}
