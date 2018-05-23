#include <iostream>
#define p1 p[head-2]
#define p2 p[head-3]
#define q1 q[head-2]
#define q2 q[head-3]
#define cp p[head-1]
#define cq q[head-1]
using namespace std;
typedef long long ll;

ll a,b,c;
ll data[1000010];
ll sum[1000010];
ll dp[1000010];
int n,i;

ll p[1000010];
ll q[1000010];
int head=1, tail=0;

ll calc(int pos,ll x){ return p[pos]*x+q[pos]; }

ll max(ll a,ll b){ return a>b?a:b; }

int main()
{
    cin.sync_with_stdio(false);
    cin>>n;
    cin>>a>>b>>c;
    for(i=1;i<=n;++i) {
        cin>>data[i];
        sum[i]=data[i]+sum[i-1];
    }
    for(i=1;i<=n;++i){
        while(tail+1<head && calc(tail,sum[i])<=calc(tail+1,sum[i])) ++tail;
        dp[i]=a*sum[i]*sum[i]+max(0,calc(tail,sum[i]));
        p[head]=-2*a*sum[i];
        q[head]=c+dp[i]+a*sum[i]*sum[i];
        ++head;
        while(tail<=head-3 && (q2-q1)*(cp-p1)>=(q1-cq)*(p1-p2)){
            p[head-2]=p[head-1]; q[head-2]=q[head-1]; --head;
        }
    }
    cout<<dp[n]+b*sum[n]+c;
    return 0;
}

