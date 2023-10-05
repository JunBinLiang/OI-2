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
const int N = 4050;
ll dp[2][N][N], p[2][N][N];

ll get(int i, int j, int l, int r) {
  if(l == 0) return p[i][j][r];
  else return (p[i][j][r] - p[i][j][l - 1] + MOD) % MOD;
}

int n, k;
void solve() {
  cin >> n >> k;
  
  if(k == 1) {
    cout << n << endl;
    return;
  }

  memset(dp, 0, sizeof dp);
  memset(p, 0, sizeof p);
  
  //i-th position
  //how many consecutive distinct numbers
  // 0 : ways  1 : score
  dp[0][1][1] = k;
  dp[1][1][1] = 0;
  
  for(int i = 1; i <= 1; i++) {
    for(int j = 1; j <= k; j++) {
        p[0][i][j] = dp[0][i][j];
        p[1][i][j] = dp[1][i][j];
        if(j > 1) {
            p[0][i][j] += p[0][i][j - 1];
            p[1][i][j] += p[1][i][j - 1];
        }
        p[0][i][j] %= MOD;
        p[1][i][j] %= MOD;
    }
  }

  for(int i = 2; i <= n; i++) {
    //add a new number
    for(int j = 2; j <= min(i, k); j++) {
      dp[0][i][j] += (dp[0][i - 1][j - 1] * (k - (j - 1)));
      dp[0][i][j] %= MOD;

      dp[1][i][j] += (dp[1][i - 1][j - 1] * (k - (j - 1)));
      dp[1][i][j] %= MOD;
      if(j == k) {
        dp[1][i][j] += dp[0][i - 1][j - 1];
        dp[1][i][j] %= MOD;
      }
    }
    dp[0][i][1] += (dp[0][i - 1][k] * k);
    dp[0][i][1] %= MOD;
    dp[1][i][1] += (dp[1][i - 1][k] * k);
    dp[1][i][1] %= MOD;
    
    //add a exist elements
    for(int j = 1; j <= k - 1; j++) {
      dp[0][i][j] += get(0, i - 1, j, k - 1);
      dp[0][i][j] %= MOD;
      
      dp[1][i][j] += get(1, i - 1, j, k - 1);
      dp[1][i][j] %= MOD;
    }
    
    for(int j = 1; j <= k; j++) {
        p[0][i][j] = dp[0][i][j];
        p[1][i][j] = dp[1][i][j];
        if(j > 1) {
            p[0][i][j] += p[0][i][j - 1];
            p[1][i][j] += p[1][i][j - 1];
        }
        p[0][i][j] %= MOD;
        p[1][i][j] %= MOD;
    }
  }
  
  /*for(int i = 1; i <= n; i++) {
      for(int j = 1; j <= k; j++) {
          cout << dp[0][i][j] << "  ";
      }
      cout << endl << endl;
      for(int j = 1; j <= k; j++) {
          cout << dp[1][i][j] << "  ";
      }
      cout << endl;
      cout << "___________________________" << endl << endl;
  }*/

  ll res = 0;
  for(int i = 1; i <= k; i++) {
    res += dp[1][n][i];
    res %= MOD;
  }
  cout << res << endl;

}

int main()
{
  int t = 1;
  //cin >> t; 
  while(t--) {
    solve();
  }
  return 0;
}


