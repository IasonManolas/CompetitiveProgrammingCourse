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
 * If counter1[i] contains the number of elements j for which a[i]<a[j] && i<j
 * in a and counter2[i] contains the number of elements k for which a[i]>a[k] &&
 * i>k then the result is the sum of counter1[i]*counter2[i] over all elements.
 * Time complexity:each sum and add command take θ(logn) respectively.
 * Thus we need θ(n*(2logn)) for filling counter1 and counter2 respectively.
 * Total complexity is thus θ(n*(4logn))=θ(nlogn)
 */
int main() {
  int64_t t = 1;
  //    cin >> t;
  while (t--) {
    int64_t n;
    cin >> n;
    vi a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }

    FenwickTree fwt1(n);
    std::vector<int> counter1(n, 0);
    for (int i = n - 1; i >= 0; i--) {
      counter1[i] = fwt1.sum(a[i] + 1, n - 1);
      fwt1.add(a[i], 1);
    }

    int res = 0;
    FenwickTree fwt2(n);
    std::vector<int> counter2(n, 0);
    for (int i = 0; i < n; i++) {
      counter2[i] = fwt2.sum(a[i] - 1);
      fwt2.add(a[i], 1);
      res += counter1[i] * counter2[i];
    }
    cout << res << endl;
  }
  return 0;
}
