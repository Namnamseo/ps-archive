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

struct Tree {
	int T;
	ll tree[4096];
	void Init(int n){
		T=1; while(T<n+1) T<<=1;
	}
	ll get(int p){
		p += T;
		ll ret=0;
		while(p) ret+=tree[p], p>>=1;
		return ret;
	}
	void upd(int l, int r, int df){
		l+=T; r+=T;
		while(l<=r){
			if(l%2==1) tree[l++] += df;
			if(r%2==0) tree[r--] += df;
			l/=2; r/=2;
		}
	}
} dpt[3001];

int n;

ll ans;

ll get(int i, int j){
	if(!i || !j) return -(1ll<<60);
	return dpt[i+j].get(j);
}

int main(){
	read(n);
	for(int i=2; i<=2*n; ++i){
		dpt[i].Init(n);
	}
	for(int i=1; i<=n; ++i) for(int j=1; j<=n; ++j){
		int x; read(x);
		if(i == 1 && j == 1){
			dpt[2].upd(1, 1, x); ans += x;
			continue;
		}
		ll d = max(get(i-1, j), get(i, j-1)) + x;
		dpt[i+j].upd(j, j, d); ans += d;
	}
	printf("%lld\n", ans);
	for(int q=1; q<=n; ++q){
		char buf[5], cmd;
		int i, j;
		scanf("%s%d%d", buf, &i, &j); cmd = buf[0];
		
		int df;
		if(cmd == 'U') df=1;
		else df=-1;
		
		int row = i+j;
		int l=j, r=j;
		for(;l<=r;){
			int l0=l, r0=r;
			if(df == 1) dpt[row].upd(l, r, df);
			ans += (r-l+1) * df;
			if(row == 2*n){
				if(df == -1) dpt[row].upd(l, r, df);
				break;
			}
			if(row + 1 - l <= n && (l == 1 || dpt[row].get(l-1) < dpt[row].get(l))){
				
			} else ++l;
			if(r < n && (row - r == 1 || dpt[row].get(r) > dpt[row].get(r+1))){
				++r;
			}
			if(df == -1) dpt[row].upd(l0, r0, df);
			row += 1;
		}
		
		printf("%lld\n", ans);
	}
	return 0;
}

