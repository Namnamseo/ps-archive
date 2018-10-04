#include <bits/stdc++.h>
using namespace std;

int n;

using pp=pair<int,int>;
using ll=long long;

pp d[2010];

#define x first
#define y second

int main(){
	scanf("%d", &n);
	int x, y;
	for(int i=1; i<=n; ++i){
		int a, b;
		scanf("%d%d", &a, &b);
		if(i == 1){
			x = a;
			y = 0;
		} else {
			y -= (a-x);
			x = a;
		}
		d[2*i-1] = {x, y};
		y += (b-x);
		x = b;
		d[2*i] = {x, y};
	}
	d[2*n+1] = {x+y, 0};
	int h; scanf("%d", &h);
	int hy;
	ll ans = 0;
	for(int i=1; i<=2*n; ++i){
		if(d[i].x <= h && h <= d[i+1].x){
			if(d[i].y <= d[i+1].y)
				hy = d[i].y + (h-d[i].x);
			else
				hy = d[i].y - (h-d[i].x);
			break;
		}
	}

	for(int i=1; i<=2*n+1; ++i){
		if(d[i].x >= h) break;
		ll a, b; tie(a, b) = d[i];
		ll ja = b * (h-a) - a*(hy - b);
		ll mo = (h-a);
		if(ja < 0) continue;
		ans = max(ans, (ja+mo-1)/mo);
	}

	printf("%lld\n", ans);
	return 0;
}

