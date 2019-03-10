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
#define eb emplace_back
#define x first
#define y second

ll down;
int n;
ll a[100010];

int main()
{
	{int s, t; read(s, t, n); down = t-s;}
	for(int i=1; i<=n; ++i) read(a[i]), a[i] += a[i-1];
	ll mv = *min_element(a+1, a+n+1);
	if(a[n] >= 0 && mv > down){
		puts("-1");
		return 0;
	}
	ll week = 0;
	while(week * a[n] + mv > down) ++week;
	ll cur = a[n] * week;
	for(int i=1; i<=n; ++i){
		if(cur + a[i] <= down){
			printf("%lld\n", week * n + i);
			break;
		}
	}
	return 0;
}

