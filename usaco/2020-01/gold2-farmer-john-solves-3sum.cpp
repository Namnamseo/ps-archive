#include <iostream>
#include <vector>
using namespace std;
using ll=long long;
const int maxn = 5010;
const int V = int(1e6);

int n, q;
int a[maxn];

ll cnt[maxn][maxn];
vector<int> occur[2*V+10];

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	cin >> n >> q;
	for (int i=1; i<=n; ++i) {
		cin >> a[i];
		occur[a[i]+V].push_back(i);
	}

	for (int i=1; i<n; ++i) {
		for (int j=i+2; j<=n; ++j) {
			int vk = -(a[i]+a[j]);
			if (abs(vk) > V) continue;
			auto &v = occur[V+vk];
			cnt[i][j] += (lower_bound(v.begin(), v.end(), j) -
				lower_bound(v.begin(), v.end(), i+1));
		}
	}

	for (int i=n; 1<=i; --i) {
		for (int j=i; j<=n; ++j) {
			cnt[i][j] += cnt[i+1][j] + cnt[i][j-1] - cnt[i+1][j-1];
		}
	}

for(;q--;) {
	int l, r; cin >> l >> r;
	cout << cnt[l][r] << '\n';
}

	return 0;
}
