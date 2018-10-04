#include <bits/stdc++.h>
using namespace std;

int n, q;

int x[2501], y[2501];

int main(){
	scanf("%d%d", &n ,&q);

	for(int i=0; i<n; ++i) scanf("%d%d", x+i, y+i);

	int qx, qy;
	int i;
	int md, tmp, dx, dy;
	int md1, md2, mdc;
	for(;q--;){
		scanf("%d%d", &qx, &qy);
		md = int(2e9)+1;
		mdc = 0;
		for(i=0; i<n; ++i){
			dx = qx-x[i];
			dy = qy-y[i];
			tmp = (dx*dx+dy*dy);
			if(md > tmp){
				md = tmp;
				mdc = 1;
				md1 = i;
			} else if(md == tmp){
				++mdc;
				md2 = i;
			}
		}
		if(mdc == 1){
			printf("REGION %d\n", md1+1);
		} else if(mdc == 2){
			if(md1>md2) swap(md1, md2);
			printf("LINE %d %d\n", md1+1, md2+1);
		} else {
			puts("POINT");
		}
	}
	return 0;
}
