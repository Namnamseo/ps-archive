#include "Bruno.h"
#include <iostream>
using namespace std;

vector<int> Bruno(int k, vector<int> value)
{
	int val_map[3][3];
	int type_map[3][3];
	for (int i=0; i<9; ++i) val_map[i/3][i%3] = value[i];
	int ar, ac;
	[&]{ for (ar=0; ar<3; ++ar) for (ac=0; ac<3; ++ac) {
		if (val_map[ar][ac] == 12) return;
	} }();
	for (int dr=0; dr<3; ++dr) for (int dc=0; dc<3; ++dc) {
		type_map[(ar+dr)%3][(ac+dc)%3] = (
			((dr+2)%3)*3 + (dc+2)%3
		);
	}

	int hi;
	for (int r=0; r<3; ++r) for (int c=0; c<3; ++c) if (type_map[r][c] == 7) {
		hi = val_map[r][c];
	}

	for (int r=0; r<3; ++r) for (int c=0; c<3; ++c) if (type_map[r][c] != 8) {
		int &v = val_map[r][c];
		if (v >= hi) ++v;
		if (v >= 9) ++v;
	}

	vector<int> ret;
	for (int i=0; i<7; ++i) {
		int tr, tc;
		[&]{ for (tr=0; tr<3; ++tr) for (tc=0; tc<3; ++tc) {
			if (type_map[tr][tc] == i) return;
		} }();

		int v = val_map[tr][tc];
		int ans;

		if (v == 10) ans = 3;
		else if (v == 11) ans = 1;
		else if (v == 12) ans = 2;
		else if (v == 13) ans = 0;
		else {
			int dr = (v-1)/3 - 1;
			int dc = (v-1)%3 - 1;

			int ir = tr+dr, ic = tc+dc;
			if (ir == 1 && ic == 1) {
				ans = 4;
			} else if (ir <= 0) {
				ans = 3;
			} else if (ir >= 2) {
				ans = 2;
			} else if (ic <= 0) {
				ans = 1;
			} else if (ic >= 2) {
				ans = 0;
			}
		}

		ret.push_back(ans);
	}

	return ret;
}
