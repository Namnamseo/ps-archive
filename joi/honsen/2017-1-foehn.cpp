#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back

int n, q, s, t;

ll alt[200010];

ll tree[200010];
ll S(int p){
	ll ret=0;
	while(p) ret+=tree[p], p&=(p-1);
	return ret;
}

void u(int p, ll v){ while(p<=200000) tree[p]+=v, p+=(p&(-p)); }

ll T=0;
void up(int p, int sg){
	if(p<1 || n<p) return;
	if(S(p)>S(p-1)) T-=sg*s*ll(S(p)-S(p-1));
	else T-=sg*t*ll(S(p)-S(p-1));
}

int main()
{
    read(n, q, s, t);
    read(alt[0]);
    for(int i=1; i<=n; ++i){
		read(alt[i]);
		if(alt[i-1]<alt[i]) T-=s*ll(alt[i]-alt[i-1]);
		else T-=t*ll(alt[i]-alt[i-1]);
		u(i, alt[i]-alt[i-1]);
    }
    for(int i=1; i<=q; ++i){
		int l, r;
		ll x;
		read(l, r, x);
		up(l, -1);
		up(r+1, -1);
		
		u(l, x);
		u(r+1, -x);
		
		up(l, 1);
		up(r+1, 1);
		printf("%lld\n", T);
    }
    return 0;
}
