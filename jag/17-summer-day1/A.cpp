#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
ll ans;
void take(ll len, ll cnt){
	if(n <= cnt){
		ans += n*len;
		cout << ans << endl;
		exit(0);
	}
	n -= cnt;
	ans += len*cnt;
}

int main()
{
	cin >> n;
	for(int i=0; i<26; ++i){
		take(1, 1);
		take(2, 1);
	}
	take(2, 26*26-26);
	ll t=26*26;
	for(int i=3;; ++i){
		take(i, t*=26);
	}
	return 0;
}

