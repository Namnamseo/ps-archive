#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
typedef long long ll;
typedef pair<ll,ll> pll;

char s[100010];
char* pt;

const int M = 998244353;

pll mult(pll a, pll b){
	if(a.y == -1){
		if(b.y == -1){
			return {a.x*b.x%M, -1};
		}
		return {a.x*b.x%M, a.x*b.y%M};
	} else if(b.y == -1){
		return {b.x*a.x%M, b.x*a.y%M};
	} else {
		return {(a.x*b.x+a.y*b.y)%M, -1};
	}
}

pll parse(){
	char c = *pt;
	if('0' <= c && c <= '9'){
		ll ret = 0;
		while('0' <= (*pt) && (*pt) <= '9'){
			ret = 10*ret + ((*pt)-'0');
			ret %= M;
			++pt;
		}
		return {ret, -1};
	}
	char type;
	++pt;
	auto a=parse(); type = *(pt++); auto b=parse(); ++pt;
	if(type == ','){
		return {a.x, b.x};
	} else {
		return mult(a, b);
	}
}

int main()
{
	cin >> s;
	pt = s;
	cout << parse().first;
	return 0;
}

