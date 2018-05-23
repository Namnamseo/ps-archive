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
void read(ll& x){ cin>>x; }
template<typename T1,typename T2>
void read(pair<T1,T2>& p){ read(p.first); read(p.second); }
template<typename T,typename... Args>
void read(T&a,Args&...b){ read(a); read(b...); }

ll data[42];

typedef pair<ll,ll> pll;

ll tmp[(1<<20)+5];

vector<pll> work(int dl,int dr){
	int n=dr-dl;
	int am=(1<<n);
	for(int i=0; i<am; ++i){
		ll s=0;
		for(int j=0; j<n; ++j){
			if(1&(i>>j)){
				s += data[dl+j];
			}
		}
		tmp[i]=s;
	}
	sort(tmp, tmp+am);
	vector<pll> ret;
	for(int i=0; i<am;){
		int j;
		for(j=i; j<am && tmp[i]==tmp[j]; ++j);
		ret.pb({tmp[i], j-i});
		i=j;
	}
	return ret;
}

#define BIG

vector<pll> vl, vr;

int main(){
	int n; ll m;
	read(n, m);

	for(int i=0; i<n; ++i){
		ll t;
		read(t);
		data[i]=t;
	}
	int hn = n/2;

	vl=work(0, hn); vr=work(hn, n);

	int sl=sz(vl);
	for(int i=1; i<sl; ++i)
		vl[i].second += vl[i-1].second;

	ll ans=0;
	auto il=vl.begin(), ir=vr.end();
	while(ir != vr.begin()){
		--ir;
		while(il != vl.end()){
			auto it=il; ++it;
			if(it == vl.end()) break;
			if(it->first + ir->first <= m){
				il=it;
			} else break;
		}
		if(il != vl.end() &&
			il->first + ir->first <= m)
			ans += il->second*ir->second;
	}

	printf("%lld\n", ans);

	return 0;
}

