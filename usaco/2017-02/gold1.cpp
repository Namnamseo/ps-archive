#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back

int n, t;

int arr[110][110];

typedef tuple<int,int,int> t3;

int dist[110][110];
priority_queue<t3> pq;

void upd(int x, int y, int d){
	if(x<1 || y<1 || x>n || y>n) return;
	d+=arr[x][y];
	if(dist[x][y]>d){
		dist[x][y]=d;
		pq.push(t3{-d,x,y});
	}
}

const int inf=1e9;

int main()
{
	freopen("visitfj.in", "r", stdin);
	freopen("visitfj.out", "w", stdout);
    read(n, t);
    for(int i=1; i<=n; ++i) for(int j=1; j<=n; ++j) read(arr[i][j]);
    for(int i=1; i<=n; ++i) for(int j=1; j<=n; ++j){
		dist[i][j]=inf;
    }
    dist[1][1]=0; pq.push(t3{0, 1, 1});
    while(pq.size()){
		int d, x, y; tie(d, x, y) = pq.top(); pq.pop();
		if(dist[x][y] != -d) continue;
		for(int i=-3; i<=3; ++i) for(int j=-3; j<=3; ++j)
			if(abs(i)+abs(j)==1 || abs(i)+abs(j)==3)
				upd(x+i, y+j, -d+3*t);
    }
    int ans=inf;
    for(int i=1; i<=n; ++i)
	for(int j=1; j<=n; ++j){
		if(n-i+n-j < 3)
			ans = min(ans, dist[i][j] + t*(n-i+n-j));
	}
	printf("%d\n", ans);
    return 0;
}
