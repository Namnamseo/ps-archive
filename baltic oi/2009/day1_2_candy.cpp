#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pp;
#define all(x) (x).begin(),(x).end()
#define pb push_back

int n;

vector<pp> candy;
int dp[100010], len;
int yy[100010];

int grp[100010];

int main()
{
    scanf("%d",&n);
    candy.resize(n);
    for(auto& x:candy){
        scanf("%d%d",&x.first,&x.second);
        x.second = -x.second;
        int a=x.first - x.second;
        int b=x.first + x.second;
        x = make_pair(a, -b);
    }
    sort(all(candy));
    for(auto& x:candy) x.second=-x.second;
    dp[grp[0]=len=1]=candy[0].second;
    for(int i=1; i<n; ++i){
        int y=candy[i].second;
        int p=upper_bound(dp+1, dp+len+1, y)-dp-1;
        if(dp[p] == y) grp[i]=grp[yy[p]];
        else if(p == len) dp[grp[i]=++len]=y, yy[len]=i;
        else grp[i]=grp[yy[p+1]], dp[p+1]=y, yy[p+1]=i;
    }
    printf("%d\n", len);
    for(int i=0; i<n; ++i){
        int a, b;
        tie(a, b) = candy[i];
        printf("%d %d %d\n", (a+b)/2, (a-b)/2, grp[i]);
    }
    return 0;
}
