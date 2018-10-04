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
int a[100010];
int p[100010][2];

int gc[100001];
int ans[100001];

int main()
{
	read(n);

	rrep(i, n){
		read(a[i]);
		rep(j, 2) p[i][j]=p[i-1][j];
		p[i][a[i-1]<=a[i]]++;
	}

	for(int mr=2; mr<=n; ++mr){
		for(int s=1; s<=n;){
			int my = (a[s] <= a[s+1]);

			int l=s, r=n+1;
			while(l+1 < r){
				int mid=(l+r)/2;
				if(p[mid][!my]-p[s][!my]){
					r = mid;
				} else {
					l = mid;
				}
			}

			if(l < min(s+mr-1, n)){
				ans[mr] += min(s+mr-1, n) - l;
				l = min(s+mr-1, n);
			}

			s = l+1;
			++gc[mr];
		}
	}

	int q; read(q);
	for(;q--;){
		int x; read(x);
		printf("%d %d\n", gc[x], ans[x]);
	}

	return 0;
}
