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

int main() {
  int64_t n, m;
  cin >> n >> m;
  vector<set<int64_t>> pointsPerNumSeg(
      n); // pointsPerNumSeg[i] contains all the points that are
          // contained in i number of segments
  vi prefixSumSegments(n + 1, 0);
  int i = 0;
  while (i++ != n) {
    int64_t l, r;
    cin >> l >> r;
    prefixSumSegments[l]++;
    prefixSumSegments[r + 1]--;
  }

  // compute number of segments per point
  int64_t counter = 0;
  for (int64_t i = 0; i < n; i++) {
    counter += prefixSumSegments[i];
    pointsPerNumSeg[counter].insert(i);
  }

  while (m--) {
    int64_t i, j, k;
    cin >> i >> j >> k;
    const set<int64_t> &points = pointsPerNumSeg[k];
    const auto &pIt = points.lower_bound(i);
    if (pIt != points.end() && *pIt <= j) {
      cout << 1 << endl;
    } else {
      cout << 0 << endl;
    }
  }

  return 0;
}
