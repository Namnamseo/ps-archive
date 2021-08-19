#include <vector>
#include <bits/stdc++.h>
using namespace std;

#include "messy.h"

char s[200];

void search(int tl, int tr) {
    if(tl+1 == tr) {
        return;
    }

    int mid = (tl+tr) / 2;
    for(int i = tl; i < mid; ++i) {
        s[i] = '1';
        add_element(s);
        s[i] = '0';
    }

    fill(s+tl, s+mid, '1');
    search(mid, tr);
    fill(s+tl, s+mid, '0');

    fill(s+mid, s+tr, '1');
    search(tl, mid);
    fill(s+mid, s+tr, '0');
}

int ans[200];

void hcraes(int tl, int tr) {
    int mid = (tl + tr) / 2;
    if(tl+1 == tr) return;

    for(int i=tl, ni=tl; i<tr; ++i) {
        s[ans[i]] = '1';
        bool res = check_element(s);
        s[ans[i]] = '0';

        if(res) {
            swap(ans[i], ans[ni++]);
        }
    }

    for(int i=mid; i<tr; ++i) s[ans[i]] = '1';
    hcraes(tl, mid);
    for(int i=mid; i<tr; ++i) s[ans[i]] = '0';

    for(int i=tl; i<mid; ++i) s[ans[i]] = '1';
    hcraes(mid, tr);
    for(int i=tl; i<mid; ++i) s[ans[i]] = '0';
}

std::vector<int> restore_permutation(int n, int w, int r) {
    fill(s, s+n, '0');
    search(0, n);

    compile_set();

    iota(ans, ans+n, 0);
    fill(s, s+n, '0');
    hcraes(0, n);

    vector<int> ret(n);
    for(int i=0; i<n; ++i) ret[ans[i]] = i;
    return ret;
}
