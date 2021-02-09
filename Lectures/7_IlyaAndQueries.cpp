#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

/*
 * We construct a vector S that contains the partial sum of consecutive equal
 * characters. We compute the asnwer to each query by computing the difference
 * of the partial sums of the range. Time complexity θ(n+m). Space complexity
 * θ(n).
 * */
int main() {
  string s;
  cin >> s;
  size_t m;
  cin >> m;
  // Creating partial sum vector S takes O(n)
  std::vector<size_t> S(s.size());
  S[0] = s[0] == s[1] ? 1 : 0;
  for (size_t charIndex = 1; charIndex < s.size() - 1; charIndex++) {
    S[charIndex] =
        S[charIndex - 1] + (s[charIndex] == s[charIndex + 1] ? 1 : 0);
  }
  S[s.size() - 1] = S[s.size() - 2];

  // Answering each query takes constant time. Answering all queries takes O(m)
  for (size_t queryIndex = 0; queryIndex < m; queryIndex++) {
    size_t i, j;
    cin >> i;
    cin >> j;
    i--;
    j--;
    const size_t Sl = i == 0 ? 0 : S[i - 1];
    size_t queryResult = S[j - 1] - Sl;
    std::cout << queryResult << std::endl;
  }

  // Total complexity O(m+n)
  return 0;
}
