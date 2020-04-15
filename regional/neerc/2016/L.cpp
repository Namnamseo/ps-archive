#include <bits/stdc++.h>
using namespace std;
using pp=pair<int,int>;
#define x first
#define y second
#define pb push_back
#define eb emplace_back
using ll=long long;

const int PN = 400, ST = 3000;

int p[PN], pn;
int pl[PN];

ll A[PN+1][3000];
ll B[PN+1][3000];
ll C[PN+1][3000];

ll L, R;
char buf[int(2e5)]; int bn;

int u[PN], un;
int cC;

int is;

void search(int i, int s){
	if(i == PN){
		if(s) return;
		bn += sprintf(buf+bn, "[");
		for(int j=0; j+1<un; ++j)
			bn += sprintf(buf+bn, "%d, ", u[j]);
		bn += sprintf(buf+bn, "%d], ", u[un-1]);
		if(bn > R){
			for(int j=L; j<=R; ++j) putchar(buf[j]);
			putchar(10);
			exit(0);
		}
		return;
	}

	ll v = 2*A[i][s] + (B[i][s] + A[i][s] * un) * 2 + (C[i][s] + A[i][s] * cC);
	if(v <= L && !bn){
		L -= v;
		R -= v;
		return;
	}

	if(s >= p[i]){
		u[un++] = p[i];
		cC += pl[i];
		search(i+1, s-p[i]);
		cC -= pl[i];
		--un;
	}
	search(i+1, s);
}

int main(){
	cin >> L >> R;
	--L; --R;

	for(int i=2; pn<PN; ++i){
		bool ok=1;
		for(int j=2; j*j<=i; ++j) if(i%j==0){ ok=0; break; }
		if(ok){
			p[pn++] = i;
		}
	}

	A[PN][0] = 1;
	for(int i=PN-1; 0<=i; --i){
		for(int t=p[i]; t; t/=10) ++pl[i];
		for(int s=0; s<ST; ++s){
			A[i][s] = A[i+1][s];
			B[i][s] = B[i+1][s];
			C[i][s] = C[i+1][s];
			if(s >= p[i]){
				A[i][s] += A[i+1][s-p[i]];
				B[i][s] += A[i+1][s-p[i]] + B[i+1][s-p[i]];
				C[i][s] += A[i+1][s-p[i]]*pl[i] + C[i+1][s-p[i]];
			}
		}
	}

	for(int i=1; i<ST; ++i) search(0, is=i);
	return 0;
}
