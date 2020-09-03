#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <vector>
#include <cstdio>
using namespace std;
using ll=long long;
using pp=pair<int,int>;
#define rep(i,n) for(int i=0;i<n;++i)
#define rrep(i,n) for(int i=1;i<=n;++i)
#define pb push_back
#define eb emplace_back

int n, m, k;

char *I;
int ri() { int ret=0; while (*I<48||*I>=58) ++I; while(*I>=48&&*I<58) ret=ret*10+(*(I++)-48); return ret; }
char Y[20];

struct E { int a, b, c; bool operator<(const E& r)const{ return c<r.c; } } ek[30], eu[300010], et[500]; int eun, etn;
vector<pp> e0[int(1e6)+1];
struct UF { int p[100010]; void init(int s=n){iota(p+1,p+s+1,1);} int r(int x){return x==p[x]?x:(p[x]=r(p[x])); }
int join(int a,int b){ a=r(a);b=r(b); if(a==b) return 0;p[a]=b;return 1; }} uf;

int g[100010],gn;
ll u[100010];

vector<pp> G[50];
vector<int> T[100010];
int P[100010];
ll s[50];

ll dfs(int x, int gn, int p) {
	ll ret = u[x]; g[x] = gn;
	for(int y:T[x]) if(p!=y) ret += dfs(y, gn, x);
	return ret;
}

ll S[50];
int gp[50], gl[50];
bool ikc[50];
int ans[50];
void gd(int x) {
	S[x] = s[x];
	for(auto [y, d]:G[x]) if (y != gp[x]) {
		gp[y] = x; gl[y] = gl[x]+1; ikc[y] = d; gd(y); S[x] += S[y];
	}
}

void ae(int a, int b, int c) {
	G[a].pb({b, c});
	G[b].pb({a, c});
}

bool seen[50][50];

int main() {
	{ static char buf[100]; using Z=struct stat*; fstat(0, (Z)buf); I=(char*)mmap(0,Z(buf)->st_size,1,2,0,0);}
	n = ri(); m = ri(); k = ri();

	static E e1[300010];
	rep(i,m) {
		int a = ri(), b = ri(), c = ri();
		e1[i] = {a, b, c};
	}
	sort(e1, e1+m);
	uf.init();
	rep(i,m) {
		int a=e1[i].a, b=e1[i].b;
		if (uf.join(a, b)) e0[e1[i].c].eb(a, b);
	}

	rep(i,k) ek[i].a=ri(), ek[i].b=ri();
	rrep(i,n) u[i]=ri();

	uf.init(); rep(i, k) uf.join(ek[i].a,ek[i].b);

	rrep(i, int(1e6)) {
		for(auto [a, b]:e0[i]) {
			if (uf.join(a, b)) {
				T[a].pb(b);
				T[b].pb(a);
			} else {
				eu[eun++]={a, b, i};
			}
		}
	}

	rrep(i, n) if (!g[i]) ++gn, s[gn]=dfs(i, gn, -1);

	rep(i, eun) {
		int a=g[eu[i].a], b=g[eu[i].b];
		if (a>b) swap(a, b);
		if (a!=b && !seen[a][b]) seen[a][b]=1, et[etn++]={a, b, eu[i].c};
	}

	rep(i, k) ek[i].a=g[ek[i].a], ek[i].b=g[ek[i].b];

	ll O = 0;

	for(int m=1; m<(1<<k); ++m) {
		uf.init(gn);
		rrep(x, gn) G[x].clear();

		bool mf=0;
		int cc=gn;
		rep(j, k) if (1&(m>>j)) {
			auto &e = ek[j];
			int a=e.a, b=e.b;
			if(a==b || !uf.join(a, b)) { mf=1; break; }
			--cc;
			ae(a, b, 1);
		}
		if (mf) continue;

		eun = 0;
		rep(j, etn){
			int a=et[j].a, b=et[j].b, &c=et[j].c;
			if(uf.join(a, b)) {
				ae(a, b, 0); --cc;
			} else eu[eun++]=et[j];
		}

		if (cc != 1) continue;

		gp[g[1]] = 0; gl[g[1]] = 0;
		gd(g[1]);

		for(int j=eun-1; 0<=j; --j) if (eu[j].c>0) {
			int a=eu[j].a, b=eu[j].b;
			if (gl[a]>gl[b]) swap(a, b);
			while (gl[a]<gl[b])
				ans[b] = eu[j].c, b=gp[b];
			while (a!=b) {
				ans[a] = eu[j].c;
				ans[b] = eu[j].c;
				a = gp[a]; b = gp[b];
			}
		}

		ll ca = 0;
		rrep(i, gn) if (ikc[i]) ca += ans[i] * S[i];

		O=max(O, ca);
	}

	for(gn=0;!gn||O;)Y[gn++]=48+O%10, O/=10;
	reverse(Y,Y+gn); Y[gn]=10; write(1,Y,gn+1);

	return 0;
}
