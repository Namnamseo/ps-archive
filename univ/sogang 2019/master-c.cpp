#include <algorithm>
#include <iostream>
using namespace std;

int a[5010];

int n, c;

int main() {
	cin.tie(0)->sync_with_stdio(0);

	cin >> n >> c;
	for (int i=1; i<=n; ++i) cin >> a[i];
	sort(a+1, a+n+1);

	for (int i=1; i<=n; ++i) {
		int x = a[i];
		if (x == c) { cout << "1\n"; return 0; }
		int k = n;
		for (int j=i+1; j<=n; ++j) {
			int y = a[j];
			if (x+y == c) { cout << "1\n"; return 0; }
			while (j < k && x+y+a[k] > c) --k;
			if (j < k && x+y+a[k] == c) { cout << "1\n"; return 0; }
		}
	}

	cout << "0\n";
	return 0;
}
