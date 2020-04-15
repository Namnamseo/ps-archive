#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using pp=pair<int,int>;
#define eb emplace_back

int n, k, mn, mx;

ll a[1010];

ll ans;

void in(){
	ios_base::sync_with_stdio(0); cin.tie(0);

	cin >> n >> k >> mn >> mx;
	tie(mn, mx) = make_pair(mx, k-mn);

	for(int i=1; i<=n; ++i){
		cin >> a[i];
		ans += a[i];
	}
	for(int i=1; i<=n; ++i){
		ll tmp; cin >> tmp;
		a[i] = tmp - a[i];
	}
}

int src, snk;
int V;
int T;
const int maxv = 1005;

struct edge {
	int to, cap, rev, cost;
	edge(int a,int b,int c,int d):to(a), cap(b), rev(c), cost(d){}
};
vector<edge> gph[maxv];

void add_edge(int f, int t, int cap, int cost){
	gph[f].eb(t, cap, gph[t].size(), cost);
	gph[t].eb(f, 0, gph[f].size()-1, -cost);
}

ll dst[maxv];
const ll inf = 1ll<<60;
bool inq[maxv];
int par[maxv], pe[maxv];

bool spfa(){
	queue<int> q;
	fill(dst+1, dst+V+1, inf);
	fill(inq+1, inq+V+1, 0);
	dst[src] = 0; q.push(src);

	int sc = 0;
	while(q.size()){
		int x = q.front(); q.pop();
		++sc;
		inq[x] = 0;

		int sz = gph[x].size();
		for(int i=0; i<sz; ++i){
			auto &tmp = gph[x][i];
			if(!tmp.cap) continue;
			if(dst[tmp.to] > dst[x] + tmp.cost){
				dst[tmp.to] = dst[x] + tmp.cost;
				par[tmp.to] = x;
				pe[tmp.to] = i;
				if(!inq[tmp.to]){
					inq[tmp.to] = 1;
					q.push(tmp.to);
				}
			}
		}
	}

	return dst[snk] != inf;
}

int mys[maxv], myi[maxv];

int main(){
	in();

	T = (n-k+1);
	V = T + 2;
	src = V, snk = V-1;

	add_edge(src, 1, mx, 0);
	for(int i=1; i<=T; ++i) add_edge(i, i+1, mx-mn, 0);
	for(int i=1; i<=n; ++i){
		int f=max(1, i-k+1);
		int t=min(snk, i+1);
		mys[i] = f;
		myi[i] = gph[f].size();
		add_edge(f, t, 1, -a[i]);
	}

	for(int i=0; i<mx; ++i){
		assert(spfa());
		ans -= dst[snk];
		for(int q=snk; q!=src; q=par[q]){
			int p=par[q], i=pe[q];
			gph[p][i].cap -= 1;
			gph[q][gph[p][i].rev].cap += 1;
		}
	}

	cout << ans << endl;

	for(int i=1; i<=n; ++i){
		auto &e = gph[mys[i]][myi[i]];
		if(e.cap == 0) cout << 'E';
		else cout << 'S';
	}

	cout << '\n';

	return 0;
}
