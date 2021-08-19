#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)((v).size()))
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define coord_comp(v) sort(all(v)), v.erase(unique(all(v)), v.end())
#define v_index(v, x) (lower_bound(all(v),x)-(v).begin())
typedef pair<int,int> pp;
typedef long long ll;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ cin>>x; }
template<typename T1,typename T2>
void read(pair<T1,T2>& p){ read(p.first); read(p.second); }
template<typename T,typename... Args>
void read(T&a,Args&...b){ read(a); read(b...); }

const int max_n = (1<<21)+5;

char data[max_n];

string t;

int n;

int js[max_n];
int os[max_n];
int is[max_n];

int main(){
	read(n); n=(1<<(2*n));
	cin >> t;
	for(int i=1; i<=n; ++i) data[i] = data[n+i] = t[i-1];

	for(int i=1; i<=2*n; ++i){
		if(data[i] == 'J') ++js[i];
		else if(data[i] == 'O') ++os[i];
		else ++is[i];
		js[i] += js[i-1];
		os[i] += os[i-1];
		is[i] += is[i-1];
	}

	int ans=2e9;

	for(int i=1; i<=n; ++i){
		int ind = i;
		int match = 0;
		for(int j=n/4; j>=1; j/=4){
			match += js[ind+j-1]-js[ind-1]; ind += j;
			match += os[ind+j-1]-os[ind-1]; ind += j;
			match += is[ind+j-1]-is[ind-1]; ind += j;
		}
		ans = min(ans, ind-i-match);
	}

	printf("%d\n", ans);

	return 0;
}
