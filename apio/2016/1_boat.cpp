#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define M (int(1e9)+7)
using namespace std;
typedef pair<int,int> pp;
pp data[510];
vector<int> pt;
int length[1010];
int n;

void read(int& x){ scanf("%d",&x); }
template<typename T1, typename... T2>
void read(T1& x,T2&... args){ read(x); read(args...); }

int dp[510][1010];
int pref[510][1010];
int level[1010];

typedef long long ll;
typedef pair<ll,ll> pli;

pli ext_gcd(int a,int b){
    if(a%b == 0) return {0,1};
    pli tmp=ext_gcd(b,a%b);
    ll x=tmp.second, y=(tmp.first - (a/b)*1LL*tmp.second);
    if(x <= -b){
        ll t=((-x+b-1) / b);
        x += t*b; y -= t*a;
    }
    if(y <= -a){
        ll t=((-y+a-1) / a);
        y += t*a; x -= t*b;
    }
    return {x,y};
}

int mod_inv(int x){
    return (M+ext_gcd(x, M).first)%M;
}

int modinv_table[510];

void build_modinv(){
    modinv_table[1]=1;
    for(int i=2; i<=500; ++i) modinv_table[i]=mod_inv(i);
}

int combi(int a,int b){
    if(a<b) return 0;
    ll ret=1;
    for(;b>=1;){
        ret *= a; ret %= M;
        ret *= modinv_table[b]; ret %= M;
        --a; --b;
    }
    return ret;
}

int main(){
    build_modinv();
{
    read(n);
    for(int i=1;i<=n;++i){
        int a,b; read(a,b); data[i]={a,b};
        pt.pb(a);
        pt.pb(b+1);
    }
}
    pt.pb(0);
    sort(all(pt));
    pt.erase(unique(all(pt)), pt.end());
    dp[0][0]=1; pref[0][0]=1;
    for(int i=1; i<pt.size(); ++i) {
        pref[0][i]  = 1;
        length[i-1] = pt[i]-pt[i-1];
    }
{
    for(int i=1; i<=n; ++i){
        int l=lower_bound(all(pt), data[i].first)-pt.begin();
        int r=upper_bound(all(pt), data[i].second)-pt.begin()-1;
        for(int j=l; j<=r; ++j){
            int came = pref[i-1][j-1];
            int ind=0;
            dp[i][j]=(dp[i][j]+length[j]*((ll)came)%M)%M;
            ll lastcombi = length[j]-1;
            for(int k=i+1; k<=n; ++k){
                if(data[k].first<=pt[j] && pt[j+1]<=data[k].second+1){
                    ++ind;
                    lastcombi *= length[j]+ind-1;     lastcombi %= M;
                    lastcombi *= modinv_table[ind+1]; lastcombi %= M;
                    dp[k][j] = (dp[k][j] + lastcombi*1LL*came%M)%M;
                }
            }
        }
        pref[i][0]=pref[i-1][0] + dp[i][0];
        for(int j=1; j<pt.size()-1; ++j){
            pref[i][j]=((ll)pref[i-1][j]+pref[i][j-1]-pref[i-1][j-1]+dp[i][j]+M)%M;
        }
    }
    printf("%d\n", (pref[n][pt.size()-2]+M-1)%M);
}
    return 0;
}
