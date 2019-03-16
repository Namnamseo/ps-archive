#include <bits/stdc++.h>
using namespace std;

using pp=pair<int,int>;
using ll=long long;

pp s[100010];
char buf[5];

pp q[100010];
ll ans[100010];

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, qn; cin >> n >> qn;
	int lst = 0, lev = 0;

	int minlev = 0;
	for(int i=1; i<=n; ++i){
		int tim, k;
		cin >> buf >> tim >> k;
		s[i] = {lev, tim - lst};
		lst = tim;
		if(buf[0] == '+') lev += k;
		else lev -= k;
		minlev = min(minlev, lev);
	}

	for(int i=1; i<=qn; ++i){ cin >> q[i].first; q[i].first = -q[i].first; q[i].second = i; }
	sort(q+1, q+qn+1);

	int width = 0;
	long long rect = 0;
	lst = minlev;

	sort(s+1, s+n+1);
	int pt = 1;
	for(int i=1; i<=qn; ++i){
		int iv = q[i].first;
		if(iv > lev){
			ans[q[i].second] = -1;
			continue;
		}

		while(pt <= n && s[pt].first <= iv){
			rect += width * ll(s[pt].first - lst);
			width += s[pt].second;
			lst = s[pt].first;
			++pt;
		}

		rect += width * ll(iv - lst);
		lst = iv;

		ans[q[i].second] = rect;
	}

	for(int i=1; i<=qn; ++i){
		if(ans[i] < 0) cout << "INFINITY\n";
		else cout << ans[i] << '\n';
	}
	return 0;
}
