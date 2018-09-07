#include <bits/stdc++.h>
using namespace std;

int press(string);

string guess_sequence(int n){
	string p;
	string use;
	if(press("AB")){
		if(press("A")){
			p = "A";
			use = "BXY";
		} else {
			p = "B";
			use = "AXY";
		}
	} else {
		if(press("X")){
			p = "X";
			use = "BAY";
		} else {
			p = "Y";
			use = "BXA";
		}
	}
	if(n == 1) return p;
	for(int i=1; i+1<n; ++i){
		int val = press(p+use[0]+use[0] + p+use[0]+use[1] + p+use[0]+use[2] + p+use[1]) - p.length();
		if(val == 0) p += use[2];
		else if(val == 2) p += use[0];
		else p += use[1];
	}
	if(press(p+use[0]+p+use[1]) == n){
		if(press(p+use[0]) == n) p += use[0];
		else p += use[1];
	} else {
		 p += use[2];
	}
	return p;
}
