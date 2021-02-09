#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/*
 * I use the lcs algorithm implemented in a previous lecture for finding the
 * longest common subsequence between the given string and the reversed string.
 * The time and space complexity is θ(n^2) where n is the length of the string.
 * */
int lcs(int x, int y, string s1, string s2) {
  vector<vector<size_t>> M(x + 1, std::vector<size_t>(y + 1, 0));

  // O(x*y)
  // cell M[i][j] contains the lcs of the s1[0:i] and s2[0:j]. Thus the
  // bottom right cell contains the lcs of the full strings s1,s2
  for (size_t i = 0; i < x + 1; i++) {
    for (size_t j = 0; j < y + 1; j++) {
      if (i == 0 || j == 0) {
        M[i][j] = 0;
      } else if (s1[i - 1] == s2[j - 1]) {
        M[i][j] = 1 + M[i - 1][j - 1];
      } else {
        M[i][j] = max(M[i][j - 1], M[i - 1][j]);
      }
    }
  }

  return M[x][y];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  size_t tc;
  cin >> tc;
  std::string s;
  while (tc--) {
    cin >> s;

    cout << lcs(s.size(), s.size(), s, string(s.rbegin(), s.rend())) << endl;
  }

  return 0;
}
