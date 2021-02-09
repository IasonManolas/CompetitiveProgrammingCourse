#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;
/*
 * We transform a to b from the leftmost to the rightmost digit.The number of
 * steps needed to transform a_i to b_i is abs(b_(i-1)-b_i). Time complexity:
 * θ(n). Space complexity: θ(n)
 * */

int main() {
  size_t n;
  cin >> n;
  vector<int> b(n);
  cin >> b[0];
  int64_t steps = abs(b[0]);
  for (size_t i = 1; i < n; i++) {
    cin >> b[i];
    steps += abs(b[i - 1] - b[i]);
  }
  cout << steps << endl;

  return 0;
}
