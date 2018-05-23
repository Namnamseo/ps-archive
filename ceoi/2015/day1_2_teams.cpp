#include <cstdio>
#include <algorithm>
using namespace std;

const int M=1000007;
typedef long long ll;

int data[10010];

ll dp[10010];
int pM[10010];
ll pr[10010];
int Mv;
int n;

int main(){
	scanf("%d", &n);
	for(int i=1; i<=n; ++i){
		int x;
		scanf("%d", &x);

		if(Mv < x) Mv = x;
		data[i] = x;
	}

	int ans=1;
	for(int i=1; i<=n; ++i) pM[i] = max(pM[i-1], data[i]);
	for(int i=1; i<=n+1; ++i) dp[i]=1, pr[i]=pr[i-1]+dp[i];
	for(int i=n; 2<=i; --i){
		int x = data[i];
		ans += (x-1) * ll(dp[pM[i-1]]) % M;
		ans %= M;
		for(int j=1; j<=i; ++j){
			dp[j] = (dp[j]*j + dp[j+1])%M;
			pr[j] = (pr[j-1] + dp[j])%M;
		}
	}
	printf("%d\n", ans);
	return 0;
}


