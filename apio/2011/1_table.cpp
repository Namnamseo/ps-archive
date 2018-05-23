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
#define x first
#define y second

int n, m, k;
typedef tuple<int,int,int> t3;

struct DSU {
	static const int N=100000;
	int par[N+1];
	int ene[N+1];
	void init(){ for(int i=1; i<=N; ++i) par[i]=i, ene[i]=-1; }
	DSU(){ init(); }
	int R(int x){ return (x==par[x])?x:(par[x]=R(par[x])); }
	int force(int x, int y){
		if(x==-1 || y==-1) return x+y+1;
		return par[x]=y;
	}
	bool unite(int x, int y){
		x=R(x); y=R(y);
		if(ene[x]==y) return 0;
		int a=force(x, y), b=force(ene[x], ene[y]);
		ene[a]=b; if(b != -1) ene[b]=a;
		return 1;
	}
	bool dis(int x, int y){
		x=R(x); y=R(y);
		if(x==y) return 0;
		int a=force(x, ene[y]), b=force(ene[x], y);
		ene[a]=b; ene[b]=a;
		return 1;
	}
	int chk(int x){
		x=R(x);
		if(ene[x]==-2) return 0;
		ene[x]=-2; return 1;
	}
} dval, drow;

vector<pp> col[100010];
bool e[100010];

void dame(){
	puts("0");
	exit(0);
}

int main()
{
	read(n, m, k);
	for(int i=1; i<=k; ++i){
		int x, y, c;
		read(x, y, c);
		if(x%2==0 && y%2==0) c=1^c;
		col[y].pb(pp{x, c});
		e[y]=1;
	}
	for(int i=1; i<=m; ++i){
		auto& v=col[i];
		int n=v.size();
		for(int i=0; i+1<n; ++i){
			if(v[i].y == v[i+1].y){
				if(!dval.unite(v[i].x, v[i+1].x)) dame();
			}
			else {
				if(!dval.dis(v[i].x, v[i+1].x)) dame();
			}
		}
	}
	for(int i=1; i<=m; ++i){
		auto& v=col[i];
		int n=v.size();
		for(int i=0; i+1<n; ++i) drow.unite(v[i].x, v[i+1].x);
	}
	int ans=1, ac=0;
	const int M=1e9;
	for(int i=1; i<=n; ++i) ac += drow.chk(i);
	for(int i=1; i<=m; ++i) if(!e[i]) ++ac;
	for(;--ac;) ans=ans*2%M;
	printf("%d\n", ans);
	return 0;
}

