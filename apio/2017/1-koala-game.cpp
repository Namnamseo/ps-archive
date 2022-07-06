#include "koala.h"
#include <algorithm>
#include <cstdio>
#include <functional>
#include <vector>
#include <numeric>
using namespace std;
using vi=vector<int>;
#define all(v) v.begin(), v.end()

vi Play(vi q) {
	vi ret(q.size());
	playRound(q.data(), ret.data());
	return ret;
}

int minValue(int N, int W) {
	vi v(N);
	v[0] = 1;
	vi res = Play(v);
	if (res[0] >= 1) res[0] -= 1;
	for (int i=0; i<N; ++i) if (!res[i]) return i;
    return 0;
}

int maxValue(int N, int W) {
	vi larger(N);
	iota(larger.begin(), larger.end(), 0);
	while (larger.size() > 1u) {
		vi mask(N);
		int afford = W / larger.size();
		for (int i:larger) mask[i] = afford;

		auto res = Play(mask);
		vi larger_new;
		for (int i:larger) if (res[i]) larger_new.push_back(i);
		larger = larger_new;
	}
    return larger[0];
}

int greaterValue(int N, int W) {
	int l = 0, r = 15;
	vi q(N);
	for (;;) {
		int m = (l+r)/2;
		q[0] = q[1] = m;
		vi res = Play(q);

		if (res[0] != res[1]) {
			return res[0] < res[1];
		}

		if (!res[0]) r = m;
		else l = m;
	}
    return 0;
}

void sort_merge(vector<int> &v, int l, int r,
    function<bool(const int&, const int&)> comp) {
    if (l >= r) return;
    int md = (l+r)/2;
    sort_merge(v, l, md, comp);
    sort_merge(v, md+1, r, comp);
    static int tmp[110];
    int oi=0, il=l, ir=md+1;
    while (il<=md || ir<=r) {
        if (il<=md && (ir>r || comp(v[il], v[ir])))
            tmp[oi++] = v[il++];
        else
            tmp[oi++] = v[ir++];
    }
    for (int i=0; i<oi; ++i) v[l+i] = tmp[i];
}

void solve5(int *P);

void allValues(int N, int W, int *P) {
    if (W == 2*N) {
        vi buf(N);

        fill(all(buf), 2);
        vi tmp = Play(buf);

        vi large, small;
        for (int i=0; i<N; ++i) {
            if (tmp[i] > 2) {
                large.push_back(i);
            } else {
                small.push_back(i);
            }
        }

        fill(all(buf), 0);
        auto Sort = [&](vi &v) {
            sort_merge(v, 0, int(v.size())-1, [&](const int& a, const int& b) {
                buf[a] = buf[b] = 100;
                tmp = Play(buf);
                buf[a] = buf[b] = 0;

                return tmp[a] < tmp[b];
            });
        };
        Sort(small); Sort(large);

        vi out;
        out.insert(out.end(), all(small));
        out.insert(out.end(), all(large));

        for (int i=0; i<N; ++i) P[out[i]] = 1+i;
    } else {
        solve5(P);
    }
}

int costs[101];
bool choose[101];
void simulate() {
    static int dp[101][101];
    static int dpc[101][101];
    static bool dpb[101][101];

    for (int i=1; i<=100; ++i) {
        copy(dp[i-1], dp[i-1]+101, dp[i]);
        copy(dpc[i-1], dpc[i-1]+101, dpc[i]);
        fill(dpb[i], dpb[i]+101, false);
        for (int j=costs[i]+1; j<=100; ++j) {
            int bv = dp[i][j], bc = dpc[i][j];
            int nv = dp[i-1][j-costs[i]-1] + i;
            int nc = dpc[i-1][j-costs[i]-1] + 1;
            if (bv < nv || (bv == nv && bc < nc)) {
                dp[i][j] = nv;
                dpc[i][j] = nc;
                dpb[i][j] = 1;
            }
        }
    }

    for (int i=100, j=100; 1<=i; --i) {
        if (dpb[i][j]) {
            choose[i] = true;
            j -= costs[i]+1;
        } else {
            choose[i] = false;
        }
    }
}

void solve5_recursive(int l, int r, vi is, int *p) {
    if (l == r) { p[is[0]] = l; return; }

    int vl, vr;
    for (vl=1, vr=(100/(r-l+1)); vl<vr;) {
        int vm = (vl+vr)/2;
        fill(costs+l, costs+r+1, vm);
        simulate();
        int cc = 0;
        for (int i=l; i<=r; ++i) cc += choose[i];
        if (cc == 0) vr = vm-1;
        else if (cc == r-l+1) vl = vm+1;
        else vl = vr = vm;
    }
    fill(costs+l, costs+r+1, 0);

    vi il, ir;
    {
        vi tmp(100);
        for (int i : is) tmp[i] = vl;
        vi ret = Play(tmp);
        for (int i : is)
            if (ret[i] > vl)
                ir.push_back(i);
            else
                il.push_back(i);
    }

    int md = il.size();
    solve5_recursive(l, l+md-1, il, p);
    solve5_recursive(l+md, r, ir, p);
}

void solve5(int *P) {
    vector<int> is(100);
    iota(all(is), 0);
    solve5_recursive(1, 100, is, P);
}
