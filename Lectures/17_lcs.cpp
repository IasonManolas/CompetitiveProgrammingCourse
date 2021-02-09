// { Driver Code Starts
#include <bits/stdc++.h>
const int mod = 1e9 + 7;
using namespace std;

int lcs(int, int, string, string);

int main() {
  int t, n, k, x, y;

  cin >> t;
  while (t--) {
    cin >> x >> y; // Take size of both the strings as input
    string s1, s2;
    cin >> s1 >> s2; // Take both the string as input

    cout << lcs(x, y, s1, s2) << endl;
  }
  return 0;
}
// } Driver Code Ends

// function to find longest common subsequence
int lcs(int x, int y, string s1, string s2) {
  vector<vector<size_t>> M(x + 1, std::vector<size_t>(y + 1, 0));

//θ(x*y) time and space complexity 
//cell M[i][j] contains the lcs of the s1[0:i] and s2[0:j]. Thus the
//bottom right cell contains the lcs of the full strings s1,s2
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
