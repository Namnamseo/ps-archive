#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using pp=pair<int,int>;
#define rrep(i, n) for(int i=1; i<=n; ++i)
#define pb push_back
#define eb emplace_back

int n, m, k, s;

int a[12][12];

bool pick[12][12];

vector<pp> lst, must;

void dfs(int x, int y, int left){
	if(y > m){
		int sm = 0;
		rrep(j, m){
			sm += a[x][j];
			if(sm > s) return;
			if(sm < 0) sm = 0;
		}
		++x;
		y = 1;
	}

	if(x > n){
		rrep(j, m) {
			int sm = 0;
			rrep(i, n){
				sm += a[i][j];
				if(sm > s){
					return;
				}
				if(sm < 0) sm = 0;
			}
		}

		cout << "Yes" << endl;
		exit(0);
	}

	if(!pick[x][y] && left){
		a[x][y] = -a[x][y];
		dfs(x, y+1, left-1);
		a[x][y] = -a[x][y];
	}

	dfs(x, y+1, left);
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);

	cin >> n >> m >> k >> s;
	rrep(i, n) rrep(j, m) cin >> a[i][j];

	rrep(i, n){
		rrep(j, m) {
			int sm = 0;
			for(int t=0; j+t<=m; ++t){
				sm += a[i][j+t];
				if(sm > s){
					for(int tt=0; tt<=t; ++tt)
						must.eb(i, j+tt);
					break;
				}
			}
			if(must.size()) break;

			sm = 0;
			for(int t=0; i+t<=n; ++t){
				sm += a[i+t][j];
				if(sm > s){
					for(int tt=0; tt<=t; ++tt)
						must.eb(i+tt, j);
					break;
				}
			}
			if(must.size()) break;

		}
		if(must.size()) break;
	}

	if(must.empty()){
		cout << "Yes\n";
		return 0;
	}

	for(auto tmp:must) pick[tmp.first][tmp.second] = 1;

	for(auto tmp:must){
		int x, y; tie(x, y) = tmp;
		a[x][y] = -a[x][y];
		dfs(1, 1, k-1);
		a[x][y] = -a[x][y];
	}
	cout << "No\n";
	return 0;
}

