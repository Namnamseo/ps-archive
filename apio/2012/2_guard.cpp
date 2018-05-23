#include <bits/stdc++.h>
using namespace std;
void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define pb push_back
#define all(x) (x).begin(),(x).end()
typedef pair<int,int> pp;

int n, k, m;
vector<pp> gugan, chain;

int pref[100010];
int rpoint[100010];
int lpoint[100010];

int start_min[100010];

int inf = 2e9;

int dp[100010];
int sv[100010];
int nxt[100010];
int ss[100010];
bool single[100010];

int main()
{
    vector<pp> gugan_tmp;
    read(n, k, m);
    for(;m--;){
        int a, b, c;
        read(a, b, c);
        if(c == 0){
            ++pref[a];
            --pref[b+1];
        } else {
            gugan_tmp.pb(pp{a, b});
        }
    }
    
    int cnt=0;
    for(int i=1; i<=n; ++i){
        pref[i] += pref[i-1];
        cnt += !pref[i];
        if(pref[i]) rpoint[i]=rpoint[i-1];
        else rpoint[i]=i;
    }
    
    if(cnt == k){
        for(int i=1; i<=n; ++i) if(!pref[i]) printf("%d\n", i);
        return 0;
    }
    
    lpoint[n+1]=n+1;
    for(int i=n; 1<=i; --i){
        if(pref[i]) lpoint[i]=lpoint[i+1];
        else lpoint[i]=i;
    }
    
    for(auto tmp:gugan_tmp){
        int x, y; tie(x, y) = tmp;
        x=lpoint[x]; y=rpoint[y];
        gugan.pb(pp{x, y});
        if(x == y) single[x] = 1;
    }
    
    sort(all(gugan), [&](const pp& a, const pp& b){
         return (a.second == b.second) ? (a.first > b.first) : (a.second < b.second);
    });
    gugan.erase(unique(all(gugan)), gugan.end());
    
    gugan.pb(pp{inf, inf});
    int gn = gugan.size();
    
    for(int i=0; i<gn; ++i) sv[i]=max(i?sv[i-1]:0, gugan[i].first);
    
    for(int i=gn-2; 0<=i; --i){
        int y = lower_bound(sv, sv+gn, gugan[i].second+1) - sv;
        dp[i] = dp[y] + 1;
        nxt[i] = y;
    }
    
    for(int i=1; i<=n; ++i) ss[i]=-1;
    for(int i=0; i<gn-1; ++i){
        int l=gugan[i].first, r=gugan[i].second;
        if(ss[l] == -1) ss[l]=i;
        else if(r < gugan[ss[l]].second) ss[l]=i;
    }
    
    vector<int> ans;
    int cn = dp[0];
    for(int i=0; i<gn-1; i=nxt[i]){
        int l=gugan[i].first, r=gugan[i].second;
        if(single[r]){
            ans.pb(r);
            continue;
        }
        if(cn < k) continue;
        if(ss[r] == -1) continue;
        if(dp[i] < 1+dp[ss[r]]) ans.pb(r);
    }
    
    if(ans.empty()) puts("-1");
    else for(int x:ans) printf("%d\n", x);
    return 0;
}
