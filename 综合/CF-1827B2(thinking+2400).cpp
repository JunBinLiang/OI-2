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

const int N = 3e5 + 10;
int a[N];
int lmin[N], lmax[N], rmin[N];

void solve() {
  int n;
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  ll res = 0;
  for(int i = 1; i <= n; i++) {
    ll x = (i + 1ll) * i / 2;
    x -= i;
    res += x;    
  }
  
  for(int i = 0; i < n; i++) {
      lmin[i] = -1; lmax[i] = -1;
      rmin[i] = n;
  }
  
  vector<int> stk;
  for(int i = n - 1; i >= 0; i--) {
      while(stk.size() > 0 && a[i] < a[stk.back()]) stk.pop_back();
      if(stk.size()) rmin[i] = stk.back();
      stk.push_back(i);
  }
  stk.clear();
  
  for(int i = 0; i < n; i++) {
      while(stk.size() > 0 && a[i] < a[stk.back()]) stk.pop_back();
      if(stk.size()) lmin[i] = stk.back();
      stk.push_back(i);
  }
  
  
  //easy version
  /*
  for(int i = 0; i < n; i++) {
    //if a[i] is min
    int x = -1, y = -1, z = n;
    for(int j = i - 1; j >= 0; j--) {
      if(a[j] < a[i]) {
        y = j;
        break;
      }
    }
    if(y == -1) continue;
    for(int j = y - 1; j >= 0; j--) {
      if(a[j] > a[i]) {
        x = j;
        break;
      }
    }
 
    for(int j = i + 1; j < n; j++) {
      if(a[j] < a[i]) {
        z = j;
        break;
      }
    }
    res -= ((y - x + 0ll) * (z - i));
  }
  
  */
  vector<pair<int, int>> b;
  for(int i = 0; i < n; i++) {
      b.push_back({a[i], i});
  }
  
  sort(b.begin(), b.end());
  set<int> s;
  for(int j = n - 1; j >= 0; j--) {
    int v = b[j].first, i = b[j].second;
    auto it = s.upper_bound(lmin[i]);
    if(it == s.begin()) {
        s.insert(i);
        continue;
    }
    it--;
    lmax[i] = *it;
    s.insert(i);
  }
  
 
  for(int i = 0; i < n; i++) {
    //if a[i] is min
    int x = -1, y = -1, z = n;
    y = lmin[i];
    if(y == -1) continue;
    //[0 : y - 1]
    x = lmax[i];
    z = rmin[i];
    res -= ((y - x + 0ll) * (z - i));
  }
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
