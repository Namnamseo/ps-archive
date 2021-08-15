#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
const int inf = int(1e9);

struct Node {
	unsigned char nxtc[26][3];
	int term, fail;
	int nxt(int c) {
		return 
			((unsigned int)(nxtc[c][2])<<16) |
			((unsigned int)(nxtc[c][1])<<8) |
			((unsigned int)(nxtc[c][0]));
	}
	void reserve(int c, unsigned int v) {
		nxtc[c][0] = v; v >>= 8;
		nxtc[c][1] = v; v >>= 8;
		nxtc[c][2] = v;
	}
} nd[int(1e7)+10];
int root, nn=1;

int k, n;
int lens[int(1e4) + 10];
char s[int(1e5) + 10];

void Build() {
	static int q[int(1e7)+10], hd, tl;
	for (int i=0, v; i<26; ++i) if (v = nd[root].nxt(i), v) {
		nd[v].fail = root; q[tl++] = v;
	}

	while (hd<tl) {
		int x = q[hd++];
		for (int i=0, v; i<26; ++i) if (v = nd[x].nxt(i), v) {
			int f = nd[x].fail;
			while (f != root && !nd[f].nxt(i)) f = nd[f].fail;
			if (nd[f].nxt(i)) f = nd[f].nxt(i);
			nd[v].fail = f; q[tl++] = v;
		}
	}
}

int dp[int(1e5) + 10];
int duse[int(1e5) + 10];

int main() { cin.tie(0)->sync_with_stdio(0);
	cin >> k;
	for (int i=1; i<=k; ++i) {
		cin >> s;
		int l = strlen(s); lens[i] = l;
		reverse(s, s+l);
		int v = root;
		for (int j=0; j<l; ++j) {
			int c = s[j]-'a';
			if (!nd[v].nxt(c)) nd[v].reserve(c, ++nn);
			v = nd[v].nxt(c);
		}
		nd[v].term = i;
	}

	Build();
	cin >> s; n = strlen(s); reverse(s, s+n);

	int v = root;
	for (int i=0; i<n; ++i) {
		dp[i] = inf;
		int c = s[i]-'a';
		while (v != root && !nd[v].nxt(c)) v = nd[v].fail;
		if (nd[v].nxt(c)) v = nd[v].nxt(c);
		for (int t=v, j; t!=root; t=nd[t].fail) if (j=nd[t].term, j) {
			int bi = i-lens[j];
			if (bi == -1) {
				if (dp[i] > 1 || (dp[i] == 1 && duse[i] > j)) {
					dp[i] = 1;
					duse[i] = j;
				}
			} else {
				if (dp[bi]+1 < dp[i] || (dp[bi]+1 == dp[i] && duse[i] > j)) {
					dp[i] = dp[bi]+1;
					duse[i] = j;
				}
			}
		}
	}

	if (dp[n-1] == inf) {
		cout << "impossible\n";
		return 0;
	}

	cout << dp[n-1] << '\n';
	for (int i=n-1, j; i>=0;) {
		j = duse[i];
		cout << j << ' ';
		i -= lens[j];
	}
	cout << '\n';

	return 0;
}

