#include <algorithm>
//#include <cmath>
// #include <cstdio>
#include <iostream>
#include <vector>
// #include <unordered_set>
using namespace std;

template <typename T> vector<T> get_input_sequence(size_t n) {
  vector<T> sequence(n);

  for (size_t i = 0; i < n; ++i)
    cin >> sequence[i];
  return sequence;
}

/*
 * We initialy begin by computing the maximum distance between consecutive rungs
 * maxDist.
 * The solution cant be smaller than maxDist because there exists at least a
 * rung with maxDist. All previous rungs can be climbed without a decrease
 * in k since maxDist is bigger than all of them (since its the maximum).
 * For all rungs coming after maxDist we need to check whether there is
 * enough strength. If k is enough its also the minimum if not the solution
 * is maxDist+1. This is for sure enough since there wont be any rungs
 * decreasing k.
 *
 * Time complexity is θ(n) since we proccess each rung. Space complexity is θ(n)
 */
int main() {
  std::ios_base::sync_with_stdio(false);
  size_t T;
  cin >> T;
  for (size_t tc = 0; tc < T; tc++) {
    size_t n;
    cin >> n;
    auto v = get_input_sequence<size_t>(n);

    // find max distance between rungs O(n)
    size_t maxDist = v[0];
    for (size_t i = 0; i < n - 1; i++) {
      maxDist = std::max(maxDist, v[i + 1] - v[i]);
    }

    int64_t k = maxDist;
    size_t minK = k;
    if (v[0] == k) {
      k -= 1;
    }

    for (size_t i = 0; i < n - 1; i++) {
      if (v[i + 1] - v[i] > k) {
        minK = maxDist + 1;
        break;
      } else if (v[i + 1] - v[i] == k) {
        k -= 1;
      }
    }
    cout << "Case " << tc + 1 << ": " << minK << endl;
  }

  return 0;
}
