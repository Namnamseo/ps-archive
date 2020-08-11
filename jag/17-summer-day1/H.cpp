#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll A, B;

bool chk(ll c){
	ll t = A+B+2*c;
	if(t%3) return 0;
	t /= 3;
	ll x = A + c - t;
	ll y = B + c - t;
	if(!(0<=x && 0<=y && x+y <= c)) return 0;
	return max({x, y, c-x-y}) <= (c+1)/2;
}

int main()
{
	cin >> A >> B;
	ll l=0, r=ll(1e10);
	while(l+1 < r){
		ll mid = (l+r)/2;
		bool c = 0;
		for(int i=0; i<3; ++i){
			if(chk(mid+i)){
				c=1; break;
			}
		}
		if(c) r=mid;
		else l=mid;
	}
	while(!chk(l)) ++l;
	cout << l << endl;
	return 0;
}

