#include "Catherine.h"
#include <vector>
using namespace std;
using vi=vector<int>;

namespace {
int A, B;

int Move1(vi &y) {
    int oc = 0;
    for (int i=0; i<3; ++i) if (y[i]) ++oc;
    if (oc == 1) for (int i=0; i<3; ++i) if (y[i]) return i;

    int tmp = 0;
    for (int i=0; i<3; ++i) if (y[i]) tmp += i;
    tmp += 2;
    tmp *= 2;
    return tmp % 3;
}

}  // namespace

namespace {
int last_move;
vector<int> hist;
bool know;
}  // namespace

void Init(int A, int B) {
    ::A = A;
    ::B = B;
    last_move = -1;
}

int Move(vi y) {
    if (B == 0) return Move1(y);

    int last = last_move;
    int which;
    int ec = y[0] + y[1] + (last != -1);

    if (know) {
        if (ec >= 3) which = !last;
        else which = !!y[1];
    } else {
        if (ec >= 3) {
            which = (y[1]+(last==1) == 1);
            if (which == last) which = -1;
            know = true;
        } else if (ec == 1) {
            which = !!(y[1]+(last==1));
            if (which == last) which = -1;
            know = true;
        } else {
            if (last != -1) ++y[last];
            int state = (y[0] == 2) ? 0 :
                      (y[1] == 2) ? 1 : 2;
            if (last != -1) --y[last];
            if (hist.size() == 3u) {
                int t = hist[0]*1000 +
                        hist[1]*100 +
                        hist[2]*10 + state;
                int down_sign = 212022212;
                bool is_down = false;
                for (int i=0; i<6; ++i) {
                    if (down_sign%10000 == t) { is_down = true; break; }
                    down_sign /= 10;
                }
                if (is_down) which = last_move;
                else which = !!y[1];
                if (which == last) which = -1;
                know = true;
            } else {
                hist.push_back(state);
                which = !!y[1];
            }
        }
    }

    if (which != -1) last_move = which;
    return which;
}
