#include <iostream>
#include <algorithm>
using namespace std;
using pp=pair<int, int>;
const int maxn = int(1e5) + 10;
#define x first
#define y second

int n, m;
pp pic[maxn];
int fr[maxn];

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	cin >> n >> m;
	for (int i=1; i<=n; ++i) cin >> pic[i].x >> pic[i].y;
	for (int i=1; i<=m; ++i) cin >> fr[i];

	sort(pic+1, pic+n+1);
	sort(fr+1, fr+m+1);

	return 0;
}
