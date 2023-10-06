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
int res[N];
struct Node {
  vector<int> nxt, ask, last;
  int v = -1, pa;
} nodes[N];

char op[2];
int n, idx = 1, cur = 0;

map<int, int> counter;
void dfs(int u) {
  if(u > 0) {
    counter[nodes[u].v] ++;
  }
  for(int i : nodes[u].ask) {
    res[i] = counter.size();
  }
  for(int nxt : nodes[u].nxt) {
    dfs(nxt);
  }
  if(u > 0) {
    counter[nodes[u].v] --;
    if(counter[nodes[u].v] == 0) counter.erase(nodes[u].v);
  }
}

int f[N][21];

void solve() {
  cin >> n;
  memset(res, -1, sizeof res);
  memset(f, -1, sizeof f);


  for(int i = 0; i < n; i++) {
    scanf("%s", op);
    if(op[0] == '+') {
      int v; scanf("%d", &v);
      nodes[idx].v = v;
      nodes[cur].nxt.push_back(idx);
      nodes[idx].pa = cur;
      nodes[idx].last.push_back(cur);
      f[idx][0] = cur;
      for(int j = 1; j < 21; j++) {
        if(f[idx][j - 1] == -1) break;
        f[idx][j] = f[f[idx][j - 1]][j - 1];  
      }
      cur = idx;
      idx++;
    } else if(op[0] == '-') {
      int k; scanf("%d", &k);
      /*int t = cur;
      for(int j = 0; j < k; j++) {
        t = nodes[t].pa;
      }*/
      //jump
      int t = cur;
      for(int j = 20; j >= 0; j--) {
          if(k & (1 << j)) t = f[t][j];
      }
      nodes[t].last.push_back(cur);
      cur = t;
    } else if(op[0] == '!') {
      int pre = nodes[cur].last.back();
      nodes[cur].last.pop_back();
      cur = pre;
    } else {
      nodes[cur].ask.push_back(i);
    }
  }

  dfs(0);

  for(int i = 0; i < n; i++) {
    if(res[i] != -1) {
      printf("%d\n", res[i]);
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

