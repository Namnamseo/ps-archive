#include <iostream>
#include <algorithm>
using namespace std;
using ll=long long;
void cppio(){ ios_base::sync_with_stdio(0); cin.tie(0); }

const int maxn = 1010;

int n, k;

int borg[maxn];
int b[maxn];

int main()
{
	cppio();

	cin >> n >> k;
	for (int i=1; i<=n; ++i) cin >> borg[i];

	int ans = 0;
	for (int v=1; v<=1000; ++v) {
		int bc = 0;
		for (int i=1; i<=n; ++i) {
			int t = borg[i];
			bc += t/v;
			b[i] = t%v;
		}
		if (bc < k/2) continue;
		bc -= k/2;
		int need = max(0, min(n, k/2 - bc));

		int cur = min(k/2, bc) * v;
		sort(b+1, b+n+1);
		for (int i=0; i<need; ++i)
			cur += b[n-i];

		ans = max(ans, cur);
	}

	cout << ans << '\n';

	return 0;
}


