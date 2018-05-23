#include "molecules.h"
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pp;
pp d[200010];
using ll=long long;
ll ps[200010];

vector<int> find_subset(int l, int u, vector<int> w) {
	int n = w.size();
	for(int i=0; i<n; ++i){
		d[i]={w[i], i};
	}
	sort(d, d+n);
	for(int i=0; i<n; ++i) ps[i+1]=ps[i]+d[i].first;
	for(int i=1; i<=n; ++i){
		int lp=lower_bound(ps, ps+i, ps[i]-u)-ps;
		if(ps[i]-ps[lp] >= l){
			vector<int> ret;
			for(int j=lp+1; j<=i; ++j) ret.push_back(d[j-1].second);
			return ret;
		}
	}
	return vector<int>();
}
