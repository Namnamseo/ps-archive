#include <cstdio>
#include <set>
using namespace std;
set<int> s;
bool chk[100010];
int data[ 50010];
int main()
{
	freopen("highcard.out","w",stdout);
	freopen("highcard.in","r",stdin);
	int n;
	scanf("%d",&n);
	int i;
	for(i=1;i<=n;++i) scanf("%d",data+i), chk[data[i]]=1;
	for(i=1;i<=2*n;++i) if(!chk[i]) s.insert(i);
	int ans=0;
	for(i=1;i<=n;++i){
		auto it=s.lower_bound(data[i]);
		if(it!=s.end()) ++ans, s.erase(it);
	}
	printf("%d\n",ans);
	return 0;
}
