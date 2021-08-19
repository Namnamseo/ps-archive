#include <algorithm>
#include <iostream>
using namespace std;
#define rep(i, n) for (int i=0; i<n; ++i)
#define rrep(i, n) for (int i=1; i<=n; ++i)

int n;
double p[14][3];
int sk[14];

double Work(int m) {
	if (!(m&1)) return 0.;
	static double _memo[1<<14]; double &ret = _memo[m];
	{ static bool _vis[1<<14]; if (_vis[m]) return ret; _vis[m] = true; }

	bool isBest = true;
	rrep(i, n-1) if ((1&(m>>i)) && (sk[i] > sk[0])) { isBest = 0; break; }

	rep(mymove, 3) {
		double pend = 0;
		double pwin = 0;
		for (int wm=(m&(m-1)); wm; wm=((wm-1)&m)) {
			int lm=(m^wm);
			int win, lose;
			if (wm & 1) { win = mymove; lose = (mymove+2)%3; }
			else { win = (mymove+1)%3; lose = mymove; }
			double pcur = 1;
			rrep(i, n-1) {
				if (1 & (wm>>i)) pcur *= p[i][win];
				else if (1 & (lm>>i)) pcur *= p[i][lose];
			}
			pend += pcur;
			if (wm & 1) {
				pwin += pcur * Work(wm);
			}
		}
		if (isBest) pwin += (1-pend);
		ret = max(ret, pwin);
	}

	return ret;
}

int main() {
	cin >> n >> sk[0];
	rrep(i, n-1) {
		cin >> sk[i];
		rep(j, 3) (cin >> p[i][j]), (p[i][j] /= 100);
	}

	double ans = Work((1<<n)-1);
	cout.precision(12);
	cout << fixed << ans << '\n';

	return 0;
}
