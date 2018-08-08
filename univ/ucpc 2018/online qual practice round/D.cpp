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
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rrep(i,n) for(int i = 1; i <= (n); ++i)
#define sz(x) (int)(x).size()

char s[2000010];
char buf[1000010];
int pr[2000010];
int lp[2000010];

int tp[2100000][26];
int sp[2100000][21];
int r1, r2;
int v;

int r1s[51], r2s[51];

int draw(int a, int i){
	i -= 'a';
	if(tp[a][i]) return tp[a][i];
	tp[a][i] = ++v;
	sp[v][0] = a;
	rrep(j, 20) sp[v][j] = sp[sp[v][j-1]][j-1];
	return v;
}

void Work(int I){
	r1s[I] = r1 = ++v;
	r2s[I] = r2 = ++v;
	
	scanf("%s", buf);
	int l=1;
	s[0] = '$';
	for(int i=0; buf[i]; ++i){
		s[l++]=buf[i];
		s[l++]='$';
	}
	int c=0, mr=0;
	lp[0] = r2;
	rrep(i, l-1){
		int r = 0;
		int cp;
		if(s[i] == '$'){
			cp = r2;
		} else {
			cp = draw(r1, s[i]);
		}
		if(i <= c+mr){
			int b = 2*c - i;
			r = min(pr[b], b-(c-mr));
			cp = lp[b];
			int df = (pr[b] - r)/2;
			
			for(int q=20; q>=0; --q) if(1&(df>>q)) cp=sp[cp][q];
		}
		while(i-(r+1) >= 0 && i+(r+1)<l && s[i-(r+1)]==s[i+(r+1)]){
			char z = s[i-(r+1)];
			if(z != '$') cp = draw(cp, z);
			++r;
		}
		lp[i] = cp;
		pr[i] = r;
		if(i+r > c+mr) c=i, mr=r;
	}
}

int ans;
int n;
void dfs(int* a, int len){
	ans=max(ans, len);
	rep(i, 26){
		bool ok=1;
		rep(j, n) if(!tp[a[j]][i]){ ok=0; break; }
		if(ok){
			rep(j, n) a[j] = tp[a[j]][i];
			dfs(a, len+2);
			rep(j, n) a[j] = sp[a[j]][0];
		}
	}
}

int main()
{
	read(n);
	rep(i, n) Work(i);
	dfs(r1s, -1);
	dfs(r2s, 0);
	printf("%d\n", ans);
	return 0;
}
