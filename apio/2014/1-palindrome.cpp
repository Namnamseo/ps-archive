#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;
using ll=long long;
#define pb push_back
#define rep(i,n) for(int i=0;i<n;++i)
#define rrep(i,n) for(int i=1;i<=n;++i)

const int maxn = int(6e5) + 10;

char s[maxn];
int n;

int nxt[maxn][27];
int fail[maxn];
int cnt[maxn], dep[maxn], par[maxn];
int myv[maxn];

int rad[maxn], lng[maxn];
int nn, root;

int G(int v, int i) {
	if (!nxt[v][i]) {
		nxt[v][i] = ++nn;
		dep[nn] = dep[v] + 1;
		par[nn] = v;
	}
	return nxt[v][i];
}

int main() {
	scanf("%s", s);
	n = strlen(s);

	{ // inflate
		for (int i=n-1; 0<=i; --i) s[2*i+1] = s[i];
		for (int i=0; i<=n; ++i) s[2*i] = '{';
		n = 2*n+1;
	}

	root = ++nn; fail[root] = root;
	fail[myv[0] = G(root, s[0]-'a')] = root;
	for (int i=1; i<n; ++i) {
		int v = myv[i-1];
		while (v != root) {
			int r = dep[v], h = 2*(i-r)-i;
			if (h >= 0 && s[i] == s[h]) break;
			v = fail[v];
		}
		int h = 2*(i-dep[v])-i;
		char c = s[i]-'a';
		if (h >= 0 && s[h] == s[i]) {
			if (!nxt[v][c]) {
				int f = fail[v];
				for(; f!=root; f=fail[f]) {
					if (s[2*(i-dep[f])-i] == s[i]) {
						break;
					}
				}
				if (nxt[f][c]) f = G(f, c);
				fail[G(v, c)] = f;
			}
			myv[i] = v = G(v, c);
		} else {
			v = myv[i] = G(root, c);
			fail[v] = root;
		}
	}

	for(int i=0; i<n; ++i) ++cnt[myv[i]];
	for(int i=nn; 1<i; --i) cnt[fail[i]] += cnt[i];

	ll ans = 0;
	for (int i=1; i<=nn; ++i) ans = max(ans, (dep[i]-1)*1ll*cnt[i]);

	printf("%lld\n", ans);

	return 0;
}
