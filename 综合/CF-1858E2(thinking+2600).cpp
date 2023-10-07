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


const int N = 1e6 + 10;
char op;
int n;

int p[N], a[N];
set<int> s[N];
vector<pair<int, int>> stk;

void solve() {
  memset(p, 0, sizeof p);
  memset(a, 0, sizeof a);

  int cur = 0;
  cin >> n;
  for(int i = 0; i < n; i++) {
    cin >> op;
    if(op == '+') {
      int v; cin >> v;
      cur++;
      stk.push_back({a[cur], p[cur]});
      if(a[cur]) {
        s[a[cur]].erase(cur);
      } 
      a[cur] = v;
      s[v].insert(cur);
      if(*(s[v].begin()) == cur) {
        p[cur] = 1;
      } else {
        p[cur] = 0;
      }
      p[cur] += p[cur - 1];
    } else if(op == '-') {
      int x; cin >> x;
      cur -= x;
      stk.push_back({-1, x});
    } else if(op == '!') {
      pair<int, int> pa = stk.back(); stk.pop_back();
      int x = pa.first, y = pa.second;
      if(x == -1) {
        cur += y;
      } else {
        p[cur] = y;
        s[a[cur]].erase(cur);
        a[cur] = x;
        if(x) {
            s[x].insert(cur);
        }
        cur--;
      }
    } else {
      cout << p[cur] << endl;
    }
  }

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
