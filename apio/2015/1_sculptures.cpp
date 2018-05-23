#include <iostream>
using namespace std;
typedef long long ll;
ll data[5010], pref[5010], ans;
int n;
int A, B;

void in(){
    cin>>n>>A>>B;
    int i;
    for(i=1; i<=n; ++i) cin>>data[i], pref[i]=pref[i-1]+data[i];
}

int dp[5010];

int min(int a,int b){ return a>b?b:a; }

bool chk_no_lb(int k){
    ll mask = (~ans) & (~((1ll<<k)-1));
    int i,j;
    for(i=1; i<=n; ++i){
        dp[i]=1e9;
        for(j=0; j<i; ++j){
            if(((pref[i]-pref[j])&mask) == 0){
                dp[i]=min(dp[i],dp[j]+1);
            }
        }
    }
    return dp[n]<=B;
}

bool dp2[101][101];

bool chk_ks(int k){
    ll mask = (~ans) & (~((1ll<<k)-1));
    int i,j,t;
    for(i=0;i<=100;++i) for(j=0;j<=100;++j) dp2[i][j]=0;
    dp2[0][0]=1;
    for(i=1; i<=n; ++i){
        for(j=1; j<=B; ++j){
            for(t=0; t<i; ++t){
                if(dp2[t][j-1]){
                    if(((pref[i]-pref[t])&mask)==0){ // t is usable
                        dp2[i][j]=1;
                    }
                }
            }
        }
    }
    for(i=A; i<=B; ++i){
        if(dp2[n][i]) return 1;
    }
    return 0;
}

int main() {
    in();
    for(int i=40; 0<=i; --i){
        if( !(A==1?chk_no_lb(i):chk_ks(i)) ) ans|=(1LL<<i);
    }
    cout<<ans;
    return 0;
}
