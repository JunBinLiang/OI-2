using ll = long long;

const int N = 1010, INF = 1e9;
ll dp[N][N];

void init(int n) {
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            dp[i][j] = -INF;
        }
    }
}

class Solution {
public:
    int minimumTime(vector<int>& a, vector<int>& b, int x) {
        int n = a.size();
        init(n);
        long long s1 = 0, s2 = 0;
        for(int x : a) s1 += x;
        for(int x : b) s2 += x;
        
        if(s1 <= x) return 0; 
        
        vector<ll> p(n + 1);
        for(int i = 1; i <= n; i++) {
            p[i] = s1 + s2 * i;
        }
        
        vector<pair<int, int>> c;
        for(int i = 0; i < n; i++) c.push_back({b[i], a[i]});
        sort(c.begin(), c.end());
        
        //base not change
        //select x integers
        dp[0][0] = 0;
        for(int i = 1; i <= n; i++) {
            int x = c[i - 1].second, y = c[i - 1].first;
            for(int j = 0; j <= i; j++) {
                dp[i][j] = dp[i - 1][j];
                if(j) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + x + (j + 0ll) * y);
                }
            }
        }
        
        for(int j = 1; j <= n; j++) {
            for(int i = 1; i <= n; i++) {
                if(dp[i][j] + x >= p[j]) {
                    return j;
                }
            }
        }
        
        return -1;
    }
};
