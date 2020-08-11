#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);

	int t;
	cin >> t;
	for(;t--;){
		int n;
		cin >> n;
		vector<int> v(n);
		for(int& x : v) cin >> x;

		int cMax = v[n-1];
		typedef long long ll;
		ll ans = 0;
		for(int i=n-2; 0<=i; --i){
			if(cMax < v[i]) cMax = v[i];
			else ans += cMax - v[i];
		}
		cout << ans << '\n';
	}
	return 0;
}

