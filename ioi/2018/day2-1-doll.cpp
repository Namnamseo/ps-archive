#include "doll.h"
#include <cassert>
#include <cstdio>
#include <algorithm>
using namespace std;
#define pb push_back

int nn;

const int maxn = int(4e5) + 10;
int x[maxn];
int y[maxn];
int c[maxn];

int f(int b, vector<int>& a)
{
	if (b == 0) return a[0];

	for(int i=0, j=0; i<(1<<b); ++i) {
		if (i<j) swap(a[i], a[j]);
		int t = (1<<(b-1));
		while (j&t) j^=t, t>>=1;
		j|=t;
	}
	int m = 1<<(b-1);
	int r = nn+1;
	assert(int(a.size()) == m*2);
	for(int i=1; i<m; ++i) x[nn+i]=-(nn+2*i), y[nn+i]=-(nn+2*i+1);
	for(int i=m, p=0; i<2*m; ++i) x[nn+i]=a[p++], y[nn+i]=a[p++];
	nn += 2*m-1;
	return -r;
}

void create_circuit(int M, vector<int> A) {
	int N = A.size();
	vector<int> bits;
	for(int i=0; i<30; ++i) if (1&(N>>i)) bits.pb(i);
	int mb = bits.back() + 1;

	vector<vector<int>> as(30);
	{ int pt = 0; for(int i=1; i<(1<<mb); ++i) {
		int j = (i&(-i));
		j = mb-1-__builtin_ctz(j);
		if (N&(1<<j)) {
			as[mb-1-j].pb(A[pt++]);
		}
	} }

	nn = mb;
	for(int i=0; i<mb; ++i) x[i+1] = -1, y[i+1] = -(i+2);
	y[mb] = 0;
	for(int b:bits) {
		x[mb-b] = f(b, as[mb-1-b]);
	}

	vector<int> C(M+1, -1);
	vector<int> X(x+1, x+nn+1);
	vector<int> Y(y+1, y+nn+1);

	answer(C, X, Y);
}
