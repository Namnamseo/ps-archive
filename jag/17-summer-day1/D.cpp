#include <bits/stdc++.h>
using namespace std;

int main()
{
	double x, y, z;
	cin >> x >> y >> z;
	double pi = atan2(y, x);
	double l = z * cos(pi), r = x;
	for(int i=0; i<1000; ++i){
		double q = (l+r)/2;
		
		double al = atan2(z * sin(pi), max(0., q - z*cos(pi)));
		double ar = atan2(y, max(0., x-q));
		if(al >= ar) l=q;
		else r=q;
	}
	cout << setprecision(21) << l << endl;
	return 0;
}

