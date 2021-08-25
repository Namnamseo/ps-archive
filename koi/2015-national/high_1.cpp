#include <bits/stdc++.h>
using namespace std;

int n, q;

int f(int a, int b){
	if(a == b) return 1;
	if(a > b){
		return b+n >= 2*(a-1);
	} else if(a < b){
		return a+n > 2*(b-1);
	}
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> q;
	for(;q--;){
		int a, b;
		cin >> a >> b;
		cout << f(a, b) << '\n';
	}
	return 0;
}
