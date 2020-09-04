#include <cstdio>
using ll=long long;
int main()
{
	int n;
	scanf("%d", &n);
	ll ans = 0, i;
	for(i=1; i*i<=n; ++i) ans += n/i;
	--i;
	ans -= i*i;
	ans *= 2;
	ans += i*i;
	ll d = 0;
	for(i=1; i*i<=n; ++i) if (n%i == 0) { ++d; if (i*i != n) ++d; }
	ans = ans + n - d;
	printf("%lld\n", ans);
	return 0;
}
