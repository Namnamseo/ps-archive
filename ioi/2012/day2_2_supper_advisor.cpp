#include <set>
#include <algorithm>
#include "advisor.h"
using namespace std;
using pp=pair<int, int>;

#define rep(i, N) for(int i=0; i<(N); ++i)

static int nut[100010];
static int lp[100010];
static int first[100010];
static bool isin[100010];

static bool weak[100010];
static bool weak0[100010];

void ComputeAdvice(int *C, int N, int K, int M) {
	set<pp> s;

	rep(i, N) lp[i] = -1, isin[i] = false;
	rep(i, K) first[i] = N;
	rep(i, N) {
		int c = C[i];
		if (lp[c] != -1) {
			nut[lp[c]] = i;
		}
		if (c < K && first[c] == N) first[c] = i;
		lp[c] = i;
		nut[i] = N;
		weak[i] = false;
	}

	rep(i, K) {
		s.emplace(first[i], -1-i);
		isin[i] = true;
	}

	rep(i, N) {
		int c = C[i];
		if (isin[c]) {
			s.erase(s.lower_bound(pp(i, -1)));
		} else {
			set<pp>::iterator it = --s.end();
			if (it->second < 0) {
				int t = (-(it->second)) - 1;
				isin[t] = false;
				weak0[t] = true;
			} else {
				isin[C[it->second]] = false;
				weak[it->second] = true;
			}
			s.erase(it);
		}
		s.emplace(nut[i], i);
		isin[c] = true;
	}

	rep(i, K) WriteAdvice(weak0[i]);
	rep(i, N) WriteAdvice(weak[i]);
}
