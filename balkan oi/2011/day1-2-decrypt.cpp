#include <iostream>
using namespace std;
#define rep(i, n) for (int i=0; i<n; ++i)

int rset[256];
int rval[256];
bool rchk[256];

int mout[8][256];
bool mchk[8][256];

int sv[7] = {1, 2, 4};
int kf[8];

bool achk[256];
int a[256];

int av[256], avn;

int main() {
	cin.tie(0)->sync_with_stdio(0);

	for (int i=3; i<7; ++i) sv[i] = sv[i-2] ^ sv[i-3];

	int kset[3], kval[3], kslb[3], kn = 0;
	int si = 0;

	int qc = 0;
	while (kn < 3) {
		int cs = sv[si]; ++si; if (si == 7) si = 0;

		int i;
		int om = 0;

		rep(j, kn) if (cs & kslb[j]) {
			cs ^= kset[j];
			om ^= kval[j];
		}

		avn = 0;
		for(i=0; i<256; ++i) if (!mchk[cs][i]) av[avn++] = i;
		if (avn) {
			i = av[rand()%avn];
		} else {
			i = 0;
		}

		cout << (i ^ om) << endl;
		++qc;

		int x; cin >> x;
		mchk[cs][i] = true;
		mout[cs][i] = x;

		if (!rchk[x]) {
			rchk[x] = true;
			rset[x] = cs;
			rval[x] = i;
			continue;
		}

		if (rset[x] == cs) continue;
		int sd = cs ^ rset[x];
		int sdlb = sd & (-sd);
		int vd = i ^ rval[x];

		kset[kn] = sd;
		kslb[kn] = sdlb;
		kval[kn] = vd;
		++kn;

		for (int j=1; j<=7; ++j) {
			rep(k, 256) if (mchk[j][k]) {
				int cj = j, ck = k, cm = mout[j][k];
				rep(t, kn) if (cj & (kslb[t])) {
					cj ^= kset[t];
					ck ^= kval[t];
				}
				mout[cj][ck] = cm;
				mchk[cj][ck] = true;

				rset[cm] = cj;
				rval[cm] = ck;
				rchk[cm] = true;
			}
		}
	}

	rep(i, 3) {
		int j; for(j=0; j<2; ++j) if (kslb[j] == (1<<i)) break;

		if (i != j) {
			swap(kset[i], kset[j]);
			swap(kval[i], kval[j]);
			swap(kslb[i], kslb[j]);
		}
	}

	rep(i, 2) {
		for(int j=i+1; j<3; ++j) if (kset[i] & (1<<j)) {
			kset[i] ^= kset[j];
			kval[i] ^= kval[j];
		}
	}

	for (int i=1; i<=7; ++i) {
		rep(j, 3) if (1&(i>>j)) kf[i] ^= kval[j];
	}

	for (int i=1; i<=7; ++i) rep(j, 256) if (mchk[i][j]) {
		int oj = j ^ kf[i];
		achk[oj] = true;
		a[oj] = mout[i][j];
	}

	int ai = 0;
	while (ai < 256) {
		if (achk[ai]) { ++ai; continue; }
		int cs = sv[si]; ++si; if (si == 7) si = 0;
		int om = kf[cs];
		cout << (ai ^ om) << endl;
		cin >> a[ai]; achk[ai] = true; ++ai;
	}

	cout << "SOLUTION" << endl;

	rep(i, 3) {
		cout << kval[i] << endl;
	}

	rep(i, 256) {
		cout << a[i] << endl;
	}

	cerr << qc << endl;

	return 0;
}
