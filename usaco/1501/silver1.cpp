#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

int n;
struct el{
	int pos;
	int y;
	int code;
	bool start;
	bool operator<(const el& other) const{ return pos<other.pos; }
} elem[100010];

bool canSee[50010];

typedef pair<int,int> pp;

set<pp> s;

#define mp make_pair

int main()
{
	freopen("stampede.in","r",stdin);
	freopen("stampede.out","w",stdout);
	scanf("%d",&n);
	int i,x,y,r;
	for(i=0;i<n;++i){
		scanf("%d%d%d",&x,&y,&r);
		elem[2*i  ].pos  = (-1-x)*r;
		elem[2*i  ].y    = y      ;
		elem[2*i  ].code = i      ;
		elem[2*i  ].start=true;
		
		elem[2*i+1].pos  = ( -x)*r;
		elem[2*i+1].y    = y      ;
		elem[2*i+1].code = i      ;
		elem[2*i+1].start=false;
	}
	sort(elem,elem+2*n);
	for(i=0;i<2*n;++i){
		if(elem[i].start){
			s.insert(mp(elem[i].y,elem[i].code));
		} else {
			s. erase(mp(elem[i].y,elem[i].code));
		}
		if(i+1==2*n || elem[i].pos!=elem[i+1].pos){
			if(!s.empty()) {
				canSee[s.begin()->second]=true;
			}
		}
	}
	int ans=0;
	for(i=0;i<n;++i) if(canSee[i]) ++ans;
	printf("%d\n",ans);
	return 0;
}
