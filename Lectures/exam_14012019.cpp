#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

#define REP(i, a, b) for (int i = a; i <= b; i++)
#define REP_R(i, a, b) for (int i = a; i >= b; i--)
#define F first
#define S second
#define PB push_back
#define MP make_pair
typedef vector<int64_t> vi;
typedef pair<int64_t, int64_t> pi;

struct FenwickTree {
  vector<int> bit; // binary indexed tree
  int n;

  FenwickTree(int n) {
    this->n = n;
    bit.assign(n, 0);
  }

  int sum(int r) {
    int ret = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1)
      ret += bit[r];
    return ret;
  }

  int sum(int l, int r) { return sum(r) - sum(l - 1); }

  void add(int idx, int delta) {
    for (; idx < n; idx = idx | (idx + 1))
      bit[idx] += delta;
  }
};

/*
 * For solving this problem we sort the queries and the vector of given elements
 * by value. Then we use a fenwick tree while processing the querries. For each
 * query we add 1 to each value of the original vector that is smaller than the
 * querrie's x value. Thus the answer to each query is the sum in the range of
 * the query. Time complexity: I have commented in the code regarding the
 * complexity. overall complexity: θ(nlogn+mlogn)=θ((n+m)*logn)
 */

struct Element {
  int x;
  int initialIndex;
};

struct Query {
  int l;
  int r;
  int x;
  int initialIndex;
};

int main() {
  int64_t n, m;
  cin >> n >> m;
  vector<Element> a(n);
  vector<Query> q(m);
  for (int i = 0; i < n; i++) {
    cin >> a[i].x;
    a[i].initialIndex = i;
  }
  std::sort(a.begin(), a.end(),
            [](Element a, Element b) { return a.x < b.x; }); //θ(nlogn)

  for (int i = 0; i < m; i++) {
    cin >> q[i].l >> q[i].r >> q[i].x;
    q[i].initialIndex = i;
  }
  std::sort(q.begin(), q.end(),
            [](Query a, Query b) { return a.x < b.x; }); //θ(mlogm)

  FenwickTree ft(n);

  int greatestXIndex = 0;
  vi res(m);
  for (int i = 0; i < m; i++) { //θ(mlogn)
    while (a[greatestXIndex].x <= q[i].x) {
      ft.add(a[greatestXIndex].initialIndex, 1); //θ(logn)
      greatestXIndex++;
    }
    res[q[i].initialIndex] = ft.sum(q[i].l, q[i].r); //θ(logn)
  }

  for (int ans : res) {
    cout << ans << endl;
  }

  return 0;
}
