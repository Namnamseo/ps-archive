#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, s, f;

ll ans;
const ll mod = int(1e9) + 7;

ll dp[2010][2010];

int main()
{
	cin >> n >> s >> f;
	dp[0][0] = 1;
	for(ll i=1; i<n; ++i){
		if(i == s || i == f){
			for(int j=0; j<i; ++j)
				(dp[i][j] += dp[i-1][j]) %= mod;
			for(int j=1; j<i; ++j)
				(dp[i][j-1] += dp[i-1][j] * j % mod) %= mod;
			continue;
		}
		for(ll j=0; j<i; ++j){
			if(j >= 2){
				(dp[i][j-1] += dp[i-1][j] * j % mod * (j-1) % mod) %= mod;
			}
			if(i >= s){
				(dp[i][j-1] += dp[i-1][j] * j % mod) %= mod;
			}
			if(i >= f){
				(dp[i][j-1] += dp[i-1][j] * j % mod) %= mod;
			}
			(dp[i][j+1] += dp[i-1][j]) %= mod;
		}
	}
	cout << dp[n-1][0] << endl;
	return 0;
}
