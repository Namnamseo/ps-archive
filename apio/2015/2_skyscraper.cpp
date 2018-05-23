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

int n, m;
vector<int> b[30010];

const int Lim = 100;
const int V = 30000*(Lim + 1);

int dist[V];
vector<pp> edge[V];

vector<int> usable[30010];

int main()
{
	read(n, m);
	int tg = 0, sp = 0;
	for(int i=0; i<m; ++i){
		int b, p;
		read(b, p);
		if(i == 0) sp = b;
		if(i == 1) tg = b;
		
		if(p <= Lim) ::b[p].pb(b);
		else usable[b].pb(p);
	}
	
	for(int p=1; p<=Lim; ++p) if(b[p].size()){
		for(int a:b[p]) edge[a].eb(p*n+a, 0);
		for(int i=0; i<n; ++i){
			if(i+p < n) edge[p*n+i].eb(p*n+(i+p), 1);
			if(i-p >=0) edge[p*n+i].eb(p*n+(i-p), 1);
			edge[p*n+i].eb(i, 0);
		}
	}
	
	fill(dist, dist+V, 1e9);
	priority_queue<pp> pq;
	dist[sp] = 0;
	pq.emplace(0, sp);
	
	while(pq.size()){
		int md, x; tie(md, x) = pq.top(); pq.pop();
		md = -md;
		if(md != dist[x]) continue;
		
		auto relax = [&](int y, int d){
			if(dist[y] > d){
				dist[y] = d;
				pq.emplace(-d, y);
			}
		};
		for(auto et:edge[x]) relax(et.x, md+et.y);
		
		if(x < n){
			for(int p:usable[x]){
				for(int i=1;;++i) if(x-p*i>=0) relax(x-p*i, md+i); else break;
				for(int i=1;;++i) if(x+p*i<n) relax(x+p*i, md+i); else break;
			}
		}
	}
	
	int ans = dist[tg];
	if(ans == 1e9) ans = -1;
	printf("%d\n", ans);
	return 0;
}

