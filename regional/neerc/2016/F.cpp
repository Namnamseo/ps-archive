#include <bits/stdc++.h>
using namespace std;

char buf[1000010];
int S[1000010];

long double dp[1000010];
long double sm[1000010];
long double sp[1000010];

int main(){
	scanf("%s", buf);
	int l = strlen(buf);
	for(int i=1; i<=l; ++i){
		if(buf[l-i] == 'C'){
			S[i] = S[i-1];
			dp[i] = S[i] + sm[i-1] / i;
		} else {
			S[i] = S[i-1] + 1;
			dp[i] = (i+1)*0.5 - S[i] + sp[i-1] / i;
		}
		sm[i] = sm[i-1] + dp[i] - S[i];
		sp[i] = sp[i-1] + dp[i] + S[i];
	}
	printf("%.20Lf\n", dp[l]);
	return 0;
}

