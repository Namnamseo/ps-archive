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
vector<int> e[1010];

int md[1010][1010];
const int inf = 1e9;

int main()
{
	read(n);
	rep(i, n) rep(j, n){
		int x; read(x); if(x) e[i].pb(j);
		md[i][j] = inf;
	}

	int mx = 0;

	rep(s, n){
		int *d = md[s];
		queue<int> q;
		for(int y:e[s]) d[y]=1, q.push(y);
		while(q.size()){
			int x=q.front(); q.pop();
			for(int y:e[x]) if(d[y]==inf){
				d[y]=d[x]+1;
				q.push(y);
			}
		}
		mx = max(mx, *max_element(d, d+n));
	}

	if(mx == inf) mx = 0;
	printf("%d\n", mx);
	return 0;
}
