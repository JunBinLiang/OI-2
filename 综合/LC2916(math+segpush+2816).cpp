using ll = long long;
const int MOD = 1e9 + 7;
const int N = 1e5 + 10;

struct Node {
    int l, r;
    ll setTo = 0, sum = 0;
} tree[N * 4];

void build(int id) {
    int l = tree[id].l, r = tree[id].r;
    if(l == r) {
        return;
    }
    int mid = l + (r - l) / 2;
    tree[id * 2 + 1] = {l, mid, 0, 0};
    tree[id * 2 + 2] = {mid + 1, r, 0, 0};
    build(id * 2 + 1);
    build(id * 2 + 2);
}

void update(int id, int s, int e, ll val) { 
    int l = tree[id].l, r = tree[id].r;
    int sz = r - l + 1;
    if(l == s && r == e) {
        tree[id].setTo += val;
        tree[id].setTo %= MOD;
        tree[id].sum += (val * sz);
        tree[id].sum %= MOD;
        return;
    }

    int mid = l + (r - l) / 2;
    int left = id * 2 + 1, right = id * 2 + 2;


    if(tree[id].setTo != 0) {
        update(left, tree[left].l, tree[left].r, tree[id].setTo);
        update(right, tree[right].l, tree[right].r, tree[id].setTo);
        tree[id].setTo = 0;
    }

    if(e <= mid) {
        update(left, s, e, val);
    } else if(s >= mid + 1) {
        update(right, s, e, val);
    } else {
        update(left, s, mid, val);
        update(right, mid + 1, e, val);
    }
    
    tree[id].sum = tree[left].sum + tree[right].sum;
    tree[id].sum %= MOD;
}


ll query(int id, int s, int e) {
    int l = tree[id].l, r = tree[id].r;
    if(l == s && r == e){
        return tree[id].sum;
    }
    int mid = l + (r - l) / 2;
    int left = id * 2 + 1, right = id * 2 + 2;

    if(tree[id].setTo != 0) {
        update(left, tree[left].l, tree[left].r, tree[id].setTo);
        update(right, tree[right].l, tree[right].r, tree[id].setTo);
        tree[id].setTo = 0;
    }

    if(e <= mid){
        return query(left, s, e);
    } else if(s >= mid + 1) {
        return query(right, s, e);
    } else {
        return (query(left, s, mid) + query(right, mid + 1, e)) % MOD;
    }
}


class Solution {
public:
    int sumCounts(vector<int>& a) {
        int n = a.size();

        
        map<int, vector<int>> f;
        ll res = 1;
        tree[0] = {0, n - 1, 0, 0};
        build(0);
        update(0, 0, 0, 1);
        f[a[0]].push_back(0);
        
        ll tot = 1;
        for(int i = 1; i < n; i++) {
            int x = a[i];
            if(f.find(x) != f.end()) {
                int last = f[x].back() + 1;
                if(last <= i - 1) {
                    int last = f[x].back() + 1;
                    ll sum = query(0, last, i - 1);
                    ll add = (2 * sum + i - last) % MOD;
                    update(0, last, i, 1);
                    tot += add;
                } else {
                    update(0, i, i, 1);
                }
            } else {
                ll sum = query(0, 0, i - 1);
                ll add = (2 * sum + i) % MOD;
                update(0, 0, i, 1);
                tot += add;
            }
            f[x].push_back(i);
            tot++;
            res += tot;
            res %= MOD;
        }
        
        return res;
    }
};
