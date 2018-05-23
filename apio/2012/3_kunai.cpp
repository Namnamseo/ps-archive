#include <bits/stdc++.h>
using namespace std;
void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
typedef pair<int,int> pp;

#define DBG if(0)

int W, H;
int n;

int px[100010];
int py[100010];
int pdir[100010];

map<int, set<pp>> byX[4], byY[4];
map<int, set<pp>> byXpY[4], byXmY[4];

pp getMinCol(int i){
    pp col_time;
    if(pdir[i] == 0){
        col_time = {2*(W - px[i]) + 1, -1};
        {
            auto it=byY[2].find(py[i]);
            if(it != byY[2].end()){
                auto& v=it->second;
                auto it=v.lower_bound({px[i], 0});
                if(it != v.end()) col_time = min(col_time, {it->first - px[i], it->second});
            }
        }
        {
            auto it=byXpY[3].find(px[i]+py[i]);
            if(it != byXpY[3].end()){
                auto& v=it->second;
                auto it=v.lower_bound({px[i], 0});
                if(it != v.end()) col_time = min(col_time, {2*(it->first - px[i]), it->second});
            }
        }
        {
            auto it=byXmY[1].find(px[i]-py[i]);
            if(it != byXmY[1].end()){
                auto& v=it->second;
                auto it=v.lower_bound({px[i], 0});
                if(it != v.end()) col_time = min(col_time, {2*(it->first - px[i]), it->second});
            }
        }
    } else if(pdir[i] == 1){
        col_time = {2*py[i]-1, -1};
        {
            auto it=byX[3].find(px[i]);
            if(it != byX[3].end()){
                auto& v=it->second;
                auto it=v.lower_bound({py[i], 0});
                if(it != v.begin()) --it, col_time = min(col_time, {py[i] - it->first, it->second});
            }
        }
        {
            auto it=byXpY[2].find(px[i]+py[i]);
            if(it != byXpY[2].end()){
                auto& v=it->second;
                auto it=v.lower_bound({px[i], 0});
                if(it != v.end()) col_time = min(col_time, {2*(it->first - px[i]), it->second});
            }
        }
        {
            auto it=byXmY[0].find(px[i]-py[i]);
            if(it != byXmY[0].end()){
                auto& v=it->second;
                auto it=v.lower_bound({px[i], 0});
                if(it != v.begin()) --it, col_time = min(col_time, {2*(px[i] - it->first), it->second});
            }
        }
    } else if(pdir[i] == 2){
        col_time = {2*px[i]-1, -1};
        {
            auto it=byY[0].find(py[i]);
            if(it != byY[0].end()){
                auto& v=it->second;
                auto it=v.lower_bound({px[i], 0});
                if(it != v.begin()) --it, col_time = min(col_time, {px[i] - it->first, it->second});
            }
        }
        {
            auto it=byXpY[1].find(px[i]+py[i]);
            if(it != byXpY[1].end()){
                auto& v=it->second;
                auto it=v.lower_bound({px[i], 0});
                if(it != v.begin()) --it, col_time = min(col_time, {2*(px[i] - it->first), it->second});
            }
        }
        {
            auto it=byXmY[3].find(px[i]-py[i]);
            if(it != byXmY[3].end()){
                auto& v=it->second;
                auto it=v.lower_bound({px[i], 0});
                if(it != v.begin()) --it, col_time = min(col_time, {2*(px[i] - it->first), it->second});
            }
        }
    } else if(pdir[i] == 3){
        col_time = {2*(H - py[i]) + 1, -1};
        {
            auto it=byX[1].find(px[i]);
            if(it != byX[1].end()){
                auto& v=it->second;
                auto it=v.lower_bound({py[i], 0});
                if(it != v.end()) col_time = min(col_time, {it->first - py[i], it->second});
            }
        }
        {
            auto it=byXpY[0].find(px[i]+py[i]);
            if(it != byXpY[0].end()){
                auto& v=it->second;
                auto it=v.lower_bound({px[i], 0});
                if(it != v.begin()) --it, col_time = min(col_time, {2*(px[i] - it->first), it->second});
            }
        }
        {
            auto it=byXmY[2].find(px[i]-py[i]);
            if(it != byXmY[2].end()){
                auto& v=it->second;
                auto it=v.lower_bound({px[i], 0});
                if(it != v.end()) col_time = min(col_time, {2*(it->first - px[i]), it->second});
            }
        }
    }
    return col_time;
}

typedef tuple<int,int,int> tp;
typedef tuple<int,int,int,int> t4;
priority_queue<tp,vector<tp>,greater<tp>> pq;
bool dead[100010];
bool dying[100010];
int colt[100010];

