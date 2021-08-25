#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair<int,int> bus;
int n,m;
pair<bus,int> data[1000010];
bool incl[500010];

int main()
{
    scanf("%d%d",&n,&m);
    int i,a,b,ind=0;
    for(i=0;i<m;++i){
        scanf("%d%d",&a,&b);
        if(a>b){
            data[ind].first ={a,-b-n};
            data[ind].second=i; ++ind;
        } else {
            data[ind].first={a  ,-b  }; data[ind].second=i; ++ind;
            data[ind].first={a+n,-b-n}; data[ind].second=i; ++ind;
        }
    }
    std::sort(data,data+ind);
    int curmax=-1;
    for(i=0;i<ind;++i){
        //printf("%d %d\n",data[i].first.first, -data[i].first.second);
        if(-data[i].first.second <= curmax) incl[data[i].second]=true;
        curmax=max(curmax,-data[i].first.second);
    }
    for(i=0;i<m;++i) if(!incl[i]) printf("%d ",i+1);
    return 0;
}
