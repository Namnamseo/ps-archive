#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll dp[3010][3010];

const ll mod = 1'000'000'007;

ll f(ll w, ll h){
    if(!w || !h) return 1;
    if(w<0 || h<0) return 0;
    if(dp[w][h]) return dp[w][h];
    ll ret = 0;
    ret += f(w, h-1);
    (ret += w * 4 * f(w-1, h-1) % mod) %= mod;
    (ret += w*(w-1)/2 % mod * f(w-2, h-1) % mod) %= mod;
    (ret += w * (h-1) % mod * f(w-1, h-2) % mod) %= mod;
    return dp[w][h]=ret;
}

int main()
{
    int n, m; cin >> n >> m;
    cout << (f(n, m) + mod - 1) % mod << endl;
    return 0;
}
