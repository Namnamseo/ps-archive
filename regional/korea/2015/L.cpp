#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(0);
    int tc; cin >> tc;
    for(;tc--;){
        int n, m; cin >> n >> m;
        ll x=0, y=0;
        for(int i=0; i<m; ++i){
            int b; cin >> b;
            x = 10 * x + b;
        }
        for(int i=0; i<m; ++i){
            int b; cin >> b;
            y = 10 * y + b;
        }
        vector<int> v(n);
        for(int& x:v) cin >> x;
        v.insert(v.end(), v.begin(), v.end());
        int ans = 0;
        for(int i=0; i<n; ++i){
            ll a=0;
            for(int j=0; j<m; ++j){
                a=10*a + v[i+j];
            }
            if(x<=a && a<=y) ++ans;
        }
        cout << ans << '\n';
    }
    return 0;
}

