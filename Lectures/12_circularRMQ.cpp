#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

#define REP(i, a, b) for (int64_t i = a; i <= b; i++)
#define REP_R(i, a, b) for (int64_t i = a; i >= b; i--)
#define F first
#define S second
#define PB push_back
#define MP make_pair
typedef vector<int64_t> vi;
/*
 * For solving this problem we use a segment tree. We use lazy propagation for
 * adding to a range and modify it for supporting range minimum queries. The
 * requirement that the segment tree works in a circular manner is solved by
 * simply breaking up the query in two if the left-end of the range is bigger
 * than the right one. In this case we break up the range as [l,r]=[1,r]+[l,n].
 * Time complexity:
 * for building θ(4n)=θ(n)
 * for adding θ(logn)
 * for answering a query θ(logn)
 * Overall:θ(n)+θ(2*m*logn)=θ(n+mlogn)
 * space complexity is θ(n) since segment trees require θ(n) space
 * */
struct node {
  int64_t l, r, minimum, propagationValue;
} tree[800005];

int64_t n;
void build(int64_t l, int64_t r, int64_t k) {
  tree[k].l = l;
  tree[k].r = r;
  if (l == r) {
    cin >> tree[k].minimum;
    return;
  }
  int64_t mid = (l + r) / 2;
  build(l, mid, k * 2);
  build(mid + 1, r, k * 2 + 1);
  tree[k].minimum = min(tree[k * 2].minimum, tree[k * 2 + 1].minimum);
}
void add(int64_t k, int64_t w, int64_t ll, int64_t rr) {
  int64_t l = tree[k].l, r = tree[k].r;
  if (l >= ll && r <= rr) {
    tree[k].propagationValue += w;
    return;
  }
  int64_t mid = (l + r) / 2;
  if (ll <= mid)
    add(k * 2, w, ll, rr);
  if (rr > mid)
    add(k * 2 + 1, w, ll, rr);
  tree[k].minimum =
      min(tree[k * 2].minimum + tree[k * 2].propagationValue,
          tree[k * 2 + 1].minimum + tree[k * 2 + 1].propagationValue);
  return;
}
int64_t query(int64_t k, int64_t ll, int64_t rr) {
  if (tree[k].l >= ll && tree[k].r <= rr) {
    return tree[k].minimum + tree[k].propagationValue;
  }
  if (tree[k].l > rr || tree[k].r < ll) {
    return std::numeric_limits<int64_t>::max();
  }
  int64_t lc = query(k * 2, ll, rr);
  int64_t rc = query(k * 2 + 1, ll, rr);
  return min(lc, rc) + tree[k].propagationValue;
}

int main() {
  int64_t m, q, x, y;
  cin >> n;
  build(1, n, 1);
  cin >> m;
  for (int64_t i = 1; i <= m; i++) {
    cin >> x >> y;
    x++;
    y++;
    char c = getchar();
    if (c == '\n') {
      if (x > y)
        cout << min(query(1, x, n), query(1, 1, y));
      else
        cout << query(1, x, y);
      cout << endl;
    } else {
      cin >> q;
      if (x > y)
        add(1, q, x, n), add(1, q, 1, y);
      else
        add(1, q, x, y);
    }
  }
  return 0;
}
