#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int (*eh)[200];
int (*ev)[200];

const int inf = 2e9;
#define BS 10

// *** TREE
int tree[1024][200][200];

int r, c;

void merge_row(int dp1[][200], int dp2[][200], int out[][200]){
	int opt[c][c];

	// big diagonal.
	out[0][c-1] = inf;
	for(int i=0; i<c; ++i){
		if(out[0][c-1] > dp1[0][i] + dp2[i][c-1])
			out[0][c-1] = dp1[0][i] + dp2[i][c-1],
			opt[0][c-1] = i;
	}

	for(int diff=2-c; diff<=c-1; ++diff){
		for(int j=0; j<c; ++j){
			int i=j+diff;
			if(i<0 || i>=c) continue;
			int lb=0, rb=c-1;
			if(i != 0)  lb=opt[i-1][j];
			if(j+1 < c) rb=opt[i][j+1];
			out[i][j]=inf;
			for(int k=lb; k<=rb; ++k){
				if(out[i][j] > dp1[i][k]+dp2[k][j]){
					out[i][j] =dp1[i][k]+dp2[k][j];
					opt[i][j]=k;
				}
			}
		}
	}
}

void row_dp(int dp[][200],int rn){
	// pref
	int pa[c], pb[c];
	pa[0]=0; for(int i=1; i<c; ++i) pa[i]=pa[i-1]+eh[rn  ][i-1];
	pb[0]=0; for(int i=1; i<c; ++i) pb[i]=pb[i-1]+eh[rn+1][i-1];

	for(int sp=0; sp<c; ++sp){
		for(int j=0; j<c; ++j) dp[sp][j] = abs(pa[sp]-pa[j]) + ev[rn][j];
		for(int j=1, cm=dp[sp][0]; j<c; ++j){
			cm+=eh[rn+1][j-1];
			dp[sp][j]=cm=min(cm, dp[sp][j]);
		}
		for(int j=c-2,cm=dp[sp][c-1]; 0<=j; --j){
			cm+=eh[rn+1][j];
			dp[sp][j]=cm=min(cm, dp[sp][j]);
		}
	}
}

void tree_calc_dp(int pos,int row_l, int row_r){
	auto bef=tree[pos];
	row_dp(bef, row_l);
	for(int i=row_l+1; i <= row_r; ++i){
		int tmp[c][200], buf[c][200];

		row_dp(tmp, i);
		merge_row(bef, tmp, buf);

		memcpy(bef, buf, c*200*4);
	}
}

void tree_init(int pos,int myl,int myr){
	if(myr-myl < BS) tree_calc_dp(pos, myl, myr);
	else {
		int mid=((myl+myr)>>1);
		tree_init(pos*2, myl, mid);
		tree_init(pos*2+1, mid+1, myr);
		merge_row(tree[pos*2], tree[pos*2+1], tree[pos]);
	}
}
// *** TREE END

void update(int upd_row,int pos,int myl,int myr){
	if(myr<upd_row || upd_row < myl) return;
	if(myr-myl < BS)
		tree_calc_dp(pos, myl, myr);
	else {
		int mid=(myl+myr)/2;
		update(upd_row, pos*2, myl, mid);
		update(upd_row, pos*2+1, mid+1, myr);
		merge_row(tree[pos*2], tree[pos*2+1], tree[pos]);
	}
}

int getNode(int upd_row,int pos,int myl,int myr){
	if(myr<upd_row || upd_row < myl) return 0;
	if(myr-myl < BS) return pos;
	int mid=(myl+myr)/2;
	return getNode(upd_row, pos*2, myl, mid) + getNode(upd_row, pos*2+1, mid+1, myr);
}

extern "C" {
void changeH(int P, int Q, int W) {
	eh[P][Q] = W;
	update(P, 1, 0, r-2);
	if(P>=1 && getNode(P-1,1,0,r-2) != getNode(P,1,0,r-2)) update(P-1, 1, 0, r-2);
}

void changeV(int P, int Q, int W) {
	ev[P][Q] = W;
	update(P, 1, 0, r-2);
}

int escape(int V1, int V2) {
	return tree[1][V1][V2];
}

void init(int R, int C, int H[5000][200], int V[5000][200]) {
	r = R; c = C;
	eh = H; ev = V;
	tree_init(1, 0, r-2);
}
}
