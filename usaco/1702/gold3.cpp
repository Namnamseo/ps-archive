#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back

int n;
int arr[100010];
int in[100010];
int out[100010];

int tree[100010];
void upd(int pos, int val){
	while(pos<=100000){
		tree[pos]+=val;
		pos+=(pos&(-pos));
	}
}

int s(int pos){
	int ret=0;
	while(pos) ret+=tree[pos], pos&=(pos-1);
	return ret;
}

int main()
{
	freopen("circlecross.in", "r", stdin);
    freopen("circlecross.out", "w", stdout);
    read(n);
    for(int i=1; i<=2*n; ++i){
		read(arr[i]);
		if(in[arr[i]]) out[arr[i]]=i;
		else in[arr[i]]=i;
    }
    ll ans=0;
    for(int i=1; i<=2*n; ++i){
		int x=arr[i];
		if(i==out[x]){
			upd(i, -1);
		} else {
			ans += s(out[x])-s(i);
			upd(out[x], 1);
		}
    }
    printf("%lld\n", ans);
    return 0;
}
