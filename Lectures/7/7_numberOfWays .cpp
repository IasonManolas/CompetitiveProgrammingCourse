#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

int main() {
  int64_t N;
  cin >> N;

  std::vector<int64_t> v(N, 0);
  std::vector<int64_t> S(N, 0); // We do not need to save it
  cin >> v[0];
  //  v[0] = 0;
  S[0] = v[0];
  for (int64_t i = 1; i < N; i++) {
    cin >> v[i];
    //    v[i] = 0;
    S[i] = S[i - 1] + v[i];
  }

  // If the sum is not dividable by there are zero ways
  if (S.back() % 3 != 0) {
    std::cout << 0 << std::endl;
    return 0;
  }
  const int64_t targetSum = S.back() / 3;

  // Construct vector that its ith value tells in how many ways we can split
  // v(i,N) in two equal summing parts O(n)
  int64_t sum = v[N - 1];
  int64_t numberOfWaysSplitInTwo = 0;
  std::vector<int64_t> numberOfWaysSplitInTwoSuffix(N, 0);
  for (int64_t i = N - 2; i > 0; i--) {
    if (sum == targetSum) {
      numberOfWaysSplitInTwo++;
    }
    sum += v[i];
    if (sum == 2 * targetSum) {
      numberOfWaysSplitInTwoSuffix[i] = numberOfWaysSplitInTwo;
    } else {
      numberOfWaysSplitInTwoSuffix[i] = 0;
    }
  }

  int64_t numberOfWays = 0; // the answer O(n)
  for (int64_t i = 0; i < N - 1; i++) {
    if (S[i] == targetSum) {
      numberOfWays += numberOfWaysSplitInTwoSuffix[i + 1]; // O(1)
    }
  }

  std::cout << numberOfWays << std::endl;

  return 0;
}
