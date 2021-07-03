#include <iostream>
#include <algorithm>
#include <numeric>
#include <cstring>
#define rrep(i, n) for(int i=1; i<=n; ++i)
#define rep(i, n) for(int i=0; i<n; ++i)
using namespace std;
using ll=long long;
const int maxn = int(2e5) + 10;

int n, m;
char s[maxn];
int sp[maxn], ln[maxn];

int rnk[maxn], tmp[maxn], sa[maxn];
int g[maxn];

void in() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	int p = 0;
	rrep(i, n) {
		sp[i] = p;
		cin >> (s+p);
		ln[i] = strlen(s+p);
		fill(g+p, g+p+ln[i]+1, i);
		p += ln[i] + 1;
		s[p-1] = '$';
	}
	m = p;
}

int lcp[maxn];

int main() {
	in();
	iota(sa, sa+m, 0);
	rep(i, m) rnk[i] = s[i];
	sort(sa, sa+m, [&](const int& a, const int& b) { return rnk[a]<rnk[b]; });

	rnk[m] = -1;
	for(int sl=1; sl<m; sl*=2) {
		for(int i=0, j; i<m; i=j) {
			for(j=i+1; j<m && rnk[sa[i]]==rnk[sa[j]]; ++j);
			auto cmp = [&](const int& a, const int& b)->bool {
				return rnk[a+sl] < rnk[b+sl];
			};
			sort(sa+i, sa+j, cmp);
			tmp[sa[i]] = (i ? (tmp[sa[i-1]]+1) : 0);
			for(int k=i+1; k<j; ++k)
				tmp[sa[k]] = tmp[sa[k-1]] + cmp(sa[k-1], sa[k]);
		}
		copy(tmp, tmp+m, rnk);
	}

	for(int i=0, z=0; i<m; ++i) {
		if (!rnk[i]) continue;
		int j=sa[rnk[i]-1];
		while (i+z<m && j+z<m && s[i+z]==s[j+z]) ++z;
		lcp[rnk[i]]=z; if (z) --z;
	}

	static int lu[maxn], ld[maxn];
	for(int i=1; i<m; ++i)
		if (g[sa[i-1]] == g[sa[i]]) lu[i] = min(lu[i-1], lcp[i]);
		else lu[i] = lcp[i];
	for(int i=m-2; 0<=i; --i)
		if (g[sa[i+1]] == g[sa[i]]) ld[i] = min(ld[i+1], lcp[i+1]);
		else ld[i] = lcp[i+1];

	rrep(i, n) {
		ll ans = 0;
		rep(j, ln[i]) {
			int t = sp[i]+j;
			int mxl = max(lu[rnk[t]], ld[rnk[t]]);
			if (rnk[t]) {
				int b = sa[rnk[t]-1];
				if (g[b] == g[t]) {
					mxl = max(mxl, lcp[rnk[t]]);
				}
			}
			ans += max(0, (ln[i]-j)-mxl);
		}
		cout << ans << '\n';
	}

	return 0;
}
