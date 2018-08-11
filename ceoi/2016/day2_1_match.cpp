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
char s[100010];
char ans[100010];

char stk[100010];
int top;

bool solve(int l, int r){
	if(l>r) return 1;
	if(((r+l)&1) == 0) return 0;
	
	if(s[l] == s[r]){ ans[l]='('; ans[r]=')'; return solve(l+1, r-1); }
	
	top = 0;
	for(int i=r; l<=i; --i){
		if(!top || stk[top-1] != s[i]) stk[top++] = s[i];
		else {
			if(!--top && l < i-1 && s[l] == s[i-1]){
				ans[l] = '('; ans[i-1] = ')';
				return solve(l+1, i-2) && solve(i, r);
			}
		}
	}
	return 0;
}
int main()
{
	scanf("%s", s+1);
	n = strlen(s+1);

	if(solve(1, n)){
		puts(ans + 1);
	} else puts("-1");

	return 0;
}
