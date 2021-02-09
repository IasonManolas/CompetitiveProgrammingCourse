#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

/*
 * We begin by computing the prefix sum vector of the given vector. If the sum
 * of the vector elements are not exactly dividable with 3 there are zero ways
 * to split the given elements. Next we compute in how many ways we can split
 * the subarray (i,N)  in two parts so that they are equal to each other and to
 * the 2*totalSum/3. Finally we compute the result by iterating throught the
 * prefix sum array and whenever the prefix sum of the ith element is equal to
 * totalSum/3 we add to the result the number of ways in which we can split the
 * rest of the array [i,n] in two equal parts of 2*totalSum/3 (which we did in
 * the previous step). Time and space complexity: θ(n)
 * */

int main() {
  int64_t N;
  cin >> N;

  std::vector<int64_t> v(N, 0);
  std::vector<int64_t> S(N, 0);
  cin >> v[0];
  // compute the prefix sum vector
  S[0] = v[0];
  for (int64_t i = 1; i < N; i++) {
    cin >> v[i];
    S[i] = S[i - 1] + v[i];
  }

  // If the sum is not dividable by there are zero ways
  if (S.back() % 3 != 0) {
    std::cout << 0 << std::endl;
    return 0;
  }
  const int64_t targetSum = S.back() / 3;

  // Construct vector of which the ith value represents in how many ways we can
  // split v(i,N) in two equal summing parts
  // Time complexity O(n)
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
