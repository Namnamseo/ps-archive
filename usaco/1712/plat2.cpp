#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
void read(pp& x){ scanf("%d%d",&x.first, &x.second); }
void read(pll& x){ scanf("%lld%lld",&x.first, &x.second); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rrep(i,n) for(int i = 1; i <= (n); ++i)
#define sz(x) (int)(x).size()

int n, m, Q;
char s[1510][1510];

vector<int> edge[1500*1500+1];

int f(int x, int y){ return (x-1)*m + y; }
void con(int a, int b){
	edge[a].pb(b); edge[b].pb(a);
}

int idx[1500*1500+1];
int lol[1500*1500+1];
int nt;
bool onstk[1500*1500+1];
void dfs(int x, int p){
	idx[x]=lol[x]=++nt;
	onstk[x]=1;
	for(int y:edge[x]){
		if(y == p) continue;
		if(!idx[y]){ dfs(y, x); lol[x]=min(lol[x], lol[y]); }
		else if(onstk[y]){ lol[x]=min(lol[x], idx[y]); }
	}
	onstk[x]=0;
}

vector<int> myc[1500*1500+1];
bool vis[1500*1500+1];
int cn;
void color(int x, int c){
	if(c>0) myc[x].pb(c);
	vis[x]=1;
	for(int y:edge[x]){
		if(vis[y]) continue;
		if(idx[x] <= lol[y]){
			myc[x].pb(++cn);
			color(y, cn);
		} else {
			color(y, c);
		}
	}
}

bool cango[1501][1501][4][4];

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

bool valid(int x, int y){ return 1<=x && 1<=y && x<=n && y<=m; }

bool sv[1501][1501][4];

typedef tuple<int,int,int> t3;
queue<t3> q;

bool tv[1501][1501];
void enqueue(){
	queue<pp> q;
	pp ax, bx;
	rrep(i, n) rrep(j, m) if(s[i][j]=='A') ax={i, j}; else if(s[i][j]=='B') bx={i, j};
	q.push(ax); tv[ax.x][ax.y]=1;
	while(q.size()){
		pp p=q.front(); q.pop();
		rep(d, 4){
			int nx=p.x+dx[d], ny=p.y+dy[d];
			if(!valid(nx, ny) || s[nx][ny]=='#' || s[nx][ny]=='B') continue;
			if(!tv[nx][ny]){
				tv[nx][ny]=1;
				q.emplace(nx, ny);
			}
		}
	}
	rep(d, 4){
		int nx=bx.x+dx[d], ny=bx.y+dy[d];
		if(!valid(nx, ny) || s[nx][ny]=='#') continue;
		if(tv[nx][ny]){
			sv[bx.x][bx.y][d]=1;
			::q.emplace(bx.x, bx.y, d);
		}
	}
}

int main()
{
	read(n, m, Q);
	rrep(i, n) scanf("%s", s[i]+1);
	rrep(i, n) rrep(j, m){
		if(s[i][j] == '#') continue;
		if(i-1 >= 1 && s[i-1][j]!='#') con(f(i, j), f(i-1, j));
		if(j-1 >= 1 && s[i][j-1]!='#') con(f(i, j), f(i, j-1));
	}

	rrep(i, n) rrep(j, m) if(s[i][j]!='#'){
		int v = f(i, j);
		if(!idx[v]){
			dfs(v, -1);
			color(v, -1);
		}
	}

	rrep(i, n) rrep(j, m) if(s[i][j] != '#'){
		rep(d1, 4){
			int x=i+dx[d1], y=j+dy[d1];
			if(!valid(x, y) || s[x][y]=='#') continue;
			for(int d2=d1+1; d2<4; ++d2){
				int e=i+dx[d2], r=j+dy[d2];
				if(!valid(e, r) || s[e][r]=='#') continue;
				int v1=f(x, y), v2=f(e, r);
				bool exist = 0;
				for(int c1:myc[v1]){
					for(int c2:myc[v2]) if(c1 == c2){ exist=1; break; }
					if(exist) break;
				}
				cango[i][j][d1][d2] = cango[i][j][d2][d1] = exist;
			}
		}
	}

	enqueue();
	auto relax = [&](int x, int y, int d){
		if(!sv[x][y][d]){
			sv[x][y][d]=1;
			q.emplace(x, y, d);
		}
	};

	while(q.size()){
		int x, y, d; tie(x, y, d) = q.front(); q.pop();
		{
			int nx = x-dx[d], ny=y-dy[d];
			if(valid(nx, ny) && s[nx][ny] != '#'){
				relax(nx, ny, d);
			}
		}
		rep(nd, 4) if(cango[x][y][d][nd]){
			relax(x, y, nd);
		}
	}

	for(;Q--;){
		int a, b; read(a, b);
		bool e=(s[a][b] == 'B');
		rep(d, 4) if(sv[a][b][d]){ e=1; break; }
		puts(e?"YES":"NO");
		fflush(stdout);
	}
	return 0;
}
