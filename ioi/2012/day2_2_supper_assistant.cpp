#include "assistant.h"
#define rep(i, N) for(int i=0; i<(N); ++i)

static bool isin[100010];
static int q[100010];

void Assist(unsigned char *A, int N, int K, int R) {
	int hd = 0, tl = 0;

	rep(i, K) {
		isin[i] = true;
		if (A[i] == 1) {
			q[hd++] = i;
		}
	}

	rep(i, N) {
		int req = GetRequest();
		if (!isin[req]) {
			isin[q[tl]] = false;
			PutBack(q[tl]);
			++tl;
		}

		if (A[K+i] == 1) {
			q[hd++] = req;
		}

		isin[req] = true;
	}
}
