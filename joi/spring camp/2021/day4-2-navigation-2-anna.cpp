#include "Anna.h"
#include <utility>
using namespace std;
using pii=pair<int,int>;

namespace {
pii pos[7];

// [     10      ]
//      1 2 3 
// 11 | 4 5 6 | 13
//      7 8 9
// [     12     ]
//
int opinion(int r, int c, int target)
{
	int dr = pos[target].first - r;
	int dc = pos[target].second - c;
	if (dr >= 2) return 12;
	if (dc >= 2) return 13;
	if (dr <= -2) return 10;
	if (dc <= -2) return 11;
	return (dr+1)*3 + (dc+1) + 1;
}

int ancr, ancc, off;
int get_type(int r, int c) { return (r+3-ancr)%3 * 3 + (c+3-ancc)%3; }
void find_anchor()
{
	for (ancr=0; ancr<3; ++ancr) for (ancc=0; ancc<3; ++ancc) {
		bool ok = 1;
		for (int i=0; i<7; ++i) {
			auto [r, c] = pos[i];
			int nine_type = get_type(r-1, c-1);
			if (nine_type == i) {
				ok = 0; break;
			}
		}
		if (ok) return;
	}
}
bool is_anchor(int i, int j) { return i%3 == ancr && j%3 == ancc; }

int raw[110][110];
bool is_used[20];

}

void Anna(int n, int k, vector<int> r, vector<int> c)
{
	for (int i=0; i<k; ++i) pos[i] = {r[i], c[i]};
	find_anchor();

	for (int i=0; i<n; ++i) {
		for (int j=0; j<n; ++j) {
			int type = get_type(i, j);
			if (type < 7) {
				raw[i][j] = opinion(i, j, type);
			} else if (type == 7) {
				raw[i][j] = 14;
			} else {
				raw[i][j] = 14;
			}
		}
	}

	for (int i=1; i<=14; ++i) is_used[i] = false;
	for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) {
		is_used[raw[i][j]] = true;
	}

	if (is_used[9]) throw "oh no";
	int hi = -1;
	for (int i=1; i<9; ++i) if (!is_used[i]) { hi = i; break; }

	for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) {
		int ans;
		switch(get_type(i, j)) {
		case 8: ans = 12; break;
		case 7: ans = hi; break;
		default:
			int v = raw[i][j];
			if (v >= 9) ans = v-2;
			else if (v >= hi) ans = v-1;
			else ans = v;
		}
		SetFlag(i, j, ans);
	}
}
