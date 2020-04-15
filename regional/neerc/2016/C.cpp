#include <bits/stdc++.h>
using namespace std;
using pp=pair<int,int>;
#define pb push_back
#define all(v) v.begin(), v.end()

#define D if(0)

const int maxn = 50010;

int n;
vector<int> e[maxn];
int col[maxn];

void in(){
	int m;
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
for(;m--;){
	int cnt, last;
	cin >> cnt >> last;
	for(;--cnt;){
		int x; cin >> x;
		e[last].pb(x); e[x].pb(last);
		last = x;
	}
}
}

set<pp> nc;

bool on[maxn];
int low[maxn], nt;
int dep[maxn];
int par[maxn];
vector<int> cyc[maxn]; int cn;
map<pp,int> ci;
void dfs(int x){
	on[x] = 1;
	low[x] = dep[x];
	for(int y:e[x]) if(!dep[y]){
		par[y] = x;
		dep[y] = dep[x] + 1;
		dfs(y);
		low[x] = min(low[x], low[y]);
		if(low[y] > dep[x]){
			nc.emplace(x, y);
			nc.emplace(y, x);
			D cout << "Non-cyclic edge " << x << ", " << y << '\n';
		}
	} else if(on[y] && y!=par[x]){
		low[x] = min(low[x], dep[y]);
		auto &v=cyc[++cn];
		D cout << "Cycle " << cn << " : ";
		for(int i=x; ; i=par[i]){
			v.pb(i);
			D cout << i << '-';
			if(i == y) break;
		}
		D cout << endl;
		int sz = v.size();
		for(int i=0; i<sz; ++i){
			ci[pp(v[i], v[(i+1)%sz])] = cn;
			ci[pp(v[i], v[(i+sz-1)%sz])] = cn;
		}
	}
	on[x] = 0;
}

bool dead[maxn];

vector<int> ans; int an;

void g_join(int a, int b){
	D cout << "Join " << a << " and " << b << endl;
	++an;
	ans.push_back(-'j');
	ans.push_back(a);
	ans.push_back(b);
}

void g_recolor(int a, int b, int c){
	D cout << "Recolor " << a << " from " << b << " to " << c << endl;
	++an;
	ans.push_back(-'r');
	ans.push_back(a);
	ans.push_back(b);
	ans.push_back(c);
}

void g_connect(int a, int b, int c){
	D cout << "Connect " << a << " from " << b << " to " << c << endl;
	++an;
	ans.push_back(-'c');
	ans.push_back(a);
	ans.push_back(b);
	ans.push_back(c);
}

void work(int x){
	dead[x] = 1;
	D cout << "Work " << x << " called\n";
	for(int y:e[x]){
		if(dead[y]) continue;
		if(nc.count(pp(x, y))){
			D cout << "Work " << x << ": tracing non-cyc edge " << y << '\n';
			work(y);
			g_recolor(y, 1, 2);
			g_join(x, y);
			g_connect(x, 1, 2);
			g_recolor(x, 2, 4);
		} else {
			int c = ci[pp(x, y)];
			auto &v = cyc[c];
			rotate(v.begin(), find(all(v), x), v.end());
			for(int y:v) dead[y] = 1;
			D{ cout << "Work " << x << ": treating cycle ";
			for(int y:v) cout << y << '-';
			cout << x << '\n'; }
			int sz = v.size();
			g_recolor(x, 1, 2);
			work(v[1]);
			g_join(x, v[1]);
			g_connect(x, 1, 2);
			for(int i=2; i<sz; ++i){
				int y = v[i];
				work(y);
				g_recolor(y, 1, 3);
				g_join(x, y);
				g_connect(x, 1, 3);
				g_recolor(x, 1, 4);
				g_recolor(x, 3, 1);
			}
			g_connect(x, 2, 1);
			g_recolor(x, 1, 4);
			g_recolor(x, 2, 1);
		}
	}
}

int main(){
	in();

	dep[1] = 1; dfs(1);

	work(1);

	cout << an;
	for(int x:ans){
		if(x < 0){
			cout << '\n' << char(-x);
		} else {
			cout << ' ' << x;
		}
	}
	cout << '\n';
	return 0;
}
