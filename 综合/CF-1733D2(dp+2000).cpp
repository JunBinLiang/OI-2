#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>
#include <fstream>
#include <iomanip>
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define var auto
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

unsigned long long seed = 75;
unsigned long long rands(){return seed = (seed << 15) + (seed << 8) + (seed >> 3);}

const int MOD = 998244353;
const int N = 5010;
const ll INF = 1000000000000000000ll;
ll dp[N][N];

int n, x, y;
string s, t;

ll dfs(vector<int>& b, int i, int cnt) {
    if(i >= b.size()) {
        int n = b.size() - cnt * 2;
        n /= 2;
        return (n + 0ll) * y;
    }
        
    if(dp[i][cnt] != -1) return dp[i][cnt];
    ll res = INF;
    //skip
    res = min(res, dfs(b, i + 1, cnt));
    if(i + 1 < b.size()) {
      res = min(res, (b[i + 1] - b[i] + 0ll) * x + dfs(b, i + 2, cnt + 1));
    }
    
    //cout << i << " " << cnt << " " << res << endl;

    return dp[i][cnt] = res;
}

void solve() {
    cin >> n >> x >> y;
    cin >> s >> t;
  
    vector<int> b;
    for(int i = 0; i < n; i++) {
        if(s[i] != t[i]) {
            b.push_back(i);
            //cout << i << " ";
        }
    }
    //cout << endl;
    
    if(b.size() % 2 == 1) {
        cout << -1 << endl;
        return;
    }
    if(b.size() == 0) {
      cout << 0 << endl;
      return;
    }

    if(b.size() == 2) {
      ll t1 = (b[1] - b[0] + 0ll) * x;
      ll t2 = y; if(b[0] + 1 == b[1]) t2 += t2;
      cout << min(t1, t2) << endl;
      return;
    }
    
    for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) dp[i][j] = -1;
    ll res = dfs(b, 0, 0);
    cout << res << endl;

}

int main()
{
  int t = 1;
  cin >> t; 
  while(t--) {
    solve();
  }
  return 0;
}


