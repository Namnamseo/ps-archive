#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back

int n;
int a[1010], b[1010];
int dp[1010][1010];

int main()
{
    freopen("nocross.in", "r", stdin);
    freopen("nocross.out", "w", stdout);
    read(n);
    for(int i=1; i<=n; ++i) read(a[i]);
    for(int i=1; i<=n; ++i) read(b[i]);
    for(int i=1; i<=n; ++i) for(int j=1; j<=n; ++j){
		dp[i][j]=max(dp[i-1][j], dp[i][j-1]);
		if(abs(a[i]-b[j])<=4) dp[i][j]=max(dp[i][j], dp[i-1][j-1]+1);
    }
    printf("%d\n", dp[n][n]);
    return 0;
}
