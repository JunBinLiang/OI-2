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
const int N = 61, M = 1e5 + 1;
ll n, m;
int cnt[N];
ll p[N], pp[N + 1];
ll colors[N * 2][M];
ll range[N + 5][2];
int f[M];
ll leftCnt[N * 2 + 1], rightCnt[N * 2 + 1];
ll fdp[N * 3];

ll fpow(ll x, ll y){
    if(x == 0 || y < 0) return 0;
    if(x == 1) return 1;
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
} 

void init() {
  for(int len = 1; len < N * 2; len++) {
    for(int color = 1; color < M; color++) {
      if(color == 1) {
        colors[len][color] = fpow(color, len);
        f[color] = colors[len][color];
      } else {
        f[color] = fpow(color, len);
        colors[len][color] = f[color] - f[color - 1];
      }
      if(colors[len][color] < 0) colors[len][color] += MOD;
      colors[len][color] *= color;
      colors[len][color] %= MOD;
      if(color > 1) colors[len][color] += colors[len][color - 1];
      if(colors[len][color] >= MOD) colors[len][color] -= MOD;
    }
  }
  p[0] = 1;
  p[1] = 1;
  for(int i = 2; i < N; i++) {
    p[i] = p[i - 1] * 2;
    p[i] %= MOD;
  }

  pp[0] = 1;
  for(int i = 1; i <= N; i++) {
    pp[i] = pp[i - 1] * 2;
  }
}

void solve() {
  ll res = 0;
  memset(cnt, 0, sizeof cnt);
  memset(range, -1, sizeof range);
  for(int i = 0; i < N * 3; i++) fdp[i] = fpow(m, n - i);
  
  for(int d = 1; d <= N; d++) {
    ll po1 = -1, po2 = -1, l = 1, r = n;
    ll t = n / pp[d - 1];
    ll bit = ((1ll << (d - 1)) - 1);
    while(l <= r) {
      ll mid = l + (r - l) / 2;
      ll x = mid;
      if(x > t) {
          r = mid - 1;
          continue;
      }
      x <<= (d - 1);
      x += bit;
      if(x <= n) {
        po1 = mid;
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    } 
    if(po1 == -1) break;
    l = 1; r = po1;
    while(l <= r) {
      ll mid = l + (r - l) / 2;
      ll x = mid << d;
      if(x <= n) {
        l = mid + 1;
      } else {
        po2 = mid;
        r = mid - 1;
      }
    }
    if(po2 == -1) continue;
    cnt[d] = (po1 - po2 + 1) % MOD;
    range[d][0] = po2, range[d][1] = po1;
  }
  
  for(int x = 2; x <= N; x++) {
    if(cnt[x] == 0) break;
    for(int len = 1; len <= x * 2 - 1; len++) {
      ll ways = 0;
      for(int left = 0; left <= x - 1; left++) {
        int right = len - 1 - left;
        if(right > x - 1 || right < 0) continue;
        ways += (p[left] * p[right]);
        ways %= MOD;
      }

      if(n >= len) {
          ll sum = (colors[len][m] * ways) % MOD; 
          sum *= fdp[len];
          sum %= MOD;
          sum *= cnt[x];
          sum %= MOD;
          res += sum;
          res %= MOD;
      }
    }
  }
  

  ll x = colors[1][m] * fpow(m, n - 1);
  x %= MOD;
  x *= cnt[1];
  x %= MOD;
  res += x;
  res %= MOD;
  
  ll nn = n;
  //if(bincount(n + 1) != 1) {
    int mxLen = 2;
    nn /= 2;
    while(nn >= 1) {
      if(nn >= range[mxLen][0] && nn <= range[mxLen][1]) {
        nn /= 2;
        mxLen++;
        continue;
      }

      ll root = nn;
      leftCnt[0] = rightCnt[0] = 1;
      for(int left = 1; left <= mxLen - 1; left++) {
          ll l = root * 2, r = root * 2;
          for(int i = 0; i < left - 1; i++) {
              l = l * 2;
              r = r * 2 + 1;
              if(l > n) break;
          }
          if(l > n) leftCnt[left] = 0;
          else {
            leftCnt[left] = (min(r, n) - l + 1) % MOD;
          }
      }
      
      for(int right = 1; right <= mxLen - 1; right++) {
          ll l = root * 2 + 1, r = root * 2 + 1;
          for(int i = 0; i < right - 1; i++) {
              l = l * 2;
              r = r * 2 + 1;
              if(l > n) break;
          }
          if(l > n) rightCnt[right] = 0;
          else {
            rightCnt[right] = (min(r, n) - l + 1) % MOD;
          }
      }
      
      for(int len = 1; len <= mxLen * 2 - 1; len++) {
        ll ways = 0;
        for(int left = 0; left <= mxLen - 1; left++) {
          int right = len - 1 - left;
          if(right < 0 || right > mxLen - 1) continue;
          if(left == 0 && right == 0 && len == 1) {
            ways++;
            continue;
          }
          ways += (leftCnt[left] * rightCnt[right]);
          ways %= MOD;
        }
        
        if(n - len >= 0) {
            ll sum = (colors[len][m] * ways) % MOD; 
            sum *= fdp[len];
            sum %= MOD;
            res += sum;
            res %= MOD;
        }
      }
      mxLen++;
      nn /= 2;
    //}
  }
  printf("%lld\n", res);
}

int main()
{
  init();
  
  /*for(int i = 0; i < 200; i++) {
      n = 502453101139881071;
      m = 500;
      solve();
  }
  return 0;*/
  
  int t = 1;
  cin >> t; 
  while(t--) {
    scanf("%lld%lld", &n, &m);
    solve();
  }
  return 0;
}



