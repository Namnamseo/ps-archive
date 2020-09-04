#include <iostream>
#include <queue>
using namespace std;
using ll=long long;
priority_queue<ll> pq;
ll ans;
int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(;n--;) { int a; cin >> a; ans += a; pq.push(-a); }
	for(;m--;) {
		ll a = pq.top(); pq.pop();
		ll b = pq.top(); pq.pop();
		pq.push(a+b);
		pq.push(a+b);
		ans -= (a+b);
	}
	printf("%lld\n", ans);
	return 0;
}
