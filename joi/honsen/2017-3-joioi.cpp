#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back

int arr[4][2010][2010];
int N[4], M[4];

void rot(){
	for(int d=1; d<4; ++d){
		N[d] = M[d-1]; M[d] = N[d-1];
		for(int i=1; i<=M[d]; ++i) for(int j=1; j<=N[d]; ++j)
			arr[d][N[d]+1-j][i]=arr[d-1][i][j];
	}
}

bool can_cur(int d, int x){
	static int Mx=-1e9, mn=1e9;
	int n = N[d], m = M[d];
	if(Mx == int(-1e9)){
		for(int i=1; i<=n; ++i){
			for(int j=1; j<=m; ++j){
				Mx = max(Mx, arr[d][i][j]);
				mn = min(mn, arr[d][i][j]);
			}
		}
	}
	int ijou = Mx-x;
	int ika = x+mn;
	int last_max = m+1;
	for(int i=1; i<=n; ++i){
		int lb=0, rb=m+1;
		while(lb<m && arr[d][i][lb+1]>=ijou) ++lb;
		while(1<rb && arr[d][i][rb-1]<=ika) --rb;
		if(lb+1<rb) return 0;
		if(last_max < rb-1) return 0;
		last_max = min(last_max, lb);
	}
	return 1;
}

bool can(int x){
	bool ret=0;
	for(int i=0; i<4; ++i) if(can_cur(i, x)) return 1;
	return 0;
}

int main()
{
    read(N[0], M[0]);
    for(int i=1; i<=N[0]; ++i) for(int j=1; j<=M[0]; ++j) read(arr[0][i][j]);
    rot();

    int l=0, r=int(1e9)+10;
    while(l+1 < r){
		int mid=(l+r)/2;
		if(can(mid)) r=mid;
		else l=mid;
    }
    printf("%d\n", r);
    return 0;
}
