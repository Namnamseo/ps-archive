#include <cstdio>
#include <set>
using namespace std;
struct tpl{
    int count[26];
    tpl operator-(const tpl& x) const {
        tpl ret;
        for(int i=0;i<26;++i) ret.count[i]=count[i]-x.count[i];
        return ret;
    }
    bool operator<(const tpl& x) const {
        for(int i=0;i<26;++i) if(count[i]!=x.count[i]) return count[i]<x.count[i];
        return false;
    }
    void operator=(const tpl& x){
        for(int i=0;i<26;++i) count[i]=x.count[i];
    }
};
set<tpl> s;
char da[1501];
char db[1501];
tpl ca[1501];
tpl cb[1501];
int n,m;
inline int max(int a,int b){ return a>b?a:b; }
inline int min(int a,int b){ return a>b?b:a; }
int main()
{
    scanf("%s%s",da+1,db+1);
    for(n=1;da[n];++n){
        ca[n]=ca[n-1];
        ++ca[n].count[da[n]-'a'];
    }
    for(m=1;db[m];++m){
        cb[m]=cb[m-1];
        ++cb[m].count[db[m]-'a'];
    }
    --n; --m;
    int len, maxlen = min(n,m);
    int i,j;
    tpl tmp;
    for(len=maxlen; len>=1; --len){
        for(i=len; i<=m; ++i){
            tmp=cb[i]-cb[i-len];
            s.insert(tmp);
        }
        for(i=len; i<=n; ++i){
            tmp=ca[i]-ca[i-len];
            if(s.find(tmp)!=s.end()){
                break;
            }
        }
        if(i<=n) break;
    }
    printf("%d\n",len);
    return 0;
}
