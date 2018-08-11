#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int t = 2500;

int tbl[2501][2501];
int tblps[2501][2501];

int n;
int x[250010];
int y[250010];

ll k1[2510][2510];
ll k2[2510][2510];

int rect(int l, int r, int d, int u){
	if(l>r || d>u) return 0;
	return tblps[r][u] - tblps[l-1][u] - tblps[r][d-1] + tblps[l-1][d-1];
}

int xmin[t+10];
int ymax[t+10];

void do_k1(){
	xmin[0] = t + 1;
	for(int j=1; j<=t; ++j){
		xmin[j] = xmin[j-1];
		for(int i=1; i<xmin[j]; ++i) if(tbl[i][j]){ xmin[j] = i; break; }
	}
	ymax[t+1] = 0;
	for(int i=t; 1<=i; --i){
		ymax[i] = ymax[i+1];
		for(int j=t; ymax[i]<j; --j) if(tbl[i][j]){ ymax[i] = j; break; }
	}

	for(int i=1; i<=t; ++i){
		for(int j=t; 1<=j; --j){
			int nx = min(xmin[j-1], i), ny = max(ymax[i+1], j);
			k1[i][j] = rect(1, i, j, t) - tbl[i][j] + k1[nx][ny] + tbl[nx][ny];
		}
	}
}

int xmax[t+10];
int ymin[t+10];

void do_k2(){
	xmax[t+1] = 0;
	for(int j=t; j>=1; --j){
		xmax[j] = xmax[j+1];
		for(int i=t; i>xmax[j]; --i) if(tbl[i][j]){ xmax[j] = i; break; }
	}
	ymin[0] = t+1;
	for(int i=1; i<=t; ++i){
		ymin[i] = ymin[i-1];
		for(int j=1; j<ymin[i]; ++j) if(tbl[i][j]){ ymin[i] = j; break; }
	}

	for(int i=t; 1<=i; --i){
		for(int j=1; j<=t; ++j){
			int nx = max(xmax[j+1], i), ny = min(ymin[i-1], j);
			k2[i][j] = rect(i, t, 1, j) - tbl[i][j] + k2[nx][ny] + tbl[nx][ny];
		}
	}
}

int main(){
	scanf("%d", &n);
	for(int i=1; i<=n; ++i){
		scanf("%d%d", x+i, y+i);
		++tbl[x[i]][y[i]];
	}

	for(int i=1; i<=t; ++i) for(int j=1; j<=t; ++j) tblps[i][j] = tblps[i-1][j] + tblps[i][j-1] - tblps[i-1][j-1] + tbl[i][j];
	do_k1();
	do_k2();

	for(int i=1; i<=n; ++i){
		int x = ::x[i], y = ::y[i];
		ll ans = n-1 + k1[x][y] + k2[x][y];
		printf("%lld\n", ans);
	}

	return 0;
}
