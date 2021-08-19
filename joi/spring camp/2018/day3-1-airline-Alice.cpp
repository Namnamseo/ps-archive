#include <vector>
#include <utility>
using namespace std;
using pp=pair<int,int>;

void InitG(int, int);
void MakeG(int, int, int);

namespace ALICE {
vector<pp> e;

void Alice(int n, int m, int A[], int B[]) {
	const int
		bvo = n,
		X = bvo+10,
		Y = X+1;
	e.reserve(m);
	for (int i=0; i<m; ++i) e.emplace_back(A[i], B[i]);
	for (int i=0; i<n; ++i) {
		e.emplace_back(i, X);
		for (int j=0; j<10; ++j) if (1&(i>>j)) {
			e.emplace_back(i, bvo+j);
		}
	}
	for (int i=0; i<10; ++i) {
		e.emplace_back(bvo+i, X);
		e.emplace_back(bvo+i, Y);
	}

	//    -- 1 -- 2
	//   /
	//  0 -- 3 -- 4 -- 5
	//   \
	//    -- 6 -- 7 -- 8 -- 9

	e.emplace_back(bvo+0, bvo+1);
	e.emplace_back(bvo+1, bvo+2);

	e.emplace_back(bvo+0, bvo+3);
	e.emplace_back(bvo+3, bvo+4);
	e.emplace_back(bvo+4, bvo+5);

	e.emplace_back(bvo+0, bvo+6);
	e.emplace_back(bvo+6, bvo+7);
	e.emplace_back(bvo+7, bvo+8);
	e.emplace_back(bvo+8, bvo+9);

	InitG(Y+1, int(e.size()));
	for (int i=0; i<int(e.size()); ++i) {
		MakeG(i, e[i].first, e[i].second);
	}
}

}

void Alice(int n, int m, int A[], int B[]) { ALICE::Alice(n, m, A, B); }
