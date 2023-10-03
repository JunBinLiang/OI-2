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


const int N = 101, M = 5000, INF = 1000;
char s[N];
int dp[N][N][M];
int p[N][N][2];

int cal(int i) {
  int one = p[0][i][1], zero = (i + 1) - one;
  int n = one + zero;
  int tot = (n) * (n - 1) / 2;
  int O = (one) * (one - 1) / 2, Z = (zero) * (zero - 1) / 2;
  //cout << n << "  " << tot << "  " << O << "  " << Z << endl;
  tot -= (O + Z);
  return tot;
}

void init() {
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      for(int k = 0; k < M; k++) {
        dp[i][j][k] = INF;
      } 
    }
  }
}

void solve() {
  //count(sub 01) == count(sub 10)
  scanf("%s", s);
  int n = strlen(s);
  
  memset(p, 0, sizeof p);
  for(int i = 0; i < n; i++) {
    int one = 0, zero = 0;
    for(int j = i; j < n; j++) {
      if(s[j] == '1') one++;
      else zero++;
      p[i][j][0] = zero;
      p[i][j][1] = one;
    }
  }
  
  //observation1: each position is swap at most once
  init();
  if(s[0] == '0') {
    dp[0][1][0] = 0; //place 0
    dp[0][0][0] = 1; // place 1
  } else {
    dp[0][1][0] = 1; //place 0
    dp[0][0][0] = 0; // place 1
  }

  for(int i = 1; i < n; i++) {
    //place 0
    int add0 = (s[i] != '0');
    for(int j = 0; j <= min(p[0][n - 1][0] - 1, i); j++) {
      for(int c = 0; c < M; c++) {
        dp[i][j + 1][c] = min(dp[i][j + 1][c], dp[i - 1][j][c] + add0);
      }
    }

    //place 1
    int add1 = (s[i] != '1');
    for(int j = 0; j <= min(p[0][n - 1][0], i); j++) {
      for(int c = 0;  c < M; c++) {
        if(c + j < M) {
          dp[i][j][c + j] = min(dp[i][j][c + j], dp[i - 1][j][c] + add1);
        }
      }
    }
  }
  
  int res = INF;
  int tot = cal(n - 1) / 2;
  cout << dp[n - 1][p[0][n - 1][0]][tot] / 2 << endl;
  
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

