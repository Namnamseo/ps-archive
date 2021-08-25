#include <bits/stdc++.h>
using namespace std;

int a[20010];

int gcd(int a, int b){ return b?gcd(b, a%b):a; }
int lcm(int a, int b){
	return a/gcd(a, b)*b;
}

bool vis[20010];

int main(){
	int n;
	scanf("%d", &n);
	for(int i=1; i<=n; ++i) scanf("%d", a+i);
	int ans = 1;
	for(int i=1; i<=n; ++i) if(!vis[i]){
		int cc = 0;
		for(int p=i;;p=a[p]){
			if(vis[p]) break;
			vis[p]=1;
			++cc;
		}
		ans = lcm(ans, cc);
	}
	printf("%d\n", ans);
	return 0;
}
