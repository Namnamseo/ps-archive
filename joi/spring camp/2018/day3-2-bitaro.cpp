#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
using pp=pair<int, int>;
const int maxn = int(1e5) + 10;
const int maxm = int(2e5) + 10;
const int B = 200;

int n, m, q;
int ren[maxm];
int rev[maxm];
int sre[maxn];
int rn;

vector<pp> prec[maxn];

int seen[maxn];
int nt;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m >> q;
	for (int i=1; i<=m; ++i) {
		int s, e; cin >> s >> e;
		ren[++rn] = sre[e]; sre[e] = rn; rev[rn] = s;
	}

	for (int i=1; i<=n; ++i) {
		prec[i].push_back({0, i});
		for (int ri=sre[i], j; j=rev[ri], ri; ri=ren[ri]) {
			static vector<pp> tmp; tmp.clear();
			vector<pp> &v1 = prec[i], &v2 = prec[j];
			int i1 = 0, i2 = 0;
			int s1 = int(v1.size()), s2 = int(v2.size());
			++nt;
			while (int(tmp.size()) < B && (i1 < s1 || i2 < s2)) {
				if (i1 < s1 && (i2 == s2 || v1[i1].first >= v2[i2].first+1)) {
					if (seen[v1[i1].second] != nt) {
						tmp.push_back(v1[i1]);
						seen[tmp.back().second] = nt;
					}
					++i1;
				} else {
					if (seen[v2[i2].second] != nt) {
						tmp.push_back(v2[i2]);
						seen[tmp.back().second] = nt;
						++tmp.back().first;
					}
					++i2;
				}
			}
			swap(v1, tmp);
		}
	}

	for (;q--;) {
		int dest, igs; cin >> dest >> igs;
		static int ign[maxn];
		++nt;
		for (int i=0; i<igs; ++i) {
			cin >> ign[i];
			seen[ign[i]] = nt;
		}

		if (igs < B) {
			bool found = 0;
			for (auto [dist, from]:prec[dest]) {
				if (seen[from] != nt) {
					cout << dist << '\n';
					found = 1;
					break;
				}
			}
			if (!found) {
				cout << "-1\n";
			}
			continue;
		}

		static int qd[maxn];
		fill(qd+1, qd+dest+1, -1);
		int ans = -1;
		qd[dest] = 0;
		for (int i=dest; 1<=i; --i) if (qd[i] != -1) {
			if (seen[i] != nt) {
				ans = max(ans, qd[i]);
			}
			for (int ri=sre[i], j; j=rev[ri], ri; ri=ren[ri]) {
				qd[j] = max(qd[j], qd[i]+1);
			}
		}

		cout << ans << '\n';
	}

	return 0;
}
