#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second

int a[5010];
int df[5010];

int main()
{
	int n;
	read(n);
	int ans = 2;
	
	for(int i=1; i<=n; ++i) read(a[i]);
	for(int i=2; i<=n; ++i){
		if(a[i]>a[i-1]) df[i]=1;
		else if(a[i]<a[i-1]) df[i]=2;
	}
	for(int i=1; i<=n;){
		if(!df[i]){
			++i; continue;
		}
		int j=i;
		while(j+1<=n && df[j+1] && (((j+1-i)%2) == (df[i] != df[j+1]))) ++j;
		ans = max(ans, j-i+2);
		i = j+1;
	}
	printf("%d\n", ans);
	return 0;
}
