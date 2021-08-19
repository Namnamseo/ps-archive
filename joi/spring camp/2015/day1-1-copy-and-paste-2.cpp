#include <cstdio>
void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args>
void read(T&a,Args&...b){ read(a); read(b...); }

int k;
int pos[210];

char S[200010];

int n;
int qs[200010];
int qe[200010];
int qp[200010];

inline int app_pos(int bp,int S,int E,int P){
	int nl=P, nr=P+E-S;
	if(nl <= bp && bp <= nr){
		return S+bp-nl;
	} else if(bp < nl){
		return bp;
	} else {
		return bp-(E-S+1);
	}
}

int main(){
	scanf("%d%*d%s%d", &k, S, &n);
	for(int i=1; i<=n; ++i) read(qs[i], qe[i], qp[i]), --qe[i];
	for(int i=0; i<k; ++i) pos[i]=i;

	for(int i=n; 1<=i; --i){
		for(int j=0; j<k; ++j){
			pos[j] = app_pos(pos[j], qs[i], qe[i], qp[i]);
		}
	}

	for(int j=0; j<k; ++j) putchar(S[pos[j]]);
	putchar(10);

	return 0;
}
