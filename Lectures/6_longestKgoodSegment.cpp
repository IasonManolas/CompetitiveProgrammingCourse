#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

/*
 * For solving this problem we use a sliding window denoted by two indices l,r
 * representing the leftmost and righmost elements of the window. We keep
 * extending the right end until the number of distinct elements becomes bigger
 * than k and the left end whenever the number of distinct elements is bigger
 * than k. While doing that we keep track of the largest k-good segment
 * encountered. This algorithm is correct because before each increase of the
 * rigth-end index the maximum k-good segment for the subarray [0,r] is formed.
 * Thus it has gone through all k-good segments of the whole array when r
 * reaches n. Time complexity is θ(n) since each element can be added and
 * removed at most once from the sliding window.
 * */

unordered_map<int64_t, int64_t> segmentElementFrequecies;

void add(int64_t el) {
  if (segmentElementFrequecies.count(el) != 0) {
    segmentElementFrequecies[el]++;
  } else {
    segmentElementFrequecies.insert(make_pair(el, 1));
  }
}

void remove(int64_t el) {
  segmentElementFrequecies[el]--;
  if (segmentElementFrequecies[el] == 0) {
    segmentElementFrequecies.erase(el);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int64_t n, k;
  cin >> n;
  cin >> k;

  vector<int64_t> v(n);
  for (int64_t i = 0; i < n; ++i) {
    cin >> v[i];
  }

  int64_t l = 0, r = 0;
  int64_t lmax = l, rmax = r;
  int64_t maxKgoodSegment = 1;

  add(v[0]);
  while (true) {
    if (segmentElementFrequecies.size() > k) {
      if (r == n)
        break;
      remove(v[l]);
      l++;
    } else {
      r++;
      if (r == n) {
        break;
      }
      add(v[r]);
      if (r - l + 1 > maxKgoodSegment && segmentElementFrequecies.size() <= k) {
        maxKgoodSegment = r - l + 1;
        lmax = l;
        rmax = r;
      }
    }
  }

  cout << lmax + 1 << " " << rmax + 1 << endl;
  return 0;
}
