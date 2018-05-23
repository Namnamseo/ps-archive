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

vector<int> xps, yps;
vector<int> xco[2010], yco[2010];

int n;
int sx,sy;
int tx,ty;

struct rect {
	int l,r;
	int d,u;
} rec[1010];

inline int conv(int x,int y){
	return x*yps.size() + y;
}

ll dijk[4009000];
vector<int> edge[4009000];
vector<int> ec[4009000];

typedef pair<ll,int> dip;
priority_queue<dip> pq;

inline int jumpRight(int x,int y){
	int ret=upper_bound(all(yco[y]),x)-yco[y].begin();
	if(ret == sz(yco[y])) return -1;
	return yco[y][ret];
}

inline int jumpLeft(int x,int y){
	int ret=lower_bound(all(yco[y]),x)-yco[y].begin()-1;
	return (ret<0)?(-1):(yco[y][ret]);
}

inline int jumpUp(int x,int y){
	int ret=upper_bound(all(xco[x]),y)-xco[x].begin();
	if(ret == sz(xco[x])) return -1;
	return xco[x][ret];
}

inline int jumpDown(int x,int y){
	int ret=lower_bound(all(xco[x]),y)-xco[x].begin()-1;
	return (ret<0)?(-1):(xco[x][ret]);
}

inline void tryJumps(int x,int y,bool a,bool b,bool c,bool d){
	if(a){
		int t=jumpLeft(x,y);
		if(t!=-1){
			int A=conv(x,y);
			int B=conv(t,y);
			edge[A].pb(B);
			ec  [A].pb(xps[x]-xps[t]);
		}
	}
	if(b){
		int t=jumpRight(x,y);
		if(t!=-1){
			int A=conv(x,y);
			int B=conv(t,y);
			edge[A].pb(B);
			ec  [A].pb(xps[t]-xps[x]);
		}
	}
	if(c){
		int t=jumpUp(x,y);
		if(t!=-1){
			int A=conv(x,y);
			int B=conv(x,t);
			edge[A].pb(B);
			ec  [A].pb(yps[t]-yps[y]);
		}	
	}
	if(d){
		int t=jumpDown(x,y);
		if(t!=-1){
			int A=conv(x,y);
			int B=conv(x,t);
			edge[A].pb(B);
			ec  [A].pb(yps[y]-yps[t]);
		}
	}
}

void work(){
	read(sx,sy,tx,ty,n);
	
	for(int i=0; i<sz(xps); ++i) xco[i].clear();
	for(int i=0; i<sz(yps); ++i) yco[i].clear();
	int t=sz(xps)*sz(yps);
	for(int i=0; i<t; ++i) edge[i].clear(), ec[i].clear();

	xps.clear(); yps.clear();

	xps.pb(sx); xps.pb(tx);
	yps.pb(sy); yps.pb(ty);

	for(int i=0; i<n; ++i){
		int a,b,c,d; read(a,b,c,d);
		rec[i].l=min(a,c);
		rec[i].r=max(a,c);
		rec[i].d=min(b,d);
		rec[i].u=max(b,d);

		xps.pb(a); xps.pb(c);
		yps.pb(b); yps.pb(d);
	}

	coord_comp(xps); coord_comp(yps);

	for(int i=0; i<n; ++i){
		int &a=rec[i].l;
		int &b=rec[i].d;
		int &c=rec[i].r;
		int &d=rec[i].u;
		a=v_index(xps, a);
		c=v_index(xps, c);
		b=v_index(yps, b);
		d=v_index(yps, d);

		for(int i=a+1; i<c; ++i){
			xco[i].pb(b); xco[i].pb(d);
			yco[b].pb(i); yco[d].pb(i);
		}
		for(int i=b+1; i<d; ++i){
			yco[i].pb(a); yco[i].pb(c);
			xco[c].pb(i); xco[a].pb(i);
		}
		xco[a].pb(b); xco[a].pb(d);
		xco[c].pb(b); xco[c].pb(d);
		yco[b].pb(a); yco[b].pb(c);
		yco[d].pb(a); yco[d].pb(c);
	}

	sx=v_index(xps, sx);
	sy=v_index(yps, sy);

	tx=v_index(xps, tx);
	ty=v_index(yps, ty);

	xco[sx].pb(sy); yco[sy].pb(sx);
	xco[tx].pb(ty); yco[ty].pb(tx);

	for(int i=0; i<sz(xps); ++i) sort(all(xco[i]));
	for(int i=0; i<sz(yps); ++i) sort(all(yco[i]));

	for(int i=0; i<n; ++i){
		int &l=rec[i].l;
		int &d=rec[i].d;
		int &r=rec[i].r;
		int &u=rec[i].u;
		for(int j=l; j<=r; ++j){
			tryJumps(j, d, 1, 1, (j==l || j==r), 1);
			tryJumps(j, u, 1, 1, 1, (j==l || j==r));
		}
		for(int j=d+1; j<u; ++j){
			tryJumps(l, j, 1, 0, 1, 1);
			tryJumps(r, j, 0, 1, 1, 1);
		}
	}

	tryJumps(sx, sy, 1, 1, 1, 1);
	tryJumps(tx, ty, 1, 1, 1, 1);

	int V=sz(xps)*sz(yps);

	for(int i=0; i<V; ++i) dijk[i]=1LL<<60;

	int sP=conv(sx,sy), tP=conv(tx,ty);

	dijk[sP]=0;
	while(pq.size()) pq.pop();

	pq.push({0, sP});

	while(pq.size()){
		dip tmp=pq.top(); pq.pop();
		int me=tmp.second;
		if(dijk[me] != -tmp.first) continue;
		int sz=edge[me].size();
		for(int i=0; i<sz; ++i){
			int y=edge[me][i];
			int yd=ec [me][i];
			if(dijk[y] > yd+dijk[me]){
				dijk[y]= yd+dijk[me];
				pq.push({-dijk[y],y});
			}
		}
	}

	if(dijk[tP] == (1LL<<60)){
		puts("No Path");
	} else printf("%lld\n", dijk[tP]);
}

int main(){
	int tc;
	read(tc);
	for(;tc--;) work();
	return 0;
}

