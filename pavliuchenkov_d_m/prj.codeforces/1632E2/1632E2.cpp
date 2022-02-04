// hard

#include <iostream>
#include <vector>

using namespace std;


int dfs(int v, vector<vector<uint32_t> > &tree, vector<uint32_t> &dist,
        int32_t p = -1, int32_t cur_d = 0) {
    uint32_t a = cur_d, b = cur_d;
    for(uint32_t u: tree[v]) {
        if(u == p) continue;
        int s_d = dfs(u, tree, dist, v, cur_d + 1);
        if(s_d > a) {
            b = a;
            a = s_d;
        } else if(s_d > b) {
            b = s_d;
        }
    }

    int32_t i = min(a, b) - 1;
    if(i >= 0) {
        dist[i] = max(dist[i], a + b - 2 * cur_d + 1);
    }
    return a;
}


void solve(uint32_t n, vector<vector<uint32_t> > &tree) {
    vector<uint32_t> dist(n, 0);

    int m_ans = dfs(0, tree, dist);
    for (int32_t i = n - 2; i >= 0; --i)
        dist[i] = max(dist[i], dist[i + 1]);

    int ans = 0;
    for (uint32_t k = 1; k <= n; ++k) {
        while(ans < m_ans && k + dist[ans] / 2 > ans)
            ++ans;
        cout << ans << ' ';
    }
    cout << endl;
}


int main() {
    uint32_t t, n;
    vector<vector<uint32_t> > tree;
    cin >> t;
    for (uint32_t i = 0; i < t; ++i) {
        cin >> n;
        tree.assign(n, {});
        for(int j = 0; j < n - 1; ++j) {
            int a, b;
            cin >> a >> b;
            tree[a - 1].push_back(b - 1);
            tree[b - 1].push_back(a - 1);
        }
        solve(n, tree);
    }
}
