#include <iostream>
#include <vector>
#include <bitset>
#include <string>
using namespace std;
void cppio(){ ios_base::sync_with_stdio(0); cin.tie(0); }

int main()
{
	cppio();
	int n; cin >> n;

	vector<int> b(n), a(n+1);
	vector<int> ans(n+1, n+1);
	for (int i=1; i<n; ++i) cin >> b[i];

	bitset<1010> ex;
	for (int i=1; i<=n; ++i) {
		a[1] = i;
		for (int j=2; j<=n; ++j) {
			a[j] = b[j-1] - a[j-1];
		}

		ex.reset();
		bool ok = 1, win = 0;
		for (int j=1; j<=n; ++j) {
			if (a[j] < 1 || a[j] > n || ex[a[j]]) {
				ok = 0; break;
			}
			ex.set(a[j]);
			if (!win && ans[j] < a[j]) {
				ok = 0; break;
			}
			if (a[j] < ans[j]) win = 1;
		}
		if (!ok) continue;
		if (win) {
			copy(a.begin()+1, a.end(), ans.begin()+1);
		}
	}

	for (int i=1; i<=n; ++i) {
		cout << ans[i] << " \n"[i == n];
	}

	return 0;
}
