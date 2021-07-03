#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;
using ll=long long;
void cppio(){ ios_base::sync_with_stdio(0); cin.tie(0); }

const int maxn = int(1e5) + 10;

int n, m;

int p[maxn];
int po[maxn];
int par[maxn];

int root(int x) {
	return (par[x] == x)?x:(par[x]=root(par[x]));
}

struct E {
	int w, a, b;
} e[maxn];

int main()
{
	cppio();

	cin >> n >> m;
	for (int i=1; i<=n; ++i) { cin >> p[i]; po[p[i]] = i; }
	for (int i=1; i<=m; ++i) {
		auto &f = e[i];
		cin >> f.a >> f.b >> f.w;
	}

	{ bool done = 1;
	for (int i=1; i<=n; ++i) if (p[i] != i) { done = 0; break; }
	if (done) { cout << "-1\n"; return 0; } }

	sort(e+1, e+m+1, [&](const E& a, const E& b) {
		return a.w < b.w;
	});

	iota(par+1, par+n+1, 1);
	int nci = 1;
	for (int i=m; 1<=i; --i) {
		auto &f = e[i];
		int a = f.a, b = f.b;
		par[root(a)] = root(b);

		while (nci <= n) {
			if (root(nci) == root(po[nci])) {
				++nci;
			} else break;
		}

		if (nci > n) {
			cout << f.w << '\n';
			return 0;
		}
	}

	return 0;
}

