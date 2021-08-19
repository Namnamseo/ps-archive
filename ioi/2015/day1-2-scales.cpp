#include "scales.h"
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

int lst[720][6];

void init(int T) {
    int cur[6];
    for(int i=0; i<6; ++i) cur[i]=i+1;
    int ind=0;
    do {
        for(int i=0; i<6; ++i) lst[ind][i]=cur[i];
        ++ind;
    } while(next_permutation(cur, cur+6));
}

inline int f1(int a,int b,int c){ return max(a, max(b, c)); }
inline int f2(int a,int b,int c){ return min(a, min(b, c)); }
inline int f3(int a,int b,int c){ return a+b+c-f1(a,b,c)-f2(a,b,c); }
inline int f4(int a,int b,int c,int d){
    int t;
    if((t=f1(a,b,c))<d) return f2(a,b,c);
    else {
        int u=f2(a,b,c);
        int v=a+b+c-t-u;
        if(v<d) return t;
        if(u<d) return v;
        return u;
    }
}

int maxdiff(vector<int>& av,vector<int>& bv,vector<int>& cv){
    int a=av.size(), b=bv.size(), c=cv.size();
    if(a>b) swap(a,b);
    if(b>c) swap(b,c);
    if(a>b) swap(a,b);
    return c;
}

struct func_obj{
    int type, a, b, c, d;
};

tuple<vector<int>,vector<int>,vector<int>> getAppliedStates(vector<int>& states,int type,int a,int b,int c,int d){
    vector<int> x,y,z;
    for(int s:states){
        int ret=0;
             if(type==1) ret=f1(lst[s][a],lst[s][b],lst[s][c]);
        else if(type==2) ret=f2(lst[s][a],lst[s][b],lst[s][c]);
        else if(type==3) ret=f3(lst[s][a],lst[s][b],lst[s][c]);
        else if(type==4) ret=f4(lst[s][a],lst[s][b],lst[s][c],lst[s][d]);
        if(ret == lst[s][a]) x.push_back(s);
        else if(ret == lst[s][b]) y.push_back(s);
        else z.push_back(s);
    }
    return tuple<vector<int>,vector<int>,vector<int>>(x,y,z);
}

vector<func_obj> getSuitableFunc(vector<int>& states){
    vector<func_obj> ret;
    int cur_diff = 2e9;
    for(int i=0; i<6; ++i){
        for(int j=0; j<6; ++j){
            if(i==j) continue;
            for(int k=0; k<6; ++k){
                if(k==i || k==j) continue;
                vector<int> a,b,c;
                for(int l=0; l<6; ++l){
                    if(i==l || j==l || k==l) continue;
                    tie(a,b,c) = getAppliedStates(states, 4, i, j, k, l);
                    if(maxdiff(a,b,c) <= cur_diff){
                        if(maxdiff(a,b,c) < cur_diff) ret.clear();
                        cur_diff = maxdiff(a,b,c);
                        ret.push_back({4, i, j, k, l});
                    }
                }
                
                tie(a,b,c) = getAppliedStates(states, 1, i, j, k, 0);
                if(maxdiff(a,b,c) <= cur_diff){
                    if(maxdiff(a,b,c) < cur_diff) ret.clear();
                    cur_diff = maxdiff(a,b,c);
                    ret.push_back({1, i, j, k, 0});
                }
                
                tie(a,b,c) = getAppliedStates(states, 2, i, j, k, 0);
                if(maxdiff(a,b,c) <= cur_diff){
                    if(maxdiff(a,b,c) < cur_diff) ret.clear();
                    cur_diff = maxdiff(a,b,c);
                    ret.push_back({2, i, j, k, 0});
                }
                
                tie(a,b,c) = getAppliedStates(states, 3, i, j, k, 0);
                if(maxdiff(a,b,c) <= cur_diff){
                    if(maxdiff(a,b,c) < cur_diff) ret.clear();
                    cur_diff = maxdiff(a,b,c);
                    ret.push_back({3, i, j, k, 0});
                }
            }
        }
    }
    return ret;
}

int pow3[] = {1, 3, 9, 27, 81, 243, 729};

func_obj lastfunc;

bool isValidState(vector<int>& states,int depth){
    if(states.size() <= 1) return true;
    if(depth>=6) return false;
    if(states.size() > pow3[6-depth]) return false;
    vector<int> a,b,c;
    auto t=getSuitableFunc(states);
    for(func_obj move : t){
        tie(a,b,c) = getAppliedStates(states, move.type, move.a, move.b, move.c, move.d);
        if(a.size()>pow3[5-depth] || b.size()>pow3[5-depth] || c.size()>pow3[5-depth]){
            return false;
        }
        if(isValidState(a, depth+1) &&
           isValidState(b, depth+1) &&
           isValidState(c, depth+1)){
            lastfunc = move;
            return true;
        }
    }
    return false;
}

void orderCoins() {
    vector<int> states, new_states;
    for(int i=0; i<720; ++i) states.push_back(i);
    int depth = 0;
    int first_state = -1;
    while(true){
        if(states.size()==1){
            int s=states[0];
            int ans[6];
            for(int i=0;i<6;++i){
                ans[lst[s][i]-1]=i+1;
            }
            answer(ans);
            break;
        }
        bool isPoss;
        func_obj f;
        if(depth>=2){
            isValidState(states, depth);
            f = lastfunc;
        } else if(depth==0) {
            f = {1,0,1,2,0};
        } else if(depth==1){
            f={3, 3, 4, 5, 0};
        }
        auto t=getAppliedStates(states, f.type, f.a, f.b, f.c, f.d);
        int ret;
        if(f.type == 1) ret=getHeaviest(f.a+1, f.b+1, f.c+1);
        if(f.type == 2) ret=getLightest(f.a+1, f.b+1, f.c+1);
        if(f.type == 3) ret=getMedian(f.a+1, f.b+1, f.c+1);
        if(f.type == 4) ret=getNextLightest(f.a+1, f.b+1, f.c+1, f.d+1);
        
        if(ret == f.a+1){
            states=get<0>(t);
            if(depth==0) first_state = 0;
        } else if(ret==f.b+1){
            states=get<1>(t);
            if(depth==0) first_state = 1;
        } else if(ret==f.c+1){
            states=get<2>(t);
            if(depth==0) first_state = 2;
        }
        ++depth;
    }
}
