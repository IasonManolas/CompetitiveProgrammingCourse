#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
using namespace std;

/*
 * We compute the greatest tower by computing the size of the maximum bucket for
 * unordered_multiset in which we keep the towers. The number of towers is given
 * by the number of buckets
 *
 * Time complexity: O(nlogn) for constructing the distinct tower set
 * Space complexity: θ(n)
 * */

int main() {
  size_t N;
  cin >> N;
  std::unordered_multiset<size_t> towers;
  size_t maxTower = 1;
  for (size_t i = 0; i < N; i++) {
    size_t l;
    cin >> l;
    towers.insert(l); // amortized constant time complexity
    maxTower = std::max(towers.count(l), maxTower);
  }

  std::set<size_t> distinctTowers(towers.begin(), towers.end());
  cout << maxTower << " " << distinctTowers.size();

  return 0;
}
