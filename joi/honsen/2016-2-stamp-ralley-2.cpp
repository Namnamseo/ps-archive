#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

char s[100010];
ll pj[100010];
ll po[100010];

ll si[100010];
ll so[100010];

int main(){
	int n;
	scanf("%d%s", &n, s+1);
	ll z = 0;
	for(int i=1; i<=n; ++i){
		pj[i] = pj[i-1] + (s[i] == 'J');
		po[i] = po[i-1] + (s[i] == 'O' ? pj[i] : 0);
		if(s[i] == 'I') z += po[i];
	}
	for(int i=n; 1<=i; --i){
		si[i] = si[i+1] + (s[i] == 'I');
		so[i] = so[i+1] + (s[i] == 'O' ? si[i] : 0);
	}
	ll ans = 0;
	for(int i=0; i<=n; ++i){
		ans = max(ans, so[i+1]);
		ans = max(ans, pj[i] * si[i+1]);
		ans = max(ans, po[i]);
	}
	printf("%lld\n", ans + z);
	return 0;
}