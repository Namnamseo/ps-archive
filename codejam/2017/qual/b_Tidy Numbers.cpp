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

ll n;
int d[20];
int v[20];

ll conv(){
    ll ret=0;
    for(int i=0; i<18; ++i) ret=ret*10+v[i];
    return ret;
}

void Work(){
    read(n);
    memset(d, 0, sizeof(d));
    memset(v, 0, sizeof(v));
    ll og_n = n;
    for(int i=17; 0<=i; --i){
        d[i]=n%10; n/=10;
    }
    for(int i=0; i<=17; ++i){
        for(int j=9; 0<=j; --j){
            for(int k=i; k<=17; ++k) v[k]=j;
            if(conv() <= og_n) break;
        }
    }
    printf("%lld\n", conv());
}

#define TYPE "l"

int main()
{
    freopen("in_" TYPE, "r", stdin);
    freopen("out_" TYPE, "w", stdout);
	int tc; read(tc);
	for(int i=1; i<=tc; ++i){
        printf("Case #%d: ", i);
        Work();
	}
    return 0;
}
