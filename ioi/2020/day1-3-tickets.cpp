#include "tickets.h"
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
using pp=pair<int, int>;
using ll=long long;

int n, m, k;
int prog[1510];

priority_queue<pp> pq;
ll ans;

int pg(auto &x, int i, int j) {
	return -x[i][j]-x[i][m-k+j];
}

#include <bitset>
bitset<1510> bs;
ll find_maximum(int k_, vector<vector<int>> x) {
	n = x.size(); m = x[0].size(); k = k_;

	for(int i=0; i<n; ++i) for(int j=m-k; j<m; ++j) ans += x[i][j];

	for(int i=0; i<n; ++i) pq.emplace(pg(x, i, 0), i);

	for(int cnt=n*k/2; cnt--;) {
		auto [tv, ti] = pq.top(); pq.pop();
		ans += tv;
		if (++prog[ti] != k) {
			pq.emplace(pg(x, ti, prog[ti]), ti);
		}
	}

	int ri = 0;
	for(int i=0; i<n; ++i) {
		fill(x[i].begin(), x[i].end(), -1);
		int t = prog[i];
		for(int j=0; j<t; ++j) {
			x[i][j] = ri;
			bs[ri] = 1;
			if (++ri == k) ri = 0;
		}
		int ng = 0;
		for(int j=m-(k-prog[i]); j<m; ++j) {
			while (bs[ng]) ++ng;
			x[i][j] = ng++;
		}
		bs.reset();
	}

	allocate_tickets(x);

	return ans;
}
