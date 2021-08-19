#include <bits/stdc++.h>
#include "aliens.h"
using namespace std;
typedef pair<int,int> pp;
typedef long long ll;

pp po[100010];
ll x[100010];
ll y[100010];
int pn;

ll dp[100010];

int top;
ll grad[100010];
ll yint[100010];
int lid[100010];
void add_line(ll g, ll y, int id){
	while(top>=2){
		if((yint[top-2]-yint[top-1])*(grad[top-1]-g)>
		(yint[top-1]-y)*(grad[top-2]-grad[top-1])) break;
		--top;
	}
	grad[top] = g;
	yint[top] = y;
	lid[top] = id;
	++top;
}
int bx;
ll f(int p, ll x){ return grad[p]*x + yint[p]; }
inline ll sqr(ll x){ return x*x; }
int lst[100010];
int F(ll cost){
	top = 0; bx = 0;
	add_line(-2*x[0], sqr(x[0]), -1);
	for(int i=0; i<pn; ++i){
		while(bx+1 < top && f(bx, y[i]+1) > f(bx+1, y[i]+1)) ++bx;
		dp[i]=f(bx, y[i]+1)+sqr(y[i]+1)+cost;
		lst[i]=lid[bx];
		if(i+1 < pn){
			add_line(-2*x[i+1], dp[i]+sqr(x[i+1])-sqr(max(0ll, y[i]-x[i+1]+1)), i);
			bx = min(bx, top-1);
		}
	}
	int cnt = 0;
	for(int i=pn-1; i!=-1; i=lst[i]) ++cnt;
	return cnt;
}

long long take_photos(int n, int m, int k, std::vector<int> r, std::vector<int> c) {
	for(int i=0; i<n; ++i){
		int x=r[i], y=c[i];
		if(x>y) swap(x, y);
		po[i]={x, y};
	}
	sort(po, po+n);
	for(int i=0; i<n; ++i){
		int cx=po[i].first, cy=po[i].second;
		if(!pn){
			x[pn]=cx; y[pn]=cy; ++pn;
			continue;
		}
		if(x[pn-1] == cx) y[pn-1] = cy;
		else if(y[pn-1] < cy) x[pn]=cx, y[pn]=cy, ++pn;
	}
	ll cl = -1, cr = m*1LL*m;
	while(cl+1 < cr){
		ll mid = (cl+cr)/2;
		(F(mid) <= k ? cr : cl) = mid;
	}
	F(cr);
	return dp[pn-1]-cr*k;
}
