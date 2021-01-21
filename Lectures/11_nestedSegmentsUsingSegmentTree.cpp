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

/*
 * For solving this problem I used a segment tree that stores the right-end
 * sorted segments. I processed the segments in left-decreasing order.The number
 * of contained segments for each segment is the sum of segments that have
 * larger left-end and smaller right-end. Using the segment tree this query can
 * processed in θ(logn) time by using the Sum(right-end-sorted-index) function
 * and the index of the segments in the right-end sorted vector. Overall time
 * complexity: θ(nlogn)
 * */
struct Segment {
  int64_t l;
  int64_t r;
  int64_t index;
};

struct FenwickTree {
  vector<int> bit; // binary indexed tree
  int n;

  FenwickTree(int n) {
    this->n = n;
    bit.assign(n, 0);
  }

  FenwickTree(vector<Segment> a) : FenwickTree(a.size()) {
    for (size_t i = 0; i < a.size(); i++)
      add(i, a[i].r);
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

struct SegmentLCompare {
  bool operator()(const Segment &s0, const Segment &s1) const {
    return s0.l < s1.l;
  }
};

struct SegmentTree {
  vi tree;
  int n;

  SegmentTree(int n) {
    tree.resize(2 * n, 0);
    this->n = n;
  }

  int sum(int a, int b) {
    a += n;
    b += n;
    int s = 0;
    while (a <= b) {
      if (a % 2 == 1)
        s += tree[a++];
      if (b % 2 == 0)
        s += tree[b--];
      a /= 2;
      b /= 2;
    }
    return s;
  }

  void add(int k, int x) {
    k += n;
    tree[k] += x;
    for (k /= 2; k >= 1; k /= 2) {
      tree[k] = tree[2 * k] + tree[2 * k + 1];
    }
  }
};

int main() {
  int64_t n;
  cin >> n;
  vector<Segment> lSortedSegments(n);
  vector<int> numContainedSegments(n, 0);
  int64_t i = 0;
  while (i < n) {
    int64_t l, r;
    cin >> l >> r;
    Segment s{l, r, i};
    lSortedSegments[i++] = s;
  }

  std::sort(lSortedSegments.begin(), lSortedSegments.end(),
            [](const Segment &s0, const Segment &s1) { return s0.l > s1.l; });

  vector<Segment> rSortedSegments = lSortedSegments;
  std::sort(rSortedSegments.begin(), rSortedSegments.end(),
            [](const Segment &s0, const Segment &s1) { return s0.r < s1.r; });

  vector<int> RSortedIndex(n);
  for (int i = 0; i < rSortedSegments.size(); i++) {
    const Segment &s = rSortedSegments[i];
    RSortedIndex[s.index] = i;
  }

  SegmentTree st(n);

  for (const Segment s : lSortedSegments) {
    numContainedSegments[s.index] = st.sum(0, RSortedIndex[s.index]);
    st.add(RSortedIndex[s.index], 1);
  }

  for (auto containedSegments : numContainedSegments) {
    std::cout << containedSegments << std::endl;
  }

  return 0;
}
