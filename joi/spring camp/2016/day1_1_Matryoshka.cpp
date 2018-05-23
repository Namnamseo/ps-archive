#include <bits/stdc++.h>
using namespace std;
void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define ind(x,y) lower_bound(x.begin(), x.end(), y) - x.begin()
typedef pair<int,int> pp;
typedef tuple<int,int,int> tp;

int n, q;

vector<int> xp, yp;
vector<pp> pts;
vector<tp> qry;

int ans[200010];

struct SEG {
    static const int M = 524288;
    int tree[M<<1];
    
    void upd(int pos, int val){
        pos += M;
        while(pos) tree[pos]=max(tree[pos], val), pos>>=1;
    }
    
    int rmax(int l,int r){
        l+=M; r+=M;
        int ret=0;
        while(l<=r){
            if(l%2==1) ret=max(ret, tree[l++]);
            if(r%2==0) ret=max(ret, tree[r--]);
            l>>=1; r>>=1;
        }
        return ret;
    }
} seg;

int main()
{
    freopen("in", "r", stdin);
    read(n, q); pts.resize(n);
    for(auto& a:pts) read(a.first, a.second), xp.pb(a.first), yp.pb(a.second);
    qry.resize(q);
    for(int i=0; i<q; ++i){
        int x, y;
        read(x, y);
        qry[i]=make_tuple(x, y, i);
        xp.pb(x);
        yp.pb(y);
    }

    sort(all(xp)); xp.erase(unique(all(xp)), xp.end());
    sort(all(yp)); yp.erase(unique(all(yp)), yp.end());
    
    for(auto& a:pts) a.first=ind(xp, a.first), a.second=ind(yp, a.second);
    for(int j=0; j<q; ++j){
        int x, y, i;
        tie(x, y, i) = qry[j];
        x=ind(xp, x);
        y=ind(yp, y);
        qry[j] = tie(x, y, i);
    }
    
    sort(all(pts), [&](const pp& a, const pp& b){
         if(a.first != b.first) return a.first > b.first;
         return a.second < b.second;
    });

    sort(all(qry), greater<tp>());
    
    int ip=0, iq=0;
    
    for(int i=xp.size()-1; 0<=i; --i){
        while(ip < pts.size()){
            int x, y;
            tie(x, y) = pts[ip];
            if(x != i) break;
            int val = seg.rmax(0, y) + 1;
            seg.upd(y, val);
            ++ip;
        }
        while(iq < qry.size()){
            int x, y, ind;
            tie(x, y, ind) = qry[iq];
            if(x != i) break;
            int val = seg.rmax(0, y);
            ans[ind] = val;
            ++iq;
        }
    }
    
    for(int i=0; i<q; ++i) printf("%d\n", ans[i]);
    
    return 0;
}
