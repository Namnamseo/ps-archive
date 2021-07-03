#include <iostream>
#include <vector>
#include <string>
using namespace std;
void cppio(){ ios_base::sync_with_stdio(0); cin.tie(0); }

int main()
{
	cppio();
	int n, k; cin >> n >> k;

	vector<string> v(n); for (auto &s:v) cin >> s;

	int cl = 0;
	for (auto &s:v) {
		int l = s.length();
		if (cl + l > k) {
			cout << '\n';
			cl = 0;
		}
		if (cl) cout << ' ';
		cl += l;
		cout << s;
	}

	cout << '\n';

	return 0;
}
