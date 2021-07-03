#include <iostream>
#include <vector>
#include <bitset>
#include <string>
using namespace std;
using ll=long long;
void cppio(){ ios_base::sync_with_stdio(0); cin.tie(0); }

int k;

ll f(ll days, ll endspeed) {
	if (days < endspeed) {
		return days * (days+1) / 2;
	}

	ll ret = (endspeed-1) * endspeed / 2;
	days -= (endspeed - 1);

	ret += days * (endspeed-1);
	ll t = (days+1)/2;
	if (days % 2 == 0) {
		ret += t*t + t;
	} else {
		ret += t*t;
	}

	return ret;
}

int main()
{
	cppio();
	int n; cin >> k >> n;

for(;n--;) {
	int x; cin >> x;

	ll l = 0, r = int(1e9);
	while (l+1 < r) {
		ll m = (l+r)/2;
		ll v = f(m, x);
		if (v >= k) {
			r = m;
		} else {
			l = m;
		}
	}

	cout << r << '\n';
}

	return 0;
}

