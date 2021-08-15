#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;
using ll=long long;

const int maxn = int(1e5) + 10;

int n, A;
struct Plant {
	int xys, w;
} d[maxn];
bool operator<(const Plant &a, const Plant &b) { return a.xys < b.xys; }

int main() {
	cin >> n >> A;
	for (int i=0; i<n; ++i) {
		int x, y, w; cin >> x >> y >> w;
		d[i] = {x*x + y*y, w};
	}
	sort(d, d+n);

	ll grad = 0; double yint = 0;
	double ans = 0;

	for (int i=0, j; i<n; i=j) { for (j=i; j<n && !(d[i]<d[j]); ++j);
		for (int t=i; t<j; ++t) {
			double r = sqrt(d[t].xys);
			grad += d[t].w;
			yint -= d[t].w * r;
		}

		double rmin = sqrt(d[i].xys);
		double rmax = (j == n ? (1e9) : sqrt(d[j].xys));

		double rpeak = double(grad) / (2*A);
		if (rmin <= rpeak && rpeak <= rmax) {
			ans = max(ans, grad * rpeak + yint - A * (rpeak * rpeak));
		}
	}

	cout.precision(20);
	cout << fixed << ans << '\n';

	return 0;
}
