#include <iostream>

using namespace std;

int main() {
    uint32_t n = 0, cur = 0;
    cin >> n;
    for (uint32_t i = 0; i < n; ++i) {
        cin >> cur;
        int8_t rest = cur % 7;
        if (rest == 0) {
            cout << cur << endl;
            continue;
        }
        if (7 - rest + cur % 10 < 10) {
            cur += 7 - rest;
        }
        else {
            cur -= rest;
        }
        cout << cur << endl;
    }
    return 0;
}
