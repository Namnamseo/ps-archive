#include <bits/stdc++.h>
using namespace std;

int N, wid;
int h, m;

using ll = long long;

ll w[5010];
ll wx[5010];
ll wy[5010];

bitset<10001> dead[5001];
int L[5010], R[5010];

void col(int tm){ cout << "yes\n" << tm << endl; exit(0); }
void strict_in(ll a, ll b, ll c, int tm){ if(b<=a || c<=b) col(tm); }

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> N >> wid >> h >> m;
	for(int i=h; i>=1; --i){
		w[i] = w[i+1] + 2*N;
		wx[i] = wx[i+1] + N*1ll*N*wid;
		wy[i] = wx[i];
		L[i] = 1; R[i] = N;
	}

	for(int tm=1; tm<=m; ++tm){
		int lev, kth;
		cin >> lev >> kth;
		dead[lev][kth] = 1;

		for(int i=lev; 1<=i; --i){
			w[i] -= 2;
			if(lev%2 == 1){
				wx[i] -= (2*kth - 1) * wid;
				wy[i] -= N*wid;
			} else {
				wx[i] -= N*wid;
				wy[i] -= (2*kth - 1) * wid;
			}

			if(i == h) continue;

			while(L[i]<=N && dead[i][L[i]]) ++L[i];
			while(R[i]>=1 && dead[i][R[i]]) --R[i];
			if(L[i] > R[i]) col(tm);

			ll xm, xM, ym, yM;
			if(i%2 == 1){
				ym = 0; yM = N*wid;
				xm = (L[i]-1)*wid; xM = (R[i]) * wid;
			} else {
				xm = 0; xM = N*wid;
				ym = (L[i]-1)*wid; yM = (R[i]) * wid;
			}

			strict_in(xm*w[i+1], wx[i+1], xM*w[i+1], tm);
			strict_in(ym*w[i+1], wy[i+1], yM*w[i+1], tm);
		}
	}
	cout << "no" << endl;
	return 0;
}

