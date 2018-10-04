#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

priority_queue<int> pq;
int n, k;
int data[300001];

int main(){
	scanf("%d%d", &n, &k);
	for(int i=1; i<=n; ++i) scanf("%d", data+i);
	for(int i=1; i<n; ++i){
		pq.push(data[i+1]-data[i]);
	}

	typedef long long ll;
	ll ans = data[n] - data[1];
	for(;--k;){
		ans -= pq.top();
		pq.pop();
	}

	printf("%lld\n", ans);
	return 0;
}

