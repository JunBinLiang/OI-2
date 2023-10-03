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


const int N = 5050;
int a[N];
bool vis[N * 2], slot[N * 2];
int pos[N];
vector<int> p[N];
bool s[N];
void solve() {
  int n;
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    //a[i] = i % 3;
  }
  for(int i = 0; i <= n; i++) p[i].clear();
  
  int m = n * 2;
  for(int i = 0; i <= m; i++) {
    vis[i] = false;
    pos[i] = 0;
  }

  p[0].push_back(0);
  vis[0] = true;

  for(int i = 1; i <= n; i++) {
    for(int x = 0; x <= n + 1; x++) s[x] = true;
    vector<int> b;
    int idx = 0;
    for(int j = i; j >= 1; j--) {
      s[a[j]] = false;
      while(!s[idx] && idx <= n + 1) idx++;
      int mex = idx;
      b.push_back(mex);
    }

    //reset empty spots
    for(int j = 0; j <= m; j++) slot[j] = false;
    for(int j = 0; j <= m; j++) {
      if(!vis[j]) {
        slot[j] = true;
      }
    }

    for(int j = 0; j < i; j++) {
      int x = b.back();
      for(int k = pos[x]; k <= j ; k++) {
        for(int y : p[k]) {
          if(slot[x ^ y]) {
            slot[x ^ y] = false;
            vis[x ^ y] = true;
            p[i].push_back(x ^ y);
          }
        }
      }
      pos[x] = j + 1;
      b.pop_back();
    }
  }
  
 // for(int i = 0; i <= n; i++) {
     //cout << p[i] << endl;
  //}

  int res = 0;
  for(int i = 0; i <= m; i++) {
    if(vis[i]) res = max(res, i);
  }
  printf("%d\n", res);
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

