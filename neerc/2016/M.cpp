#include <bits/stdc++.h>
using namespace std;

using ll=long long;

int n, m;

int food[100'010];

ll ans;

int dep[100'010];
int nt;

void dfs(int x){
	if(x > n) return;
	dep[x] = dep[x/2]+1;
	dfs(x*2); dfs(x*2+1);
}

const int inf = 1e9;
using pp=pair<int,int>;
const pp dft {inf, -1};

int upflow[100'010];

pp tree[100'010];
pp me[100'010];

void pull(int x){
	tree[x] = me[x];
	for(int it=2*x; it<=2*x+1 && it<=n; ++it){
		tree[x] = min(tree[x], pp{tree[it].first + 1-(upflow[it]>0)*2, tree[it].second});
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);

	cin >> n >> m;
	dfs(1);

	fill(me+1, me+n+1, dft);
	fill(tree+1, tree+n+1, dft);

	for(int i=1; i<=n; ++i){
		cin >> food[i];
		if(!food[i]) continue;
		me[i] = pp{0, i};
	}

	for(int i=n; 1<=i; --i) pull(i);

	for(;m--;){
		int s; cin >> s;

		pp pick = dft; int pickx = -1;
		int upd = 0;

		for(int a=s; a; a/=2){
			pp tmp = tree[a];
			tmp.first += upd;

			if(pick > tmp){
				pick = tmp;
				pickx = a;
			}

			if(upflow[a] < 0) --upd;
			else ++upd;
		}

		assert(pickx != -1);
		ans += pick.first;
		printf("%lld ", ans);

		int bot = pick.second;
		--food[bot];
		if(!food[bot]) me[bot]=dft, pull(bot);

		for(int i=bot; i!=pickx; i/=2) upflow[i] -= 1, pull(i/2);
		for(int i=s; i!=pickx; i/=2) upflow[i] += 1, pull(i/2);
		for(int i=pickx; i; i/=2) pull(i);
	}

	return 0;
}
