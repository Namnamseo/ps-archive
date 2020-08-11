#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int n, k, m;
int a[int(1e6)+10];

ll work(ll p) {
	ll ret = 0;
	for(int i=1; i<=n; ++i) {
		ret += a[i]/p;
	}
	return ret;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

	cin >> n >> k >> m;

	for(int i=1; i<=n; ++i) {
		cin >> a[i];
		if (a[i] <= k) a[i] = 0;
		else if(a[i] < 2*k) a[i] -= k;
		else a[i] -= 2*k;
	}

	if (accumulate(a+1, a+n+1, 0LL) < m) {
		cout << "-1" << endl;
		return 0;
	}

	int l = 0, r = int(1e9) + 10;
	while(l+1 < r) {
		int mid = (l+r)/2;
		if(work(mid) >= m) {
			l = mid;
		} else {
			r = mid;
		}
	}

	cout << l << endl;
    return 0;
}
