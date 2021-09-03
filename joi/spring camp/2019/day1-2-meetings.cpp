#include "meetings.h"
#include <algorithm>
#include <map>
#include <numeric>
#include <vector>
using namespace std;

void bridge(int a, int b) { if (a>b) swap(a, b); Bridge(a, b); }

void work_set(int *v, int n) {
	if (n == 1) return;
	int a = v[0], b = v[1];
	int *par = new int[n]; par[0]=a, par[1]=b;
	for (int i=2; i<n; ++i) par[i]=Query(a, b, v[i]);

	{ int *ps = new int[n]; iota(ps, ps+n, 0);
	sort(ps, ps+n, [&](const int& a, const int& b) { return par[a] < par[b]; });
	for (int i=0, j; i<n; i=j) {
		for (j=i+1; j<n && par[ps[i]]==par[ps[j]]; ++j);
		for (int t=i; t<j; ++t) ps[t] = v[ps[t]];
		work_set(ps+i, j-i);
	}
	delete[] ps; }

	sort(par, par+n);
	n = unique(par, par+n) - par;
	{ int w = 0; for (int i=0; i<n; ++i) {
		if (par[i] == a || par[i] == b) continue;
		if (i != w) par[w] = par[i]; ++w;
	} n = w; }
	if (!n) { bridge(a, b); delete[] par; return; }

	sort(par, par+n, [&](const int& x, const int& y) { return Query(x, y, a) == x; });

	bridge(a, par[0]);
	for (int i=1; i<n; ++i) bridge(par[i-1], par[i]);
	bridge(par[n-1], b);
	delete[] par;
}

void Solve(int N) {
	vector<int> v(N);
	iota(v.begin(), v.end(), 0);
	work_set(v.data(), N);
}
