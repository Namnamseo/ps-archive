#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using pp=pair<int,int>;
#define rrep(i, n) for(int i=1; i<=n; ++i)
#define pb push_back
#define eb emplace_back

int n;

vector<int> e[10010];

bool dead[10010];

int udc(int x){
	int ret = 0;
	for(int y:e[x]) ret += !dead[y];
	return ret;
}

bool di(int x){
	for(int y:e[x]) if(dead[y]) return 1;
	return 0;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);

	cin >> n;
	for(int i=2*n*n-2*n; i--;){
		int a, b; cin >> a >> b;
		e[a].pb(b); e[b].pb(a);
	}

	int corner = -1;
	rrep(i, n*n) if(udc(i) == 2){
		corner = i;
		break;
	}

	cout << corner << ' ';
	int last = e[corner][0], other = e[corner][1];
	dead[corner] = 1;
	for(int i=2; i<=n; ++i){
		cout << last << (i==n ? '\n':' ');
		dead[last] = 1;
		if(i < n){
			for(int x:e[last]) if(!dead[x] && udc(x) == 2-(i+1 == n)){
				last = x;
				break;
			}
		}
	}

	for(int row=2; row<=n; ++row){
		last = other;
		for(int x:e[last]) if(!dead[x]){
			if(!di(x)){
				static int chk = 0;
				if(row == 1 && !chk){
					chk = 1;
					continue;
				}
				other = x;
				break;
			}
		}

		cout << last << ' ';
		for(int j=2; j<=n; ++j){
			int bl = last;
			for(int x:e[last]) if(!dead[x] && di(x)){
				last = x;
				break;
			}
			dead[bl] = 1;
			cout << last << (j==n ? '\n' :' ');
		}
		dead[last] = 1;
	}
	return 0;
}

