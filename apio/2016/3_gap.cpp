#include "gap.h"
#include <algorithm>
using namespace std;

typedef long long ll;

ll big=ll(1e18);

int n;

ll binwork(ll X, ll Y,int n){
	ll a,b;
	MinMax(X, Y, &a, &b);
	if(n==2) return b-a;
	ll ans=0;
	n-=2;
	while(true){
		ll c,d;
		MinMax(a+1, b-1, &c, &d);
		ans=max({ans, c-a, b-d});
		if(n==1){
			break;
		}
		if(n==2){
			ans=max(ans, d-c);
			break;
		}
		n-=2;
		a=c; b=d;
	}
	return ans;
}

ll work2(){
	ll x,y;
	MinMax(0,big,&x,&y);
	ll l=x+1, r=y-1;
	ll width = (r-l+1)/n;
	int i;
	ll li=l;
	ll lastp = x;
	ll ans=0;
	for(i=0; i<n; ++i){
		ll p=li, q=li+width-1;
		if( i < (r-l+1)-width*n ) ++q;
		li=q+1;
		ll ba, bb;
		MinMax(p, q, &ba, &bb);
		if(ba!=-1){
			ans=max(ans, ba-lastp);
			lastp=bb;
		}
	}
	ans=max(ans, y-lastp);
	return ans;
}

ll findGap(int T, int N)
{
	if(T == 1){
		return binwork(0, big, N);
	} else {
		if(N==2){
			ll a,b;
			MinMax(0, big, &a, &b);
			return b-a;
		}
		n=N;
		return work2();
	}
}
