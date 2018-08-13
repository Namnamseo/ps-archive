#include "rail.h"
#include <bits/stdc++.h>
using namespace std;
using pp=pair<int,int>;
#define all(v) (v).begin(), (v).end()
#define pb push_back

int dcache[5000][5000];
int get_dist(int a, int b){
	if(dcache[a][b]) return dcache[a][b]-1;
	int d = getDistance(a, b);
	dcache[a][b] = d+1;
	return d;
}

vector<pp> ds;
vector<int> lv, rv;
bool ex[1000010];
bool ex2[1000010];
void findLocation(int n, int first, int location[], int stype[])
{
	if(n == 1){
		location[0] = first;
		stype[0] = 1;
		return;
	}

	for(int i=1; i<n; ++i) ds.emplace_back(get_dist(0, i), i);
	sort(all(ds));

	int diam, ri;
	tie(diam, ri) = ds[0];
	int rp = first + diam;

	location[0] = first; stype[0] = 1;
	location[ri] = rp; stype[ri] = 2;

	for(int t=1; t<n-1; ++t){
		int i = ds[t].second;
		int dl = get_dist(0, i);
		int dr = get_dist(ri, i);

		if(dr < diam && dl == diam + dr){
			location[i] = rp - dr;
			stype[i] = 1;
			continue;
		}

		if(dl == dr + diam) lv.pb(i);
		else rv.pb(i);
	}

	int lp = first, li = 0;
	for(int i : lv){
		int ld = get_dist(li, i);
		int tm = (rp - lp) + ld - get_dist(ri, i);
		tm /= 2;
		if(lp + tm <= int(1e6) && ex[lp+tm]){
			location[i] = lp + ld;
			stype[i] = 2;
		} else {
			lp = rp - get_dist(ri, i);
			li = i;
			location[i] = lp;
			stype[i] = 1;
			ex[lp] = 1;
		}
	}

	for(int i : rv){
		int rd = get_dist(ri, i);
		int tm = (rp-first) + rd - get_dist(0, i);
		tm /= 2;
		if(0 <= rp-tm && ex2[rp-tm]){
			location[i] = rp - rd;
			stype[i] = 1;
		} else {
			rp = first + get_dist(0, i);
			ri = i;
			location[i] = rp;
			stype[i] = 2;
			ex2[rp] = 1;
		}
	}
}
