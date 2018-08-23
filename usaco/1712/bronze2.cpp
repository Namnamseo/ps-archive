#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
void read(pp& x){ scanf("%d%d",&x.first, &x.second); }
void read(pll& x){ scanf("%lld%lld",&x.first, &x.second); }
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

int n;
int ans[110];
int ai[110];

int shu[110], tmp[110];

int main()
{
	read(n);
	rrep(i, n) read(shu[i]), ai[i]=i;
	rrep(_, 3){
		rrep(i, n) tmp[shu[i]]=ai[i];
		rrep(i, n) ai[i]=tmp[i];
	}
	rrep(i, n){
		int x; read(x); ans[ai[i]]=x;
	}
	rrep(i ,n) printf("%d ", ans[i]);
	return 0;
}

