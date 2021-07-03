#include <iostream>
#include <cstring>
using namespace std;
using ll=long long;

ll dp[50][2][2][2];
int dx[50];
int dy[50];
int dd[50];

int main()
{
	cin.tie(0)->sync_with_stdio(0);
int tc; cin >> tc; for(;tc--;) {
	ll d, x, y; cin >> d >> x >> y;
	{
		ll td = d, tx = x, ty = y;
		for (int i=0; i<40; ++i) {
			dx[i] = tx%3; tx /= 3;
			dy[i] = ty%3; ty /= 3;
			dd[i] = td%3; td /= 3;
		}
	}

	memset(dp, 0, sizeof(dp));
	dp[0][0][0][0] = 1;
	for (int i=0; i<40; ++i) {
		for (int state=0; state<8; ++state) {
			int cx = !!(state&4);
			int cy = !!(state&2);
			int od = !!(state&1);
			for (int cd=0; cd<3; ++cd) {
				if ((dx[i]+cx+cd)%3%2 != (dy[i]+cy+cd)%3%2) continue;
				dp[i+1]
					[(cx+dx[i]+cd)/3]
					[(cy+dy[i]+cd)/3]
					[(od && dd[i]==cd) || (dd[i]<cd)]
					+= dp[i][cx][cy][od];
			}
		}
	}

	cout << dp[40][0][0][0] << '\n';
}

	return 0;
}
