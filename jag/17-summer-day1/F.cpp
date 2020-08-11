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

int nxt[100010][26];
int prv[100010][26];
int n;
char s[100010];

char buf[100010];

int main()
{
	scanf("%s", s+1);
	n = strlen(s+1);
	for(int i=0; i<26; ++i) nxt[n+1][i]=-1, nxt[0][i]=-1;
	for(int i=n; 1<=i; --i){
		for(int j=0; j<26; ++j) nxt[i][j]=nxt[i+1][j];
		nxt[i][s[i]-'a'] = i;
	}
	for(int i=1; i<=n; ++i){
		for(int j=0; j<26; ++j) prv[i][j]=prv[i-1][j];
		prv[i][s[i]-'a'] = i;
	}
	int q; scanf("%d", &q);
	for(;q--;){
		scanf("%s", buf);
		int l = strlen(buf);
		int p = 0;
		for(int i=0; i<l; ++i){
			if(p != -1){
				p = nxt[p+1][buf[i]-'a'];
			}
		}
		if(p == -1){
			puts("-1"); continue;
		}
		int R = p;
		for(int i=l-2; 0<=i; --i){
			p = prv[p-1][buf[i]-'a'];
		}
		printf("%d %d\n", p, R);
	}
	return 0;
}

