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
int r1, r2, r3, r4;
int f1, f2, f3, f4;

map<string,pp> m;
char nbuf[12];

int main()
{
	read(r1, r2, r3, r4);
	read(f1, f2, f3, f4);
	
	int n; read(n);
	for(int t=1; t<=n; ++t){
		int cmd;
		scanf("%d%s", &cmd, nbuf);
		if(cmd == 1){
			pp& hist = m[nbuf];
			hist.x = t;
			++hist.y;
			continue;
		}
		
		auto it = m.find(nbuf);
		if(it == m.end()){
			puts("None");
			continue;
		}
		int r, f; tie(r, f) = it->second;
		r = t - r;
		
		if(r <= r1){
			if(f <= f1) puts("New Customer");
			else if(f <= f3) puts("Potential Loyalist");
			else if(f <= f4) puts("Loyal Customer");
			else puts("Champion");
		} else if(r <= r2){
			if(f <= f1) puts("Promising");
			else if(f <= f3) puts("Potential Loyalist");
			else puts("Loyal Customer");
		} else if(r <= r3){
			if(f <= f2) puts("About to Sleep");
			else if(f <= f3) puts("Need Attention");
			else puts("Loyal Customer");
		} else if(r <= r4){
			if(f <= f1) puts("Lost");
			else if(f <= f2) puts("Hibernating");
			else puts("About to Leave");
		} else {
			if(f <= f2) puts("Lost");
			else if(f <= f4) puts("About to Leave");
			else puts("Can't Lose Them");
		}
	}
	return 0;
}
