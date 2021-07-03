#include <iostream>
using namespace std;
using ll=long long;
using pp=pair<int, int>;
const int maxn = int(1e5) + 10;
const int maxv = int(1e6);

int n;
int a[maxn];
int ac[maxv+10];
int occ[maxv+10];

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin >> n;
	for (int i=1; i<=n; ++i) cin >> a[i];
	for (int i=1; i<=n; ++i) ++ac[a[i]];
	for (int i=1; i<=maxv; ++i) ac[i] += ac[i-1];

	long long ans = 0;
	for (int x=1; x<=maxv; ++x) {
		int odc = 0;
		for (int i=1; i<=(maxv/x); ++i) {
			occ[i] = ac[min(maxv+1, x*(i+1))-1] - ac[max(0,x*i-1)];
			odc += (occ[i]%2);
		}
		for (int i=1; i<=(maxv/x); ++i) {
			if ((i == 1 && occ[i]%2 == 1 && odc == 1) ||
			    (i>1 && occ[i]%2 == 1 && occ[i-1]%2 == 1 && odc == 2)) {
			    ans += occ[i];
			}
		}
	}

	cout << ans << '\n';

	return 0;
}
