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

int data[100010];

int n;

int main(){
	read(n);
	for(int i=1; i<=n; ++i) read(data[i]), data[i] *= 10;
	sort(data+1, data+n+1);
	ll ans = 0;
	ll prs = 0;
	for(int i=1; i<=n; ++i){
		auto a = lower_bound(data+1, data+n+1, data[i]/10*9);
		auto b = lower_bound(data+1, data+n+1, data[i]);
		auto c = upper_bound(data+1, data+n+1, data[i]);
		ans += b-a;
		prs += c-b-1;
	}
	printf("%lld\n", ans + prs/2);
	return 0;
}
