#include <bits/stdc++.h>
using namespace std;
using pp=pair<int,int>;
#define x first
#define y second
#define rep(i, n) for(int i=0; i<n; ++i)
#define rrep(i, n) for(int i=1; i<=n; ++i)
#define pb push_back
#define eb emplace_back
using ll=long long;

int n, m;
int a[510][60];
ll ps[510][60];

int xp[110], xn;

ll f(int i, int x){
	int pt = upper_bound(a[i]+1, a[i]+m+1, x) - a[i];
	return ps[i][pt-1] + ll(m+1-pt) * x;
}

void work(int r){
	map<int,int> df;

	rrep(i, n) if(i!=r){
		int lon = 0, bx = 0;
		xn = 0;
		rrep(j, m) xp[xn++] = a[i][j];
		rrep(j, m) xp[xn++] = a[r][j];

		sort(xp, xp+xn); xn = unique(xp, xp+xn) - xp;
		ll br = 0, bi = 0;
		for(int xi=0; xi<xn; ++xi){
			int x=xp[xi];
			ll cr = f(r, x), ci = f(i, x);
			ll dx = x - bx;
			ll myinc = cr-br, thyinc = ci-bi;
			if(lon != -1 && cr < ci){
				ll nx = bx + (br-bi) * dx / (thyinc - myinc);
				df[lon] ++;
				df[nx+1] --;
				lon = -1;
			} else if(lon == -1 && cr >= ci){
				ll nx = x - (cr-ci) * dx / (myinc - thyinc);
				lon = nx;
			}
			br = cr; bi = ci; bx = x;
		}

		if(lon != -1) df[lon] ++;
	}

	int ans = n+1, cur = 1;
	for(auto& tmp:df) if(tmp.x <= int(1e9)){
		ans = min(ans, cur += tmp.y);
	}
	cout << ans << '\n';
}

int main(){ ios_base::sync_with_stdio(0); cin.tie(0);

	cin >> n >> m;
	rrep(i, n){
		rrep(j, m) cin >> a[i][j];
		sort(a[i]+1, a[i]+m+1);
	}

	rrep(i, n) rrep(j, m) ps[i][j] = ps[i][j-1] + a[i][j];

	rrep(i, n) work(i);
	return 0;
}
