#include <cstdio>

int n;

int d[262145];

bool dp[60][262145];
int  rb[60][262145];

template<typename T> inline T max(T a, T b){ return a>b?a:b; }
template<typename T> inline T min(T a, T b){ return a<b?a:b; }

int main()
{
    scanf("%d",&n);
    int i,j;
    int ans=0;
    typedef long long ll;
    ll sum=0;
    for(i=0;i<n;++i) {
        scanf("%d",d+i);
        --d[i];
        dp[d[i]][i]=true;
        rb[d[i]][i]=i;
        ans=max(ans, d[i]);
        sum += (1LL<<d[i]);
    }
    for(j=1;(1LL<<j)<=sum;++j){
        for(i=0;i<n;++i){
            if(dp[j-1][i]){
                if(rb[j-1][i] != n-1 && dp[j-1][rb[j-1][i]+1]){
                    dp[j][i]=true;
                    ans=max(ans, j);
                    rb[j][i]=rb[j-1][rb[j-1][i]+1];
                }
            }
        }
    }
    printf("%d\n",ans+1);
    return 0;
}