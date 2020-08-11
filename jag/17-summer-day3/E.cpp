#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;
#define rep(i,n) for(int i=0; i<n; ++i)
#define rrep(i,n) for(int i=1; i<=n; ++i)
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define all(x) x.begin(), x.end()

const ll LIM = ll(1e15);

vector<pll> ln[51][51];

int n, m;
char S[60][60];

bool ccw(pll l1, pll l2, pll l3){
	return (l1.y - l2.y) * (l3.x - l2.x) < (l3.y - l2.y) * (l1.x - l2.x);
}

int main(){
	cin >> n >> m;
	rrep(i, n) cin >> (S[i]+1);

	ln[1][0].eb(1, 0);
	rrep(rss, n+m){
		rrep(i, n){
			int j = rss - i;
			if(j<1 || j>m) continue;

			auto &lv = ln[i][j];

			auto add_line = [&](ll g, ll y){
				if(g > LIM || y > LIM){
					cout << -1 << endl;
					exit(0);
				}

				lv.eb(g, y);
			};

			for(pll dp:{pll{-1, 0}, pll{0, -1}}){
				int bx=i+dp.x, by=j+dp.y;

				for(auto l:ln[bx][by]){
					if(S[i][j] == '+'){
						add_line(1, l.x + l.y);
					} else if(S[i][j] == '*'){
						add_line(l.x, l.y);
					} else {
						add_line(l.x*(S[i][j]-'0'), l.y);
					}
				}
			}

			sort(all(lv), [&](const pll& a, const pll& b){
				if(a.x == b.x) return a.y > b.y;
				else return a.x < b.x;
			});

			lv.erase(unique(all(lv), [&](const pll& a, const pll& b){ return a.x == b.x; }), lv.end());

			vector<pll> tmp;
			for(auto l:lv){
				while(tmp.size() >= 2u && !ccw(tmp[tmp.size()-2], tmp[tmp.size()-1], l)) tmp.pop_back();
				tmp.pb(l);
			}

			swap(tmp, lv);
		}
	}

	ll ans = 0;
	for(auto l:ln[n][m]){
		ans = max(ans, l.x + l.y);
	}

	if(ans > LIM) ans = -1;

	cout << ans << endl;
	return 0;
}
