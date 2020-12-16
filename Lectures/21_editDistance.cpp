// { Driver Code Starts

#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends

/*
 * We solve the subproblems of computing the edit distance for editing the
 prefix
 * s(0:i) into t(0:j). We save the result in a matrix
 * M. The answer to the problem of finding the edit distance between the
 * whole strings s and t is found at position M[s.size()][t.size()] of the
 * matrix. The time complexity of the solution is the time complexity of filing
 * the matrix M, namely θ(s.size()*t.size()).
 * For computing M[i][j] (which is the edit distance between the prefix s(0:i)
 and t(0:j)) if s(i)==t(j) then
 * the edit distance is M[i][j]=M[i-1][j-1]
 *  If s(i)!=t[j] we choose based on the min of the following:
 * Replace the t(j) with s(i) and thus M[i-1][j-1]+1
 * remove the last char at the end of the string s and thus M[i][j-1]+1
 * insert a char at the end of the string s and thus M[i-1][j]+1
*/
class Solution {
public:
  int editDistance(string s, string t) {
    vector<vector<int>> M(s.size() + 1, vector<int>(t.size() + 1));

    for (int i = 0; i < s.size() + 1; i++) {
      for (int j = 0; j < t.size() + 1; j++) {
        if (i == 0 || j == 0)
          M[i][j] = i + j;
        else if (s[i - 1] == t[j - 1]) {
          M[i][j] = M[i - 1][j - 1];
        } else {
          M[i][j] =
              1 + std::min(std::min(M[i - 1][j], M[i][j - 1]), M[i - 1][j - 1]);
        }
      }
    }

    return M[s.size()][t.size()];
  }
};

// { Driver Code Starts.
int main() {
  int T;
  cin >> T;
  while (T--) {
    string s, t;
    cin >> s >> t;
    Solution ob;
    int ans = ob.editDistance(s, t);
    cout << ans << "\n";
  }
  return 0;
}
// } Driver Code Ends
