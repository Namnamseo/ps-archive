#include "paint.h"

#include <cstdlib>

using namespace std;

bool L [200010][110];
bool LS[200010][110];
bool R [200010][110];

int psEmpty[200010];
int psFill [200010];

bool canFill(int a, int b){
    if(a) return !(psEmpty[b]-psEmpty[a-1]);
    else return !psEmpty[b];
}

string s;
vector<int> c;
int n, k;

bool canEmpty(int p){
    return s[p] != 'X';
}

bool canEmpty(int a, int b){
    if(a) return !(psFill[b]-psFill[a-1]);
    else return !psFill[b];
}

bool testEmptyK(int a,int j){
    if(a && L[a-1][j]  && ((j+1==k && canEmpty(a, n-1)) || R[a+1][j+1]))
        return true;
    return false;
}

typedef long long ll;
ll fillPref[200010];

bool testFill(int a){
    if(!canFill(a,a)) return false;
    if(s[a] == 'X') return true;
    return fillPref[a];
}

bool testEmpty(int a){
    if(!canEmpty(a)) return false;
    if(a+1<n && R[a+1][0] && canEmpty(0, a)){
        return true;
    }
    for(int j=0; j<k; ++j) if(testEmptyK(a, j)) return true;
    return false;
}

string solve_puzzle(string s_, vector<int> c_) {
    s = s_; c = c_;
    n = s.length();
    k = c.size();

    psEmpty[0] = (s[0] == '_');
    psFill [0] = (s[0] == 'X');
    for(int i=1; i<n; ++i){
        psEmpty[i]=psEmpty[i-1] + (s[i] == '_');
        psFill [i]=psFill [i-1] + (s[i] == 'X');
    }

    for(int i=n-1; 0<=i; --i){
        for(int j=0; j<k; ++j){
            if(i+1<n && canEmpty(i)) R[i][j] = R[i+1][j];
            int np = i+c[j]-1;
            if(np >= n) continue;
            if(canFill(i, np)){
                if(j == k-1 && (np==n-1 || canEmpty(np+1, n-1))){
                    R[i][j] = true;
                } else if(j+1<k && np+2<n && canEmpty(np+1) && R[np+2][j+1]){
                    R[i][j] = true;
                }
            }
        }
    }

    for(int i=0; i<n; ++i){
        for(int j=0; j<k; ++j){
            if(i && canEmpty(i)) L[i][j] = L[i-1][j];
            int bp = i-c[j]+1;
            if(bp >=0 && canFill(bp, i)){
                if(j == 0 && (bp==0 || canEmpty(0, bp-1))){
                    L[i][j] = true;
                    LS[i][j] = true;
                } else if(j && bp>1 && canEmpty(bp-1) && L[bp-2][j-1]){
                    L[i][j] = true;
                    LS[i][j] = true;
                }
            }
            if(!LS[i][j]) continue;
            if((j==k-1 && (i+1==n || canEmpty(i+1, n-1))) ||
                (j!=k-1 && i+2<n && canEmpty(i+1, i+1) && R[i+2][j+1])){
                    fillPref[bp] += 1;
                    fillPref[i+1] -= 1;
                }
        }
    }

    for(int i=1; i<n; ++i) fillPref[i] += fillPref[i-1];

    string ret;
    for(int i=0; i<n; ++i){
        bool a=testFill(i), b=testEmpty(i);
        if(a){
            if(b){
                ret += '?';
            } else ret += 'X';
        } else ret += '_';
    }

    return ret;
}
