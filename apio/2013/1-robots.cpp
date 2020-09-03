#include <cstdio>
#include <cstring>
#include <utility>
#include <functional>
#include <queue>
#define rep(i,n) for(int i=0;i<n;++i)
#define rrep(i,n) for(int i=1;i<=n;++i)
#define x first
#define y second
#define eb emplace_back
using namespace std;
using pp=pair<int,int>;
int n, m, k;
char q[510][510];
pp e[510][510][4];
pp il[10];

int dp[510][510][50];
bool vis[510][510][50];

const int dx[5] = {0, 1, 0, -1}, *dy = dx+1;
pp E(int x, int y, int d) {
	pp &ret = e[x][y][d];
	if (ret.x) return ret;
	int nx=x+dx[d], ny=y+dy[d];
	if (1<=nx && nx<=n && 1<=ny && ny<=m && q[nx][ny]!='x') {
		switch(q[nx][ny]) {
			case 'A': ret = E(nx, ny, (d+3)%4); break;
			case 'C': ret = E(nx, ny, (d+1)%4); break;
			default: ret = E(nx, ny, d); break;
		}
		return ret;
	} else return ret={x, y};
}

int C[10][10];

using t3=tuple<int,int,int>;
t3 qv[2500000];
int st[250010];
int nxt[2500000];
int nn;

int main()
{
	scanf("%d%d%d",&k,&m,&n);
	rrep(i, n) {
		scanf("%s", q[i]+1);
		rrep(j, m) if ((q[i][j]&48)==48) il[q[i][j]-48]={i,j};
	}

	{ static int p = 0; rrep(i, k) rrep(j, i) C[j][i] = ++p; }

	const int inf = 1e9;

	rrep(len, k) {
		nn = 0;
		rrep(i, n) rrep(j, m) rrep(l, k-len+1) {
			int r = l+len-1;
			int p = C[l][r];
			int me = inf;
			if (len == 1 && q[i][j]>=48 && q[i][j]<58 && l == q[i][j]-48) me = 0;
			else for(int t=l; t<r; ++t) {
				int v = dp[i][j][C[l][t]]+
						dp[i][j][C[t+1][r]];
				if (v >= inf) continue;
				if (v < me) me = v;
			}
			dp[i][j][p] = me;
			if (me != inf) {
				int x = ++nn; qv[x] = {i, j, l};
				if (!st[me]) st[me] = x;
				else nxt[x] = st[me], st[me] = x;
			}
		}

		if (len == k) break;

		for(int ans=0; ans<n*m; st[ans]=0, ++ans) for(int v=st[ans]; v; ) {
			int x,y,l,u;
			tie(x,y,l) = qv[v]; u = nxt[v]; nxt[v] = 0; v = u;
			int p = C[l][l+len-1];
			if (dp[x][y][p] != ans) continue;

			rep(d, 4) {
				pp t = E(x, y, d);
				if (t == pp(x, y)) continue;
				if (dp[t.x][t.y][p] > ans+1) {
					dp[t.x][t.y][p] = ans+1;
					int x = ++nn; qv[x] = {t.x, t.y, l};
					if (!st[ans+1]) st[ans+1]=x;
					else nxt[x]=st[ans+1], st[ans+1]=x;
				}
			}
		}
	}

	int ans = inf;
	rrep(i, n) rrep(j, m)
		ans = min(ans, dp[i][j][C[1][k]]);

	if (ans == inf) ans = -1;

	printf("%d\n", ans);

	return 0;
}
