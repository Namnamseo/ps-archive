#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second

int n;
int wow[100010];

int wp[100010], wn;

int p[20][100010];
int d[100010];
int c[100010];
int l[100010];

const int M=131072;
pp t[M<<1];
pp rmax(int l, int r){
	l+=M; r+=M;
	pp ret;
	while(l<=r){
		if(l%2==1) ret=max(ret, t[l++]);
		if(r%2==0) ret=max(ret, t[r--]); l/=2; r/=2;
	}
	return ret;
}
int a[100010];
int b[100010];
vector<int> e[100010];
int I[100010], O[100010];
void dfs(int x){ static int T=0; I[x]=++T; for(int y:e[x]) d[y]=d[x]+1, dfs(y); O[x]=T; }
int GC(int x){ return rmax(I[x], O[x]).y; }
void tupd(int i){
	int p=I[i]+M; static int TT=0; ++TT;
	while(p) t[p].x=TT, t[p].y=i, p/=2;
}

int q[100010], z;
int k[100010];
int Q[100010], N;
int F[100010];
ll WOW(){
	for(int i=0; i<z; ++i) Q[i]=q[i];
	sort(Q, Q+z); N=unique(Q, Q+z)-Q;
	for(int i=1; i<=N; ++i) F[i]=0;
	ll ret=0;
	for(int i=0; i<z; ++i){
		int p=lower_bound(Q, Q+N, q[i])-Q+1;
		int q=p-1;
		while(q) ret+=F[q]*1LL*k[i], q&=(q-1);
		while(p<=N) F[p]+=k[i], p+=(p&(-p));
	}
	return ret;
}

int main()
{
	read(n);
	for(int i=1; i<=n; ++i) read(wow[i]);
	for(int i=1; i<n; ++i){
		read(a[i], b[i]); e[a[i]].pb(b[i]); p[0][b[i]]=a[i];
	}
	for(int i=1; i<=16; ++i) for(int j=1; j<=n; ++j) p[i][j]=p[i-1][p[i-1][j]];
	dfs(1);
	tupd(1); l[1]=1;
	for(int i=1; i<n; ++i){
		z = 0;
		int A=a[i], B=b[i];
		for(int i=A;i;){
			int cc=GC(i);
			q[z]=wow[cc]; k[z]=d[i]-d[l[cc]]+1; ++z;
			int nx=l[cc];
			if(d[cc]>=d[i]+1){
				int df=d[cc]-(d[i]+1), dn=cc;
				for(int i=0; i<=16; ++i) if(1&(df>>i)) dn=p[i][dn];
				l[cc]=dn;
			}
			i=p[0][nx];
		}
		l[B]=1;
		tupd(B);
		printf("%lld\n", WOW());
	}
	return 0;
}
