#include "cmp.h"

int helper(int lev, int pos) {
	for(int i = 0; i < lev; ++i)
		pos += (1 << (12 - (2*i)));
	return 1 + pos;
}

void remember(int a) {
	for(int i =  0; i < 6; ++i)
		bit_set(helper(i, a >> (2*i)));
}

int final(int a, int b) {
	if(b < a) return -1;
	if(b == a) return 0;
	if(b > a) return 1;
}

int compare(int b) {
	//    [5]    [4]    [3]    [2]    [1]    [0]
	// 11 10 / 9  8 / 7  6 | 5  4 / 3  2 / 1  0  (-1)
	if(bit_get(helper(3, b >> 6))) {
		// different= (-1)-5
		if(bit_get(helper(1, b >> 2))) {
			// different = (-1)-1
			if(bit_get(helper(0, b >> 0))) {
				return 0;
			} else {
				// different = 0 - 1.
				if(bit_get(helper(0, (b >> 0) ^ 1))) {
					return final(b^1, b);
				} else {
					return final(b^2, b);
				}
			}
		} else {
			// different= 2-5
			if(bit_get(helper(2, (b >> 4)))) {
				// different= 2-3
				if(bit_get(helper(1, (b >> 2) ^ 1))) {
					return final(b^(1<<2), b);
				} else {
					return final(b^(1<<3), b);
				}
			} else {
				// different= 4-5
				if(bit_get(helper(2, (b >> 4) ^ 1))) {
					return final(b^(1<<4), b);
				} else {
					return final(b^(1<<5), b);
				}
			}
		}
	} else {
		// different= 6-11
		if(bit_get(helper(4, (b >> 8)))) {
			// different= 6-7
			if(bit_get(helper(3, (b >> 6) ^ 1))) {
				return final(b^(1<<6), b);
			} else {
				return final(b^(1<<7), b);
			}
		} else {
			// different= 8-11
			if(bit_get(helper(5, b >> 10))) {
				// 8-9
				if(bit_get(helper(4, (b >> 8) ^ 1))) {
					return final(b^(1<<8), b);
				} else {
					return final(b^(1<<9), b);
				}
			} else {
				// 10-11
				if(bit_get(helper(5, (b >> 10) ^ 1))) {
					return final(b^(1<<10), b);
				} else {
					return final(b^(1<<11), b);
				}
			}
		}
	}
}

