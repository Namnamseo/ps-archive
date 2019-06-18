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

int n,m;

struct edgee {
	int x, y, t, c;
} es[10001];

void read(edgee& e){ read(e.x, e.y, e.t, e.c); }

int par[201];
void init(){ for(int i=0; i<n; ++i) par[i]=i; }
int root(int x){ return (x==par[x])?x:(par[x]=root(par[x])); }

vector<pp> edge;

typedef pair<int,pp> pip;
pip ans(2147483647, pp(0,0));

pp tryLine(int cA,int cB,bool really=false){
	sort(es, es+m, [&](const edgee& a, const edgee& b){
		return a.t*cA + a.c*cB < b.t*cA + b.c*cB;
	});
	init();
	int aT=0, aC=0;
	for(int i=0; i<m; ++i){
		int a=es[i].x, b=es[i].y;
		a=root(a); b=root(b);
		if(a == b) continue;
		aT += es[i].t;
		aC += es[i].c;
		par[a] = b;
		if(really) edge.pb({es[i].x, es[i].y});
	}
	if(ans.first > aT*aC){
		ans = {aT*aC, {cA, cB}};
	}
	return pp(aT, aC);
}

void workPoints(pp a,pp b){
	int dx = b.first - a.first, dy = a.second - b.second;
	pp tmp = tryLine(dy, dx);
	if(dy*a.first + dx*a.second <= dy*tmp.first + dx*tmp.second)
		return;
	workPoints(a, tmp);
	workPoints(tmp, b);
}

int main(){
	read(n,m);
	for(int i=0; i<m; ++i) read(es[i]);
	
	workPoints(tryLine(1,0), tryLine(0,1));
	int a,b; tie(a,b) = ans.second;
	pp asdf = tryLine(a, b, true);
	printf("%d %d\n", asdf.first, asdf.second);
	for(pp tmp : edge)
		printf("%d %d\n", tmp.first, tmp.second);
	return 0;
}

