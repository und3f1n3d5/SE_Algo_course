// medium


#include <iostream>
#include <vector>

using namespace std;

int main() {
    uint32_t t = 0, n = 0, k = 0;
    cin >> t;

    // using dynamic programming, let's count minimal number of operations
    // needed to get j from 1
    vector<uint32_t> moves(3000, UINT32_MAX);
    moves[1] = 0;
    for (uint32_t j = 1; j <= 1000; ++j) {
        for (uint32_t x = 1; x <= j; ++x) {
            moves[(uint32_t) (j / x) + j] = min(moves[j] + 1, moves[(uint32_t) (j / x) + j]);
        }
    }

    // for every set
    for (uint32_t i = 0; i < t; ++i) {
        cin >> n >> k;
        vector<uint32_t> b(n);
        vector <uint32_t> c(n);
        for (uint32_t j = 0; j < n; ++j) {
            cin >> b[j];
        }
        for (uint32_t j = 0; j < n; ++j) {
            cin >> c[j];
        }

        // max(moves[i]) <= 12 for n <= 1000
        k = min(k, 12*n);

        // we came to the standard backpack problem
        vector<uint32_t> weights(n);
        for (uint32_t j = 0; j < n; ++j) {
            weights[j] = moves[b[j]];
        }
        vector<uint32_t> dp(k+1, 0);
        for (uint32_t j = 0; j < n; ++j) {
            for (int32_t s = k - weights[j]; s >= 0; --s) {
                dp[s + weights[j]] = max(dp[s + weights[j]], dp[s] + c[j]);
            }
        }
        cout << dp[k] << endl;
    }
    return 0;
}
