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

#define param 710][710
#define map namseo
char map[param];

int vik[param];
int usr[param];

int n,m;

int inf = int(2e9);

int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};

void bfs(int sx,int sy,int d[][710], bool init){
	if(init)
		for(int i=1; i<=n; ++i){
			for(int j=1; j<=m; ++j){
				d[i][j] = inf;
			}
		}

	queue<pp> q;
	q.push({sx, sy});
	d[sx][sy]=0;

	while(q.size()){
		int x,y; tie(x,y) = q.front(); q.pop();
		for(int i=0; i<4; ++i){
			int nx=x+dx[i], ny=y+dy[i];
			if(1<=nx && 1<=ny && nx<=n && ny<=m){
				if(map[nx][ny] == 'I') continue;
				if(d[nx][ny] > d[x][y] + 1){
					d[nx][ny]=d[x][y] + 1;
					q.push({nx,ny});
				}
			}
		}
	}
}

int vikdist[param];

int enc(int x,int y){
	return x*m+y;
}

int par[701*701];
int R(int x){ return (x==par[x])?x:(par[x]=R(par[x])); }

int main(){
	read(n,m);

	int ux=-1,uy=-1;
	int vx=-1,vy=-1;
	int tx=-1,ty=-1;

	for(int i=1; i<=n; ++i){
		scanf("%s",map[i]+1);
		for(int j=1; j<=m; ++j){
			if(map[i][j] == 'V') tie(vx,vy) = tie(i,j);
			else if(map[i][j] == 'Y') tie(ux,uy) = tie(i,j);
			else if(map[i][j] == 'T') tie(tx,ty) = tie(i,j);

			vikdist[i][j] = inf;
		}
	}

	bfs(vx, vy, vik, true);
	
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=m;){
			if(map[i][j] == 'I'){
				++j;
				continue;
			}

			int k;
			int minT = inf;
			for(k=j; k<=m && map[i][k]!='I'; ++k){
				minT = min(minT, vik[i][k]);
			}

			for(int l=j; l<k; ++l){
				vikdist[i][l] = min(vikdist[i][l], minT);
			}

			j=k;
		}
	}
	
	for(int j=1; j<=m; ++j){
		for(int i=1; i<=n;){
			if(map[i][j] == 'I'){
				++i;
				continue;
			}

			int k;
			int minT = inf;
			for(k=i; k<=n && map[k][j]!='I'; ++k){
				minT = min(minT, vik[k][j]);
			}

			for(int l=i; l<k; ++l){
				vikdist[l][j] = min(vikdist[l][j], minT);
			}

			i=k;
		}
	}

	for(int i=1; i<=n; ++i) for(int j=1; j<=m; ++j){
		usr[i][j] = vikdist[i][j];
	}

	int in_val = usr[tx][ty];
	
	bfs(ux, uy, usr, false);

	if(in_val != usr[tx][ty]){
		puts("YES");
	} else puts("NO");

	return 0;
}
