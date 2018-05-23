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
#define x first
#define y second

void Work(){
    string s; int k;
    cin >> s >> k;
    int n = s.length();
    int ans = 0;
    for(int i=0; i<n; ++i){
        if(i+k-1 >= n) break;
        if(s[i] == '-'){
            for(int j=0; j<k; ++j) s[i+j]^='-'^'+';
            ++ans;
        }
    }
    if(s != string(n, '+')) cout << "IMPOSSIBLE" << endl;
    else cout << ans << endl;
}

int main()
{
    freopen("in_l", "r", stdin);
    freopen("out_l", "w", stdout);
	int tc; read(tc);
	for(int i=1; i<=tc; ++i){
        cout << "Case #" << i << ": ";
        Work();
	}
    return 0;
}
