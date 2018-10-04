#include <bits/stdc++.h>
using namespace std;
using ll=long long;

ll a, b, c, d;

int gcd(int a, int b){ return b?gcd(b, a%b):a; }

int main(){
	cin>>a>>b>>c>>d;

	ll ans=0;

	for(int mo=1; mo<=1000; ++mo){
		for(int ja=1; ja<=1000; ++ja){
			if(!(mo+ja < 1000 && gcd(mo, ja) == 1)) continue;
			ll mn = max((c+mo-1)/mo, (a+ja-1)/ja);
			ll mx = min(d/mo, b/ja);
			ans += max(mx-mn+1, 0ll);
		}
	}

	cout << ans;
	return 0;
}
