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
#define eb emplace_back
#define x first
#define y second

int n;

int a[2][100010];
int P[200010];
int R(int x){ return (x==P[x])?x:(P[x]=R(P[x])); }
void Join(int a,int b){ a=R(a); b=R(b); P[a]=b; }

void Conn(int i, int j, int k, int l){
	if(a[i][j] == a[k][l]){
		Join(i*n+j, k*n+l);
	}
}

bool chk[200010];
int col[200010];
vector<int> ce[200010];

void Draw(int i, int j, int k, int l){
	if(a[i][j] != a[k][l]){
		int ra = R(i*n+j);
		int rb = R(k*n+l);
		if(ra > rb) swap(ra, rb);
		ce[ra].pb(rb);
	}
}

int Conv(int x){
	if(x > 0) return x;
	return 300 - x;
}

int cost[700][700];
int cap[700][700];
vector<int> edge[700];

void Cc(int a, int b, int df=1){
	if((a>0) == (b>0)) return;
	if(a<b) swap(a, b);
	cost[Conv(a)][Conv(b)] -= df;
	cost[Conv(b)][Conv(a)] += df;
}

const int source = 601;
const int sink = 602;
const int V = 602;

int dst[700];
const int inf = 1e9;
int bef[700];
bool iq[700];
queue<int> q;

bool spfa(){
	for(int i=1; i<=V; ++i) dst[i]=inf, bef[i]=-1;
	q.push(source); dst[source]=0; iq[source]=1;
	while(q.size()){
		int x=q.front(); q.pop(); iq[x]=0;
		for(int y:edge[x]){
			if(!cap[x][y]) continue;
			if(dst[y] > dst[x] + cost[x][y]){
				dst[y] = dst[x] + cost[x][y];
				bef[y] = x;
				if(!iq[y]) q.push(y), iq[y]=1;
			}
		}
	}
	return bef[sink] != -1;
}

int main()
{
	read(n);
	for(int i=1; i<=2*n; ++i) P[i]=i;
	for(int i=0; i<2; ++i) for(int j=1; j<=n; ++j){
		read(a[i][j]);
		if(i) Conn(i, j, i-1, j);
		if(j>1) Conn(i, j, i, j-1);
	}
	int comps = 0;
	for(int i=0; i<2; ++i) for(int j=1; j<=n; ++j){
		int r = R(i*n+j);
		col[r]=a[i][j];
		if(!chk[r]){
			++comps; chk[r] = 1;
		}
		if(i) Draw(i, j, i-1, j);
		if(j>1) Draw(i, j, i, j-1);
	}
	for(int j=1; j<n; ++j){
		if(a[0][j] == a[1][j+1] && a[1][j] == a[0][j+1]){
			Cc(a[0][j], a[1][j], -1);
		}
	}
	
	for(int i=1; i<=2*n; ++i){
		auto& v=ce[i];
		sort(all(v));
		v.erase(unique(all(v)), v.end());
		for(int j:v){
			Cc(col[i], col[j]);
		}
	}
	
	auto F = [&](int s, int e){ edge[s].pb(e); edge[e].pb(s); cap[s][e]=1; };
	for(int i=1; i<=300; ++i){
		F(source, Conv(i));
		F(Conv(-i), sink);
		for(int j=1; j<=300; ++j) F(Conv(i), Conv(-j));
	}
	
	int ans = 0;
	while(spfa()){
		int p = sink;
		while(p != source){
			int q = bef[p];
			cap[q][p]=0;
			cap[p][q]=1;
			ans += cost[q][p];
			p = q;
		}
	}
	
	printf("%d\n", comps + ans);
	return 0;
}

