#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second
typedef tuple<int,int,int> t3;
typedef pair<ll, t3> dijk_flg;
const ll inf=(1LL<<60);

int dx[]={0,1,0,-1,0};
int* dy=dx+1;

ll nearest[510][510];
pp player[100010];

int A, B, C;
int N;
int n, m;

void in(){
	read(n, m, A, B, C, N);
	for(int i=1; i<=N; ++i) read(player[i].x, player[i].y);
}

ll dplu[510][510];
ll dpld[510][510];
ll dpru[510][510];
ll dprd[510][510];

void find_nearest(){
	memset(dplu, 0x7f, sizeof(dplu));
	memset(dpld, 0x7f, sizeof(dpld));
	memset(dpru, 0x7f, sizeof(dpru));
	memset(dprd, 0x7f, sizeof(dprd));
	for(int i=1; i<=N; ++i){
		int x, y; tie(x, y) = player[i];
		dplu[x][y]=min(dplu[x][y], 0ll-x-y);
		dpld[x][y]=min(dpld[x][y], 0ll+x-y);
		dpru[x][y]=min(dpru[x][y], 0ll-x+y);
		dprd[x][y]=min(dprd[x][y], 0ll+x+y);
	}
	for(int i=0; i<=n; ++i) for(int j=0; j<=m; ++j)
		dplu[i][j]=min({dplu[i][j], i?dplu[i-1][j]:inf, j?dplu[i][j-1]:inf});
	for(int i=0; i<=n; ++i) for(int j=m; j>=0; --j)
		dpru[i][j]=min({dpru[i][j], i?dpru[i-1][j]:inf, dpru[i][j+1]});
	for(int i=n; i>=0; --i) for(int j=0; j<=m; ++j)
		dpld[i][j]=min({dpld[i][j], dpld[i+1][j], j?dpld[i][j-1]:inf});
	for(int i=n; i>=0; --i) for(int j=m; j>=0; --j)
		dprd[i][j]=min({dprd[i][j], dprd[i+1][j], dprd[i][j+1]});
	
	for(int i=0; i<=n; ++i) for(int j=0; j<=m; ++j){
		nearest[i][j] = inf;
		nearest[i][j]=min(nearest[i][j],+i+j + dplu[i][j]);
		nearest[i][j]=min(nearest[i][j],-i+j + dpld[i][j]);
		nearest[i][j]=min(nearest[i][j],+i-j + dpru[i][j]);
		nearest[i][j]=min(nearest[i][j],-i-j + dprd[i][j]);
		nearest[i][j] *= C;
	}
}

// 0   : stationary
// 1-4 : flying
// 5   : holding & moving

vector<pair<t3, ll>> get_edge_list(int d, int x, int y){
	vector<pair<t3, ll>> v;
	if(d == 0){
		ll ne = nearest[x][y];
		v.eb(t3{1, x, y}, ne+B);
		v.eb(t3{2, x, y}, ne+B);
		v.eb(t3{3, x, y}, ne+B);
		v.eb(t3{4, x, y}, ne+B);
		v.eb(t3{5, x, y}, ne);
	} else if(1<=d && d<=4){
		int nx=x+dx[d-1], ny=y+dy[d-1];
		if(nx<=n && ny<=m && nx>=0 && ny>=0){
			v.eb(t3{d, nx, ny}, A);
		}
		v.eb(t3{0, x, y}, 0);
	} else {
		v.eb(t3{0, x, y}, 0);
		v.eb(t3{1, x, y}, B);
		v.eb(t3{2, x, y}, B);
		v.eb(t3{3, x, y}, B);
		v.eb(t3{4, x, y}, B);
		for(int d=0; d<4; ++d){
			int nx=x+dx[d], ny=y+dy[d];
			if(nx<=n && ny<=m && nx>=0 && ny>=0){
				v.eb(t3{5, nx, ny}, C);
			}
		}
	}
	return v;
}

ll dist[6][510][510];

void dijk(){
	priority_queue<dijk_flg> pq;
	memset(dist, 0x7f, sizeof(dist));
	int sx, sy; tie(sx, sy) = player[1];
	int tx, ty; tie(tx, ty) = player[N];
	dist[0][sx][sy]=0;
	pq.emplace(0, t3{0, sx, sy});
	while(pq.size()){
		int ind, x, y;
		ll d;
		tie(ind, x, y) = pq.top().second;
		d = -pq.top().first;
		pq.pop();
		if(d != dist[ind][x][y]) continue;
		
		for(auto& tmp:get_edge_list(ind, x, y)){
			int ni, nx, ny; tie(ni, nx, ny) = tmp.first;
			ll nd=tmp.second;
			if(dist[ni][nx][ny] > d+nd){
				dist[ni][nx][ny] = d+nd;
				pq.emplace(-dist[ni][nx][ny], t3{ni, nx, ny});
			}
		}
	}
	printf("%lld\n", dist[0][tx][ty]);
}

int main()
{
    in();
    find_nearest();
    dijk();
    return 0;
}
