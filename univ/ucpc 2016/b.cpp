#include <cstdio>
#include <algorithm>
using namespace std;
#define pb push_back
#define all(v) v.begin(), v.end()

typedef pair<int,int> pp;

vector<pp> vec;
bool on[300010];

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1; i<=n; ++i){
    	int a,b; scanf("%d%d", &a, &b);
    	vec.emplace_back(a, -i);
    	vec.emplace_back(b,  i);
	}
	sort(all(vec));
	int sz=2*n;
	int ans=0, cnt=0, ap;
	for(int i=0; i<sz;){
		int j;
		for(j=i; j<sz && vec[i].first==vec[j].first && vec[j].second<0; ++j) ++cnt;
		if(ans<cnt){
			ans=cnt;
			ap=i;
		}
		for(   ; j<sz && vec[i].first==vec[j].first && vec[j].second>0; ++j) --cnt;
		i=j;
	}

	printf("%d\n", ans);
	for(int i=0; i<sz;){
		int j;
		for(j=i; j<sz && vec[i].first==vec[j].first && vec[j].second<0; ++j)
			on[-vec[j].second]=true, ++cnt;
		if(ap == i){
			for(int i=1; i<=n; ++i) if(on[i]) printf("%d ",i);
			return 0;
		}
		for(   ; j<sz && vec[i].first==vec[j].first && vec[j].second>0; ++j)
			on[vec[j].second]=false, --cnt;
		i=j;
	}

    return 0;
}

