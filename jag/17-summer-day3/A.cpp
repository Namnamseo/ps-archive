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

int main()
{
	string s; cin >> s;
	int n = s.length();
	int ans = 0;
	for(int i=0; i<n; ++i){
		for(int j=i+1; j<n; ++j){
			string cut = s.substr(i, j-i+1);
			int l = cut.length();
			if(cut.find("*") == -1) continue;
			if(cut[0] != '(') continue;
			if(cut[l-1] != ')') continue;
			bool daijoubu = 1;
			int lev = 0;
			for(int k=1; k<l-1; ++k){
				if(cut[k] == '*') continue;
				if(cut[k] == '(') ++lev; else --lev;
				if(lev < 0) daijoubu = 0;
			}
			ans += daijoubu && !lev;
		}
	}
	printf("%d\n", ans);
	return 0;
}

