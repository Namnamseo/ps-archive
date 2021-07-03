#include <iostream>
#include <algorithm>
using namespace std;
using ll=long long;
void cppio(){ ios_base::sync_with_stdio(0); cin.tie(0); }

ll n, k, m;

bool ok(ll x) {
	ll days = 0, left = n;
	while (days < k && left > 0) {
		if (left <= days * m) return true;
		ll t = left / x;
		if (t < m) {
			left -= (k-days) * m;
			days = 0;
			break;
		} else {
			++days;
			left -= t;
		}
	}

	return left <= 0;
}

int main()
{
	cppio();

	cin >> n >> k >> m;

	ll l = 0, r = 2*k;
	while (l+1 < r) {
		ll x = (l+r)/2;
		if (ok(x)) l = x;
		else r = x;
	}

	cout << l << '\n';

	return 0;
}