void del_point(int i){
    byX[pdir[i]][px[i]].erase({py[i], i});
    byY[pdir[i]][py[i]].erase({px[i], i});
    
    byXpY[pdir[i]][px[i]+py[i]].erase({px[i], i});
    byXmY[pdir[i]][px[i]-py[i]].erase({px[i], i});
}

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

vector<int> yp;

struct node {
    int l, r;
    node *lp, *rp;
    int my_cnt;
    int sum;
    node(int L, int R){
        lp=rp=0;
        my_cnt = sum = 0;
        l=L; r=R;
        if(l!=r){
            int mid=(l+r)/2;
            lp=new node(l, mid);
            rp=new node(mid+1, r);
        }
    }
    
    void update(int ul, int ur, int val){
        if(ul <= l && r <= ur){
            my_cnt += val;
        } else if(ur<l || r<ul) return;
        else {
            lp->update(ul, ur, val);
            rp->update(ul, ur, val);
        }
        if(my_cnt != 0) assert(my_cnt > 0), sum = yp[r+1]-yp[l];
        else if(lp && rp) sum = lp->sum + rp->sum;
        else sum=0;
    }
} *root;

int main()
{
    read(W, H, n); for(int i=1; i<=n; ++i) read(px[i], py[i], pdir[i]);
    
    // save points
    for(int i=1; i<=n; ++i){
        byX[pdir[i]][px[i]].insert({py[i], i});
        byY[pdir[i]][py[i]].insert({px[i], i});
        
        byXpY[pdir[i]][px[i]+py[i]].insert({px[i], i});
        byXmY[pdir[i]][px[i]-py[i]].insert({px[i], i});
    }
    
    // find collision
    for(int i=1; i<=n; ++i){
        auto tmp = getMinCol(i);
        pq.push(make_tuple(tmp.first, tmp.second, i));
    }
    
    vector<pair<pp, pp>> rects;
    
    while(pq.size()){
        int cur_time = get<0>(pq.top());
        
        vector<int> del_points, aimai;
        while(pq.size() && get<0>(pq.top()) == cur_time){
            int time, yp, ind;
            tie(time, yp, ind) = pq.top(); pq.pop();
            if(dead[ind]) continue;
            if(yp != -1 && dying[yp]){
                del_point(yp);
                int x=ind;
                auto tmp = getMinCol(x);
                pq.push(make_tuple(tmp.first, tmp.second, x));
                continue;
            }
            del_points.pb(ind);
            dying[ind]=1;
            if(yp != -1) del_points.pb(yp), dying[yp]=1;
            
            auto ar = [&](int p) -> void {
                if(p == -1) return;
                int x=px[p], y=py[p], dir=pdir[p];
                int nx=x+dx[dir]*(time/2), ny=y+dy[dir]*(time/2);
                int left=min(x, nx), right=max(x, nx);
                int down=min(y, ny), up=max(y, ny);
                if(left<1) left=1; if(W<right) right=W;
                if(down<1) down=1; if(H<up) up=H;
                rects.pb({{down, up}, {left, right}});
                ::yp.pb(down); ::yp.pb(up+1);
            };
            ar(ind); ar(yp);
        }
        
        for(int x:del_points) dead[x]=1, del_point(x);
        for(int x:aimai){
            auto tmp = getMinCol(x);
            pq.push(make_tuple(tmp.first, tmp.second, x));
        }
    }
    
    yp.pb(0);
    sort(all(yp)); yp.erase(unique(all(yp)), yp.end());
    root = new node(0, yp.size()-2);
    
    vector<t4> qry;
    for(auto& tmp:rects){
        int left, right, down, up;
        tie(down, up) = tmp.first;
        tie(left, right) = tmp.second;
        down = lower_bound(all(yp), down) - yp.begin();
        up   = lower_bound(all(yp), up+1) - yp.begin();
        qry.pb(make_tuple(left, down, up, 1));
        qry.pb(make_tuple(right+1, down, up, -1));
    }
    
    sort(all(qry));
    int qn=qry.size();
    typedef long long ll;
    ll ans=0;
    int bx=0;
    for(int i=0; i<qn;){
        int cx=get<0>(qry[i]);
        ans += (cx-bx)*1LL*(root->sum);
        bx=cx;
        int j;
        for(j=i; j<qn && get<0>(qry[i]) == get<0>(qry[j]); ++j){
            int _, down, up, val;
            tie(_, down, up, val) = qry[j];
            root->update(down, up-1, val);
        }
        i=j;
    }
    assert(root->sum == 0);
    printf("%lld\n", ans);
    return 0;
}
