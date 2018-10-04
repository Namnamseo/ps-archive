#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
void read(pp& x){ scanf("%d%d",&x.first, &x.second); }
void read(pll& x){ scanf("%lld%lld",&x.first, &x.second); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rrep(i,n) for(int i = 1; i <= (n); ++i)
#define sz(x) (int)(x).size()

int a, b;
pp tg;

map<pp,int> d;

queue<pp> q;

int main()
{
	read(a, b, tg.x, tg.y);
	d[pp(0, 0)]=0;
	q.emplace(0, 0);
	while(q.size()){
		int x,y; tie(x,y) = q.front();
		int md = d[q.front()]; q.pop();

		auto relax = [&](int a, int b){
			pp key(a, b);
			auto it = d.find(key);
			if(it == d.end()){
				d[key] = md+1;
				q.emplace(key);
			}
		};

		relax(0, y);
		relax(a, y);
		relax(x, 0);
		relax(x, b);
		int d1 = min(x, b-y);
		relax(x-d1, y+d1);
		int d2 = min(a-x, y);
		relax(x+d2, y-d2);
	}

	auto it = d.find(tg);
	if(it == d.end()) puts("-1");
	else printf("%d\n", it->y);
	return 0;
}
