#include <cstdio>
#include <cstdlib>
 
#include <vector>
#include <stack>
#include <algorithm>
#define all(x) (x).begin(), (x).end()
#define pb push_back
using namespace std;
 
typedef pair<int,int> pp;
stack<pp > st;
stack<int> left;
int n;
 
struct seg2d{
    static const int M=524288;
    vector<int> tree[M*2];
    void addPoint(int x,int y){
        y+=M;
        while(y){
            tree[y].pb(x);
            y>>=1;
        }
    }
    void init(){
        int i;
        for(i=1;i<2*M;++i) sort(all(tree[i]));
    }
    inline int get(int point,int x,int y){
        return max(0,int(upper_bound(all(tree[point]),y) -
                         lower_bound(all(tree[point]),x)));
    }
    int query(int l,int r,int x,int y){
        int ret=0;
        x+=M; y+=M;
        while(x<=y){
            if(x==y){
                ret += get(x,l,r); break;
            }
            if(x&1)      ret+=get(x++,l,r);
            if((y&1)==0) ret+=get(y--,l,r);
            x>>=1; y>>=1;
        }
        return ret;
    }
    int get_over(int x1,int x2,int k){
        int pos=1;
        int cnt=0;
        while(pos<M){
            int l=pos*2, r=l+1;
            int tmp=get(l,x1,x2);
            if(cnt+tmp < k){
                cnt += tmp;
                pos=r;
            } else pos=l;
        }
        return pos-M;
    }
} seg;
void init(int N, int A[], int B[]) {
    int i;
    n=N;
    for(i=0;i<N;++i) seg.addPoint(A[i],B[i]);
    seg.init();
}
 
int can(int M, int K[]) {
    sort(K,K+M);
    int i;
    while(st  .size()) st  .pop();
    while(left.size()) left.pop();
    st.push({0,n});
    left.push(0);
    for(i=0;i<M;++i){
 
        int& x=K[i];
        
        int curcnt=x, lasty=x-1;
        
        for(;st.size()>1;){
            auto t=st.top();
            if(t.second < x){
                st.pop(); left.pop();
                continue;
            }
            int cnt=seg.query(t.first+1, x, lasty+1, t.second) + left.top();
            if(curcnt <= cnt) {
                break;
            }
            st.pop(); left.pop();
            lasty  = t.second;
            curcnt -= cnt;
        }
        
        pp t=st.top();
        if(seg.query(t.first+1, x, lasty+1, t.second) + left.top() < curcnt) return 0;
        
        int R=min(t.second, seg.get_over(t.first+1, x, curcnt + seg.query(t.first+1, x, 0, lasty) ));
        
        left.push(seg.query(st.top().first+1,x,lasty+1,R)-curcnt);
        st.push({x,R});
    }
    return 1;
}
