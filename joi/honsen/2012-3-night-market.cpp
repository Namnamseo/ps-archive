#include <bits/stdc++.h>
using namespace std;

int n;
int T, S;

int dp[3010];

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> T >> S;
	for(;n--;){
		int earn, b;
		cin >> earn >> b;
		for(int i=T-b; 0<=i; --i){
			if(i < S && S < i+b) continue;
			dp[i+b] = max(dp[i+b], dp[i] + earn);
		}
		for(int i=1; i<=T; ++i) dp[i] = max(dp[i], dp[i-1]);
	}

	cout << dp[T] << endl;
	return 0;
}
