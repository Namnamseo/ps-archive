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

int n;
priority_queue<int> pq;

int main()
{
	read(n);
	ll gain=0;
	for(int i=1; i<=n; ++i){
		int c, g; read(c, g);
		gain += g;
		pq.push(-c-g);
	}
	while(pq.size()){
		int t=pq.top();
		if(gain + t < 0) break;
		gain += t;
		pq.pop();
	}
	printf("%d\n", int(n-pq.size()));
	return 0;
}

