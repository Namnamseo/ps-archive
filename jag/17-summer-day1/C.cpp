#include <bits/stdc++.h>
using namespace std;
typedef complex<double> cd;
const double pi = acos(-1);

int n, m;
int a[100010];
int b[100010];

const int M = 262144;
cd A[M];
cd B[M];
cd C[M];
cd D[M];

double dp_orig[100010];
double dp[100010];

cd buf[M];
void fft_nonrec(cd* in, cd* out, int N, bool inv=0){
	int n=0;
	while((1<<n) != N) ++n;
	for(int i=0; i<N; ++i) out[i]=in[i];
	
	for(int depth=n-1; 0<=depth; --depth){
		int ser = (1<<depth);
		int sz = (1<<(n-depth));
		cd omega = polar(1., 2*pi/sz*(inv?-1:1));
		for(int down=0; down<ser; ++down){
			for(int up=0; up<sz; ++up){
				buf[up] = out[(up << depth)| down];
			}
			for(int up=0; up<sz/2; ++up){
				cd a=buf[up*2], b=buf[up*2+1];
				out[(up << depth) | down] = a + pow(omega, up)*b;
				out[((up << depth)|down) + N/2] = a - pow(omega, up)*b;
			}
		}
	}
	
	if(inv) for(int i=0; i<N; ++i) out[i] /= N;
}

int main()
{
	scanf("%d%d", &n, &m);
	for(int i=1; i<=n; ++i) scanf("%d", a+i), C[a[i]-1] += 1.;
	for(int i=m; i>=1; --i) scanf("%d", b+i);
	
	for(int i=2; i<=m; ++i){
		dp_orig[i] = 1 + dp_orig[i]/n;
		if(b[i] >= 0){
			dp[i] = dp_orig[max(0, i-b[i])];
		} else {
			dp[i] = dp_orig[i] - b[i];
		}
		A[i] = dp[i];
		int last_bit = i&-i;
		fft_nonrec(A+i-last_bit+1, B, last_bit*2);
		fft_nonrec(C, D, last_bit*2);
		for(int j=0; j<last_bit*2; ++j){
			B[j] *= D[j];
		}
		fft_nonrec(B, D, last_bit*2, 1);
		for(int j=0; j<last_bit; ++j){
			dp_orig[i+j+1] += D[last_bit-1+j].real();
		}
	}
	
	printf("%.20f\n", dp_orig[m]);
	return 0;
}

