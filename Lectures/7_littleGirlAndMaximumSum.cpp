#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <unordered_set>
#include <vector>
using namespace std;

template <typename T> vector<T> get_input_sequence(size_t n) {
  vector<T> sequence(n);

  for (size_t i = 0; i < n; ++i)
    cin >> sequence[i];
  return sequence;
}

/*
 * Using prefix sums we compute the number of times each element is queried and
 * then we construct the result by sorting the frequencies, the given vector and
 * by computing the product of those and adding it to the result. The bottleneck
 * is the sorting of frequencies and of the given vector. Time complexity is
 * O(nlogn). Space complexity is θ(n)
 * */

int main() {
  std::ios_base::sync_with_stdio(false);

  size_t n;
  cin >> n;
  size_t q;
  cin >> q;

  auto v = get_input_sequence<size_t>(n);
  auto c = vector<int64_t>(n, 0);

  // create vector of votes for the queries. O(q)
  for (size_t i = 0; i < q; ++i) {
    int l, r;
    cin >> l;
    cin >> r;
    c[l - 1]++; // l and r are not zero based
    if (r < n)  // if right index is not the last element
      c[r]--;   // decrease by 1 so that the prefix sum does not propagate
                // c[l]++
  }

  // compute the prefix sum
  for (size_t i = 1; i < n; ++i)
    c[i] += c[i - 1];
  // prefix sum contains the number of times the ith element was queried
  std::sort(v.begin(), v.end());
  std::sort(c.begin(), c.end());

  // compute result
  int64_t sum = 0;
  for (size_t i = 0; i < n; ++i) {
    sum += v[i] * c[i];
  }
  cout << sum << endl;

  return 0;
}
