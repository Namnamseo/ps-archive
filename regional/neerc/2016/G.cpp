#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using pp=pair<int,int>;
#define pb push_back
#define eb emplace_back

int n, m;
const int maxn = 100010;
const int maxv = maxn * 2;

//vector<int> e[maxv];
vector<int> re[maxv];
int ind[maxv];

// 0: finite
// 1: infinite

bool chk[maxv];
bool win[maxv];
bool vis[maxv];

void ae(int f, int t){ /*e[f].pb(t);*/ re[t].pb(f); ++ind[f]; }

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);

	cin >> n >> m;
	for(;m--;){
		int a, b; cin >> a >> b;
		ae(2*a, 2*b+1); ae(2*a+1, 2*b);
	}

	queue<int> q;
	for(int i=2; i<=2*n+1; ++i) if(!ind[i]){
		chk[i] = 1;
		q.push(i);
	}

	while(q.size()){
		int x = q.front(); q.pop();
		for(int y:re[x]){
			--ind[y];
			if(y%2 == 0 || !ind[y]){
				if(!chk[y]){
					chk[y] = 1;
					q.push(y);
				}
			}
		}
	}

	fill(ind+2, ind+2*n+2, 0);
	for(int i=2; i<=2*n+1; ++i) for(int j:re[i]) ++ind[j];
	for(int i=1; i<=n; ++i) win[2*i+1] = 1;
	for(int i=2; i<=2*n+1; ++i) if(i%2==1 && !ind[i]){
		win[i] = 0; vis[i] = 1;
		q.push(i);
	}

	while(q.size()){
		int x = q.front(); q.pop();
		win[x] = !(x%2);
		for(int y:re[x]){
			--ind[y];
			if(y%2 == 0 || !ind[y]){
				if(!vis[y]){
					vis[y] = 1;
					q.push(y);
				}
			}
		}
	}

	for(int i=1; i<=n; ++i){
		if(chk[2*i+1]){
			cout << (win[2*i+1] ? 'W':'L');
		} else cout << 'D';
	}
	cout << '\n';

	for(int i=1; i<=n; ++i){
		if(chk[2*i]){
			cout << (win[2*i] ? 'W':'L');
		} else cout << 'D';
	}
	cout << '\n';

	return 0;
}
