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

int N;
char cmd[10010];

int n;
char s[20010];
int d[20010];

int Count(){
	int c = 0, r = 0;
	int ret = 1;
	for(int i=1; i<n; ++i){
		int R = 0;
		if(i <= c+r) R=min(d[2*c-i], c+r-i);
		while(0<=i-R-1 && i+R+1<n && s[i-R-1] == s[i+R+1]) ++R;
		d[i]=R;
		if(c+r < i+R) c=i, r=R;
		if(i&1){
			ret += (R+1)/2;
		} else {
			ret += R/2+1;
		}
	}
	return ret;
}

int main()
{
	scanf("%d%s", &N, cmd);
	for(int i=0; i<N; ++i){
		char t = cmd[i];
		if(t == '-'){
			n -= 2;
		} else {
			if(n) s[n++]='$';
			s[n++] = t;
		}
		printf("%d ", Count());
	}
	return 0;
}
