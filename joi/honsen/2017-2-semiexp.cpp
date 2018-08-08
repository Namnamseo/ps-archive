#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
const ll inf=1ll<<60;
#define exp asdf

int n, m, k;
ll a, b, c;
ll T;

vector<int> exp;

void in(){
	//freopen("in", "r", stdin);
    read(n, m, k, a, b, c, T);
    for(int i=1; i<=m; ++i){
		int x; read(x); exp.pb(x);
    }
}

ll gs[3010];
ll gl[3010];
ll lst[3010];

priority_queue<pair<ll,int>> pq;

ll getearn(ll gs, ll gl, ll p){
	if(gs-c*p < 0) return -1;
	ll r=p+(gs-c*p)/a;
	r=min(r, gl-1);
	return r-p+1;
}

void build(){
	sort(all(exp));
	for(int i=0; i<m-1; ++i){
		gs[i]=T-(exp[i]-1)*b;
		gl[i]=exp[i+1]-exp[i];
		lst[i]=min(gl[i]-1, gs[i]/a);
		if(lst[i]+1 <= gl[i]-1){
			ll earn=getearn(gs[i], gl[i], lst[i]+1);
			if(earn > 0){
				pq.push(make_pair(earn, i));
				lst[i] = min(gl[i]-1, lst[i]+earn);
			}
		}
	}
}

int main()
{
	in();
	build();
	int ans=0;
	for(int i=0; i<m-1; ++i){
		int l=exp[i], r=exp[i+1];
		if(T-(l-1)*b < 0) break;
		ll t=(T-(l-1)*b)/a;
		t=min(t, ll(r-l-1));
		ans += t+1;
	}
	if((n-1)*b <= T) ans++;
	for(int I=0; I<k-m && pq.size(); ++I){
		ans += pq.top().first;
		int i=pq.top().second;
		pq.pop();
		if(lst[i]+1 <= gl[i]-1){
			ll earn=getearn(gs[i], gl[i], lst[i]+1);
			if(earn > 0){
				pq.push(make_pair(earn, i));
				lst[i] = min(gl[i]-1, lst[i]+earn);
			}
		}
	}
	printf("%d\n", ans-1);
    return 0;
}
