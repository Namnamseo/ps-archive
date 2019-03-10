#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define rrep(i, n) for(int i=1; i<=n; ++i)
#define pb push_back

int n, m;

vector<int> e[200010];

void con(int a, int b){ e[a].pb(b); e[b].pb(a); }

const ll inf = 1ll<<60;

ll d[200010];

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);

	cin >> n >> m;
	rrep(i, m){
		int a, b; cin >> a >> b;
		con(2*a-1, 2*b);
		con(2*a, 2*b-1);
	}

	fill(d+2, d+2*n+1, inf);
	queue<int> q;
	q.push(1);
	while(q.size()){
		int x=q.front(); q.pop();
		for(int y:e[x]){
			if(d[y] > d[x]+1){
				d[y] = d[x]+1;
				q.push(y);
			}
		}
	}

	ll a[2] = {0, 0};
	for(int df=0; df<2; ++df) rrep(i, n) a[df] = max(a[df], d[2*i-df]);

	ll ans = min(a[0], a[1]);
	if(ans == inf) ans = -1;

	cout << ans << endl;
	return 0;
}

