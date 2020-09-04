#include <iostream>
#include <tuple>
#include <algorithm>
#include <vector>
using namespace std;
using ll=long long;
#define rep(i, n) for(int i=0; i<n; ++i)
#define rrep(i, n) for(int i=1; i<=n; ++i)
#define pb push_back

int n;
const int maxn = int(1e6) + 10;

int tmp[3][maxn];
int *A = tmp[0], *B = tmp[1], *M = tmp[2];

int trunc(int *(&v), int s, int m, int c0)
{
	int i0=0, n0=c0, i1=c0, n1=s;
	for(int i=c0; i<s; ++i) v[i] &= m;
	int pt = 0;
	while(i0<n0 || i1<n1) {
		if (i0<n0 && (i1==n1 || v[i0]<v[i1])) M[pt++] = v[i0++];
		else  M[pt++] = v[i1++];
		if (pt >= 2 && M[pt-2] == M[pt-1]) --pt;
	}
	swap(v, M);
	return pt;
}

char *I;
int ri() {
	int ret=0;
	while((*I)<'0' || *I>'9')++I;
	while((*I)>='0' && *I<='9') ret=ret*10+(*I-48), ++I;
	return ret;
}

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
int main()
{
	{using Z=struct stat *;fstat(0,(Z)A);I=(char*)mmap(0,Z(A)->st_size,1,2,0,0);}
	n = ri();
	rep(i, n) A[i] = ri();
	rep(i, n) B[i] = ri();

	[]{
		static ll cnt[2][30];
		rep(i, n) rep(j, 30) if (1&(A[i]>>j)) ++cnt[0][j];
		rep(i, n) rep(j, 30) if (1&(B[i]>>j)) ++cnt[1][j];
		ll ans = 0;
		const ll mod = 1999;
		rep(i, 30) (ans += ((1ll<<i)%mod) * cnt[0][i]%mod * cnt[1][i]%mod) %= mod;
		cout << ans << ' ';
	}();

	int ans = 0;
	sort(A, A+n);
	sort(B, B+n);
	int sA = n, sB = n;
	int tt[4], ttn;

	for(int d=30; 0<=d; --d) {
		int c0A = 0; while (!(1&(A[c0A]>>d)) && c0A<sA) ++c0A;
		int c0B = 0; while (!(1&(B[c0B]>>d)) && c0B<sB) ++c0B;

		ans += [&]{
			for (int iA : {0, c0A-1, c0A, sA-1}) if (iA >= 0 && iA < sA) {
				for (int iB : {0, c0B-1, c0B, sB-1}) if (iB >= 0 && iB < sB) {
					if (!(1&((A[iA] + B[iB])>>d))) return 0;
				}
			}
			return 1<<d;
		}();
		if (!d) break;

		int m = (1<<d)-1;
		sA = trunc(A, sA, m, c0A);
		sB = trunc(B, sB, m, c0B);
	}

	cout << ans << '\n';

	return 0;
}
