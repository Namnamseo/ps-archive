#include <bits/stdc++.h>
using namespace std;

vector<string> txt;

void read(){
	static char buf[200];
	int l = 0;
	while(true){
		char t = getchar();
		bool ia = ((0x41<=t && t<=0x5A) || (0x61<=t && t<=0x7A));
		if(!ia){
			if(l){
				buf[l] = 0;
				txt.push_back(buf);
				l = 0;
			}
			if(t < 0) break;
			buf[0]=t; buf[1]=0; txt.push_back(buf);
		} else {
			buf[l++] = t;
		}
	}
}

bool isCapital(string& s){
	int n = s.length();
	if(s[0] < 0x41 || s[0] > 0x5a || n == 1) return 0;
	for(int i=1; i<n; ++i) if(s[i] < 0x61 || s[i] > 0x7a) return 0;
	return 1;
}

int main(){
	read();
	for(int i=0; i<int(txt.size());){
		if(!isCapital(txt[i])){
			printf("%s", txt[i].c_str());
			++i;
			continue;
		}
		int j = i;
		while(j+2 < int(txt.size()) && txt[j+1] == " " && isCapital(txt[j+2])) j+=2;
		if(i == j){
			printf("%s", txt[i].c_str());
			++i;
			continue;
		}
		for(int k=i; k<=j; k+=2) putchar(txt[k][0]);
		printf(" (");
		for(int k=i; k<=j; k+=2){
			printf("%s", txt[k].c_str());
			if(k < j) putchar(' ');
		}
		printf(")");
		i = j+1;
		continue;
	}
	return 0;
}

