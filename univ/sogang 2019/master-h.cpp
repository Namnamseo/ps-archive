#include <cstdio>
int main(){
    int n;
    scanf("%d", &n);
    long long b = 1, mod = int(1e9) + 7;
    n += 2;
    for(;n--;) {
        (b *= 2) %= mod;
    }
    b += mod-5;
    b %= mod;
    printf("%lld\n", b);
    return 0;
}
