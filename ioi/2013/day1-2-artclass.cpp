#include <iostream>
using namespace std;

const double coeff[4][3] = {
	{0.1928, -0.1139,  0.1222},
	{0.0542,  0.1696, -0.0592},
	{0.1728, -0.0459,  0.0689},
	{0.2232, -0.1136,  0.0790}
};

int n, m;
double Read() {
	long long t = 0;
	int nm = n*m;
	for (int i=0; i<nm; ++i) {
		int x; cin >> x; t += x;
	}
	return double(t) / nm;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m;
	double p[3];
	for (int i=0; i<3; ++i) p[i] = Read();

	double ans[4];
	for (int i=0; i<4; ++i) {
		ans[i] = 0;
		for (int j=0; j<3; ++j) {
			ans[i] += coeff[i][j] * p[j];
		}
	}

	int mi = 0;
	for (int i=1; i<4; ++i) if (ans[mi] < ans[i]) mi = i;
	cout << (mi+1) << endl;

	return 0;
}
