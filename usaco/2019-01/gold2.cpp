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
void cppio(){ ios_base::sync_with_stdio(0); cin.tie(0); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rrep(i,n) for(int i = 1; i <= (n); ++i)
#define sz(x) (int)(x).size()

const int M = 131072;
int t[M<<1];

void upd(int p,int v){ for(p+=M; p; p/=2) t[p]+=v; }
int rs(int l, int r){
	int ret=0;
	for(l+=M, r+=M; l<=r; l/=2, r/=2){
		if(l%2==1) ret+=t[l++];
		if(r%2==0) ret+=t[r--];
	}

	return ret;
}

int n;
int a[int(1e5) + 10];
int ans[int(1e5) + 10];

int main()
{
	cppio();
	cin >> n; rrep(i, n) cin >> a[i];
	int pt = 0;
	for(pt=n; 1<pt && a[pt-1]<a[pt]; pt--);
	cout << pt-1 << endl;

	rrep(i, n) t[M+i]=1;
	for(int i=M-1; 1<=i; --i) t[i]=t[i*2] + t[i*2+1];

	for(int i=pt-1; 1<=i; --i){
		ans[i] = rs(1, a[i]-1) + (pt-1-i);
		upd(a[i], -1);
	}
	for(int i=1; i<pt; ++i) cout << ans[i] << ' ';
	cout << endl;
	return 0;
}
