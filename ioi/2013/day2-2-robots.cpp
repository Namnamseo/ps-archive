#include "robots.h"
#include <algorithm>
#include <functional>
#include <queue>
using namespace std;

int *x, *y;
int n,p,q;

typedef pair<int,int> pp;

pp da[1000010];

bool tester(int bae){
	int ind=0;

	priority_queue<int> pq;
	for(int i=0; i<p; ++i){
		int cur=x[i];
		while(ind<n && da[ind].first<cur){
			pq.push(da[ind].second);
			++ind;
		}
		for(int j=0; j<bae; ++j){
			if(pq.size()) pq.pop();
			else break;
		}
	}
	for(;ind<n;++ind) pq.push(da[ind].second);

	for(int i=q-1; i>=0; --i){
		for(int j=0; j<bae; ++j){
			if(pq.size() == 0) break;
			int t=pq.top();
			if(t<y[i]){
				pq.pop();
			} else break;
		}
	}

	return pq.size() == 0u;
}

int putaway(int A, int B, int T, int X[], int Y[], int W[], int S[]) {
	n=T;
	p=A; q=B;
	x=X; y=Y;
	sort(x, x+p);
	sort(y, y+q);
	for(int i=0; i<n; ++i) da[i]={W[i], S[i]};
	sort(da, da+n);

	int L=0, R=T;
	if(!tester(R)) return -1;
	while(L+1<R){
		int mid=(L+R)/2;
		if(tester(mid)) R=mid;
		else L=mid;
	}
	return R;
}
