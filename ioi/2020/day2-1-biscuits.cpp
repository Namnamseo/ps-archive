#include <vector>
#include <map>
#include <algorithm>
#include <cstdio>
using namespace std;
using ll=long long;
using pll=pair<ll, ll>;

map<ll, ll> memo[100];
vector<ll> a;
ll k;
ll x;

ll F(int i, ll carry)
{
	if (i >= k) {
		return carry / x;
	}

	{
		auto ir = memo[i].lower_bound(carry);
		auto il = ir;
		if (il != memo[i].end() && il->first == carry) return il->second;
		if (il != memo[i].begin() && ir != memo[i].end()) {
			--il;
			if (il->second == ir->second) return il->second;
		}
	}

	ll &ret = memo[i][carry];

	ret = !!((a[i] + carry) / x);

	ret += F(i+1, (a[i] + carry) / 2);
	if (a[i] + carry >= x)
		ret += F(i+1, (a[i] + carry - x) / 2);

	{
		auto ir = memo[i].upper_bound(carry);
		if (ir != memo[i].end() && ir->second == ret) {
			auto ir2 = ir;
			if (ir2 != memo[i].end()) {
				++ir2;
				if (ir2->second == ret)
					memo[i].erase(ir);
			}
		}

		auto il = memo[i].lower_bound(carry);
		if (il != memo[i].begin() && (--il)->second == ret) {
			auto il2 = il;
			if (il2 != memo[i].begin()) {
				--il2;
				if (il2->second == ret)
					memo[i].erase(il);
			}
		}
	}

	return ret;
}

ll count_tastiness(ll x, vector<ll> a)
{
	::k = a.size();
	for(int i=0; i<64; ++i) memo[i].clear();
	::a = a;
	::x = x;
	return F(0, 0) + 1;
}
